#!/usr/bin/env node
import net from "node:net";

function option(name, fallback = null) {
  const i = process.argv.indexOf(name);
  return i >= 0 ? process.argv[i + 1] : fallback;
}

const port = Number(option("--port", "4475"));
const execute = option("--execute");
const rawArguments = option("--arguments");
if (!execute) throw new Error("missing --execute COMMAND");
if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error("invalid --port");
const commandArguments = rawArguments ? JSON.parse(rawArguments) : null;

const socket = net.createConnection({ host: "127.0.0.1", port });
socket.setEncoding("utf8");
let buffer = "";
const replies = [];
const waiters = [];
socket.on("data", chunk => {
  buffer += chunk;
  for (;;) {
    const newline = buffer.indexOf("\n");
    if (newline < 0) break;
    const line = buffer.slice(0, newline).trim();
    buffer = buffer.slice(newline + 1);
    if (!line) continue;
    const message = JSON.parse(line);
    if (message.event) continue;
    const waiter = waiters.shift();
    if (waiter) waiter(message);
    else replies.push(message);
  }
});

function nextReply(timeout = 5000) {
  if (replies.length) return Promise.resolve(replies.shift());
  return new Promise((resolve, reject) => {
    const timer = setTimeout(() => reject(new Error("QMP response timeout")), timeout);
    waiters.push(value => { clearTimeout(timer); resolve(value); });
  });
}

function send(command, args = null) {
  socket.write(`${JSON.stringify({ execute: command, ...(args ? { arguments: args } : {}) })}\r\n`);
  return nextReply();
}

try {
  await new Promise((resolve, reject) => {
    socket.once("connect", resolve);
    socket.once("error", reject);
    setTimeout(() => reject(new Error("QMP connect timeout")), 3000);
  });
  const greeting = await nextReply();
  const capabilities = await send("qmp_capabilities");
  const response = await send(execute, commandArguments);
  console.log(JSON.stringify({ greeting, capabilities, execute, arguments: commandArguments, response }, null, 2));
} catch (error) {
  console.error(`xemu-qmp-control: ${error.message}`);
  process.exitCode = 1;
} finally {
  socket.destroy();
}
