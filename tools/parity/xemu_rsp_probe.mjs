#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

function option(name, fallback = null) {
  const i = process.argv.indexOf(name);
  return i >= 0 ? process.argv[i + 1] : fallback;
}

const command = process.argv[2] || "probe";
const host = option("--host", "127.0.0.1");
const port = Number(option("--port", "1265"));
if (command !== "probe") throw new Error("usage: node xemu_rsp_probe.mjs probe [--host HOST] [--port PORT]");
if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error("invalid --port");

const socket = net.createConnection({ host, port });
socket.setNoDelay(true);
const timeout = setTimeout(() => socket.destroy(new Error("connect timeout")), 3000);
try {
  await new Promise((resolve, reject) => {
    socket.once("connect", resolve);
    socket.once("error", reject);
  });
  clearTimeout(timeout);
  const rsp = new RspClient(socket);
  let supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (/^[STW]/.test(supported)) supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  console.log(JSON.stringify({ ok: true, host, port, supported }, null, 2));
  rsp.resume();
  setTimeout(() => rsp.close(), 50);
} catch (error) {
  clearTimeout(timeout);
  console.error(`xemu-rsp: ${error.message}`);
  socket.destroy();
  process.exitCode = 1;
}
