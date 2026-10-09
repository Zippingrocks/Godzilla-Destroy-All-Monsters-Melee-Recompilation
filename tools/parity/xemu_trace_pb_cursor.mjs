#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const opt = (n, d) => args.includes(n) ? args[args.indexOf(n) + 1] : d;
const port = Number(opt("--port", "1265"));
const hits = Number(opt("--hits", "12"));
const address = Number(opt("--address", "0x00134080"));
const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((ok, fail) => { socket.once("connect", ok); socket.once("error", fail); });
socket.setNoDelay(true);
const rsp = new RspClient(socket);
let running = false, armed = false;
const le32 = (b, n) => b.readUInt32LE(n * 4);
try {
  let supported = "";
  for (let i = 0; i < 4 && !supported.includes("PacketSize"); ++i)
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  await rsp.halt();
  if (await rsp.packet(`Z2,${address.toString(16)},4`) !== "OK")
    throw new Error("write watchpoint rejected");
  armed = true;
  const samples = [];
  for (let i = 0; i < hits; ++i) {
    rsp.resume(); running = true;
    const stop = await rsp.nextPacket(10000); running = false;
    const regs = Buffer.from(await rsp.packet("g"), "hex");
    const esp = le32(regs, 4);
    const stackReply = await rsp.packet(`m${esp.toString(16)},40`);
    samples.push({ hit: i, stop,
      eip: `0x${le32(regs, 8).toString(16).padStart(8,"0")}`,
      esp: `0x${esp.toString(16).padStart(8,"0")}`,
      ecx: `0x${le32(regs, 1).toString(16).padStart(8,"0")}`,
      stack: stackReply });
  }
  console.log(JSON.stringify({ address: `0x${address.toString(16)}`, samples }, null, 2));
} finally {
  if (running) { try { await rsp.halt(); } catch {} }
  if (armed) { try { await rsp.packet(`z2,${address.toString(16)},4`); } catch {} }
  rsp.resume(); socket.destroy();
}
