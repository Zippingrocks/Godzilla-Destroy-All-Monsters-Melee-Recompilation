#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const option = (name, fallback) => args.includes(name) ? args[args.indexOf(name) + 1] : fallback;
const port = Number(option("--port", "1265"));
const address = Number(option("--address", "NaN"));
const length = Number(option("--length", "256"));
if (!Number.isInteger(address) || address < 0 || address > 0xffffffff ||
    !Number.isInteger(length) || length < 1 || length > 0x10000)
  throw new Error("usage: node xemu_read_guest.mjs --address ADDRESS [--length LENGTH] [--port PORT]");

const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => {
  socket.once("connect", resolve);
  socket.once("error", reject);
});
socket.setNoDelay(true);
const rsp = new RspClient(socket);
let halted = false;
try {
  let supported = "";
  for (let attempt = 0; attempt < 4 && !supported.includes("PacketSize"); ++attempt)
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (!/^[STW]/.test(supported)) {
    await rsp.halt();
    halted = true;
  } else {
    halted = true;
  }
  const reply = await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
  if (!/^[0-9a-f]+$/i.test(reply) || reply.length !== length * 2)
    throw new Error(`guest read failed: ${reply}`);
  const data = Buffer.from(reply, "hex");
  for (let offset = 0; offset < data.length; offset += 16) {
    const row = data.subarray(offset, offset + 16);
    const hex = [...row].map(value => value.toString(16).padStart(2, "0")).join(" ");
    const ascii = [...row].map(value => value >= 0x20 && value < 0x7f ? String.fromCharCode(value) : ".").join("");
    console.log(`${((address + offset) >>> 0).toString(16).padStart(8, "0")}: ${hex.padEnd(47)}  ${ascii}`);
  }
} finally {
  if (halted) rsp.resume();
  socket.destroy();
}
