#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const opt = (name, fallback) => args.includes(name) ? args[args.indexOf(name) + 1] : fallback;
const port = Number(opt("--port", "1265"));
const inputEntry = 0x001DAB1C;
const callbackEntry = Number(opt("--breakpoint", "0x000ECD40"));
const action = opt("--action", "a").toLowerCase();
if (!["a", "b", "start", "up", "down", "left", "right"].includes(action))
  throw new Error("invalid --action");
const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => { socket.once("connect", resolve); socket.once("error", reject); });
socket.setNoDelay(true);
const rsp = new RspClient(socket);
let running = false;
let inputBreak = false;
let callbackBreak = false;

async function read(address, length) {
  const reply = await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
  if (!/^[0-9a-f]+$/i.test(reply)) throw new Error(`read failed: ${reply}`);
  return Buffer.from(reply, "hex");
}
async function write(address, bytes) {
  const reply = await rsp.packet(`M${address.toString(16)},${bytes.length.toString(16)}:${bytes.toString("hex")}`);
  if (reply !== "OK") throw new Error(`write failed: ${reply}`);
}

try {
  let supported = "";
  for (let attempt = 0; attempt < 4 && !supported.includes("PacketSize"); ++attempt)
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (!supported.includes("PacketSize")) throw new Error(`GDB handshake failed: ${supported}`);
  await rsp.halt();
  if (await rsp.packet(`Z1,${inputEntry.toString(16)},1`) !== "OK") throw new Error("input breakpoint rejected");
  inputBreak = true;
  rsp.resume(); running = true;
  let stop = await rsp.nextPacket(30000); running = false;
  if (!/^[STW]/.test(stop)) throw new Error(`unexpected input stop: ${stop}`);
  let registers = Buffer.from(await rsp.packet("g"), "hex");
  const esp = registers.readUInt32LE(4 * 4);
  const stack = await read(esp, 12);
  const returnAddress = stack.readUInt32LE(0);
  const stateAddress = stack.readUInt32LE(8);
  const state = Buffer.alloc(22);
  state.writeUInt32LE(1, 0);
  const digital = { up: 0x0001, down: 0x0002, left: 0x0004, right: 0x0008, start: 0x0010 };
  if (action in digital) state.writeUInt16LE(digital[action], 4);
  if (action === "a") state[6] = 255;
  if (action === "b") state[7] = 255;
  await write(stateAddress, state);
  await rsp.packet(`z1,${inputEntry.toString(16)},1`); inputBreak = false;
  if (await rsp.packet(`Z1,${callbackEntry.toString(16)},1`) !== "OK") throw new Error("callback breakpoint rejected");
  callbackBreak = true;
  registers.writeUInt32LE(0, 0);
  registers.writeUInt32LE((esp + 12) >>> 0, 4 * 4);
  registers.writeUInt32LE(returnAddress, 8 * 4);
  if (await rsp.packet(`G${registers.toString("hex")}`) !== "OK") throw new Error("register write failed");
  rsp.resume(); running = true;
  stop = await rsp.nextPacket(30000); running = false;
  if (!/^[STW]/.test(stop)) throw new Error(`unexpected callback stop: ${stop}`);
  registers = Buffer.from(await rsp.packet("g"), "hex");
  const cbEsp = registers.readUInt32LE(4 * 4);
  const ecx = registers.readUInt32LE(1 * 4);
  const eip = registers.readUInt32LE(8 * 4);
  const cbStack = await read(cbEsp, 32);
  const object = await read(ecx, 0x220);
  const manager = await read(0x004AD508, 0x170);
  const shellCommit = await read(0x004A9630, 16);
  const profileGlobals = await read(0x004B0180, 0x40);
  const mainGlobals = await read(0x002C2AC0, 0xC0);
  const nodes = [];
  let nodeAddress = manager.readUInt32LE(0x158);
  for (let i = 0; i < 8 && nodeAddress; i++) {
    const node = await read(nodeAddress, 0x220);
    nodes.push({
      address: `0x${nodeAddress.toString(16)}`,
      vtable: `0x${node.readUInt32LE(0).toString(16)}`,
      next: `0x${node.readUInt32LE(0xa4).toString(16)}`,
      ac: node[0xac], dc: node[0xdc], c8: node[0xc8],
      done: node[0x1a0], op: `0x${node.readUInt32LE(0x1a8).toString(16)}`
    });
    nodeAddress = node.readUInt32LE(0xa4);
  }
  console.log(JSON.stringify({
    port, action, inputEntry: `0x${inputEntry.toString(16)}`, callbackEntry: `0x${callbackEntry.toString(16)}`,
    eip: `0x${eip.toString(16)}`, ecx: `0x${ecx.toString(16)}`, esp: `0x${cbEsp.toString(16)}`,
    args: [cbStack.readUInt32LE(4), cbStack.readUInt32LE(8)],
    fields: { dc: object[0xdc], ac: object.readUInt32LE(0xac), done: object[0x1a0], op: object.readUInt32LE(0x1a8) },
    manager: { state: manager.readUInt32LE(0x154), head: manager.readUInt32LE(0x158), nodes },
    shellCommit: {
      tag: `0x${shellCommit.readUInt32LE(0).toString(16)}`,
      value: `0x${shellCommit.readUInt32LE(4).toString(16)}`,
      tail: shellCommit.subarray(8).toString("hex")
    },
    profileGlobalsHex: profileGlobals.toString("hex"),
    mainGlobalsHex: mainGlobals.toString("hex"),
    stackHex: cbStack.toString("hex")
  }, null, 2));
} finally {
  if (running) { try { await rsp.halt(); running = false; } catch {} }
  if (inputBreak) { try { await rsp.packet(`z1,${inputEntry.toString(16)},1`); } catch {} }
  if (callbackBreak) { try { await rsp.packet(`z1,${callbackEntry.toString(16)},1`); } catch {} }
  rsp.resume();
  socket.destroy();
}
