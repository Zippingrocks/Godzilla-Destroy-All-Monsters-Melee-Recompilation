#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const opt = (name, fallback) => args.includes(name) ? args[args.indexOf(name) + 1] : fallback;
const port = Number(opt("--port", "1265"));
const address = Number(opt("--addr", "0"));
const length = Number(opt("--length", "64"));

if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error("invalid --port");
if (!Number.isInteger(address) || address <= 0) throw new Error("--addr is required");
if (!Number.isInteger(length) || length < 1 || length > 4096) throw new Error("invalid --length");

const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => {
  socket.once("connect", resolve);
  socket.once("error", reject);
});

const rsp = new RspClient(socket);
let resumed = false;
try {
  socket.setNoDelay(true);
  let supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (/^[STW]/.test(supported)) {
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  } else {
    await rsp.halt();
  }

  const reply = await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
  if (reply.startsWith("E")) throw new Error(`memory read failed: ${reply}`);
  const data = Buffer.from(reply, "hex");
  const dwords = [];
  for (let offset = 0; offset + 4 <= data.length; offset += 4) {
    dwords.push({
      address: `0x${(address + offset).toString(16).toUpperCase().padStart(8, "0")}`,
      value: `0x${data.readUInt32LE(offset).toString(16).toUpperCase().padStart(8, "0")}`,
    });
  }
  console.log(JSON.stringify({
    port,
    address: `0x${address.toString(16).toUpperCase().padStart(8, "0")}`,
    length: data.length,
    hex: data.toString("hex"),
    dwords,
  }, null, 2));

  rsp.resume();
  resumed = true;
  await new Promise(resolve => setTimeout(resolve, 50));
} finally {
  if (!resumed) rsp.resume();
  socket.end();
}
