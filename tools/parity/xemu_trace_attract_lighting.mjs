#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const opt = (name, fallback) => args.includes(name) ? args[args.indexOf(name) + 1] : fallback;
const port = Number(opt("--port", "1265"));
const address = Number(opt("--breakpoint", "0x000AAD70"));
const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => { socket.once("connect", resolve); socket.once("error", reject); });
socket.setNoDelay(true);
const rsp = new RspClient(socket);
let armed = false;
let running = false;
async function read(address, length) {
  const reply = await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
  if (!/^[0-9a-f]+$/i.test(reply)) throw new Error(`read failed: ${reply}`);
  return Buffer.from(reply, "hex");
}
try {
  let supported = "";
  for (let attempt = 0; attempt < 4 && !supported.includes("PacketSize"); ++attempt)
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  await rsp.halt();
  if (await rsp.packet(`Z1,${address.toString(16)},1`) !== "OK") throw new Error("breakpoint rejected");
  armed = true;
  rsp.resume(); running = true;
  const stop = await rsp.nextPacket(90000); running = false;
  if (!/^[STW]/.test(stop)) throw new Error(`unexpected stop: ${stop}`);
  const registers = Buffer.from(await rsp.packet("g"), "hex");
  const eax = registers.readUInt32LE(0);
  const ecx = registers.readUInt32LE(4);
  const edx = registers.readUInt32LE(8);
  const ebx = registers.readUInt32LE(12);
  const esp = registers.readUInt32LE(16);
  const ebp = registers.readUInt32LE(20);
  const esi = registers.readUInt32LE(24);
  const edi = registers.readUInt32LE(28);
  const eip = registers.readUInt32LE(32);
  const stack = await read(esp, 48);
  const object = await read(esi, 64);
  console.log(JSON.stringify({
    eip: `0x${eip.toString(16)}`, eax: `0x${eax.toString(16)}`,
    ecx: `0x${ecx.toString(16)}`, edx: `0x${edx.toString(16)}`,
    ebx: `0x${ebx.toString(16)}`, esi: `0x${esi.toString(16)}`,
    edi, ebp: `0x${ebp.toString(16)}`, esp: `0x${esp.toString(16)}`,
    objectHex: object.toString("hex"), stackHex: stack.toString("hex")
  }, null, 2));
} finally {
  if (running) { try { await rsp.halt(); } catch {} }
  if (armed) { try { await rsp.packet(`z1,${address.toString(16)},1`); } catch {} }
  rsp.resume();
  socket.destroy();
}
