#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const opt = (name, fallback) => args.includes(name) ? args[args.indexOf(name) + 1] : fallback;
const port = Number(opt("--port", "1265"));
const hits = Number(opt("--hits", "2"));
const timeoutMs = Number(opt("--timeout", "180000"));
const breakpoint = 0x000E0820;

const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => {
  socket.once("connect", resolve);
  socket.once("error", reject);
});
socket.setNoDelay(true);
const rsp = new RspClient(socket);

function le32(hex, byteOffset) {
  return Buffer.from(hex.slice(byteOffset * 2, byteOffset * 2 + 8), "hex").readUInt32LE(0);
}

async function readMemory(address, length) {
  const reply = await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
  if (reply.startsWith("E")) throw new Error(`memory read failed at ${address.toString(16)}: ${reply}`);
  return Buffer.from(reply, "hex");
}

let breakpointSet = false;
let guestRunning = false;
try {
  let supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (/^[STW]/.test(supported)) supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  else await rsp.halt();

  const set = await rsp.packet(`Z1,${breakpoint.toString(16)},1`);
  if (set !== "OK") throw new Error(`hardware breakpoint failed: ${set}`);
  breakpointSet = true;

  const samples = [];
  for (let i = 0; i < hits; i++) {
    rsp.resume();
    guestRunning = true;
    const stop = await rsp.nextPacket(timeoutMs);
    guestRunning = false;
    if (!/^[STW]/.test(stop)) throw new Error(`unexpected stop reply: ${stop}`);
    const registers = await rsp.packet("g");
    const ecx = le32(registers, 4);
    const eip = le32(registers, 8 * 4);
    const adjustData = await readMemory(ecx - 4, 4);
    const adjust = adjustData.readUInt32LE(0);
    const iface = (ecx - adjust) >>> 0;
    const base = (iface - 0x78) >>> 0;
    const baseData = await readMemory(base, 0x84);
    const node = baseData.readUInt32LE(8);
    const nodeData = await readMemory(node, 0x90);
    const renderObject = nodeData.readUInt32LE(0);
    const renderData = await readMemory(renderObject, 0x90);
    samples.push({
      hit: i,
      stop,
      eip: `0x${eip.toString(16).toUpperCase().padStart(8, "0")}`,
      entryEcx: `0x${ecx.toString(16).toUpperCase().padStart(8, "0")}`,
      adjust: `0x${adjust.toString(16).toUpperCase().padStart(8, "0")}`,
      interface: `0x${iface.toString(16).toUpperCase().padStart(8, "0")}`,
      base: `0x${base.toString(16).toUpperCase().padStart(8, "0")}`,
      node: `0x${node.toString(16).toUpperCase().padStart(8, "0")}`,
      nodeDisabled: nodeData[0x89],
      renderObject: `0x${renderObject.toString(16).toUpperCase().padStart(8, "0")}`,
      renderCount: renderData.readUInt32LE(0x4C),
      renderRecords: `0x${renderData.readUInt32LE(0x50).toString(16).toUpperCase().padStart(8, "0")}`,
      renderRefs: `0x${renderData.readUInt32LE(0x54).toString(16).toUpperCase().padStart(8, "0")}`,
    });
  }
  console.log(JSON.stringify({ port, breakpoint: "0x000E0820", samples }, null, 2));
} finally {
  if (guestRunning) {
    try { await rsp.halt(); guestRunning = false; } catch {}
  }
  if (breakpointSet) {
    try { await rsp.packet(`z1,${breakpoint.toString(16)},1`); } catch {}
  }
  rsp.resume();
  socket.destroy();
}
