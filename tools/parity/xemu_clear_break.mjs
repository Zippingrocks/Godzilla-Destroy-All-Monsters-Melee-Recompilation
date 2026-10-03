#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const opt = (name, fallback) => args.includes(name) ? args[args.indexOf(name) + 1] : fallback;
const port = Number(opt("--port", "1265"));
const address = Number(opt("--addr", "0"));
if (!address) throw new Error("--addr is required");

const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => {
  socket.once("connect", resolve);
  socket.once("error", reject);
});
const rsp = new RspClient(socket);
try {
  socket.setNoDelay(true);
  let supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (/^[STW]/.test(supported)) {
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  } else {
    await rsp.halt();
  }
  const result = await rsp.packet(`z1,${address.toString(16)},1`);
  console.log(JSON.stringify({ port, address: `0x${address.toString(16).toUpperCase()}`, result }));
  rsp.resume();
} finally {
  socket.end();
}
