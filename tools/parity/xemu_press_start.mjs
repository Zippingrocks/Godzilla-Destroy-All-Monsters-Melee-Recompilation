#!/usr/bin/env node
/* Inject one logical controller edge at DAMM's retail XInputGetState boundary.
 * This preserves enumeration/handles and changes no menu, renderer, save, or
 * animation state directly. It is the DAMM equivalent of DAH1's input replay. */
import fs from "node:fs";
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const args = process.argv.slice(2);
const option = (name, fallback) => args.includes(name) ? args[args.indexOf(name) + 1] : fallback;
const port = Number(option("--port", "1265"));
const out = option("--out");
const action = option("--action", "a").toLowerCase();
if (!out || fs.existsSync(out)) throw new Error("--out must name a new JSON file");
if (!["a", "b", "start", "up", "down", "left", "right"].includes(action)) throw new Error("invalid --action");
const entry = 0x001DAB1C;
const expectedPrefix = "535633dbff15b4121e00";

const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => {
  socket.once("connect", resolve);
  socket.once("error", reject);
});
socket.setNoDelay(true);
const rsp = new RspClient(socket);
let armed = false, running = false;

async function read(address, length) {
  const reply = await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
  if (!/^[0-9a-f]+$/i.test(reply) || reply.length !== length * 2)
    throw new Error(`guest read failed address=0x${address.toString(16)} length=${length} reply=${JSON.stringify(reply)}`);
  return Buffer.from(reply, "hex");
}
async function write(address, bytes) {
  const reply = await rsp.packet(`M${address.toString(16)},${bytes.length.toString(16)}:${bytes.toString("hex")}`);
  if (reply !== "OK") throw new Error(`guest controller-result write failed: ${reply}`);
}

try {
  let supported = "";
  for (let attempt = 0; attempt < 4 && !supported.includes("PacketSize"); ++attempt)
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (!supported.includes("PacketSize")) throw new Error(`GDB handshake failed: ${supported}`);
  await rsp.halt();
  const code = await read(entry, 10);
  if (code.toString("hex") !== expectedPrefix) throw new Error(`unexpected DAMM XInputGetState bytes: ${code.toString("hex")}`);
  if (await rsp.packet(`Z1,${entry.toString(16)},1`) !== "OK") throw new Error("hardware breakpoint rejected");
  armed = true;
  rsp.resume();
  running = true;
  const stop = await rsp.nextPacket(30000);
  running = false;
  if (!/^[STW]/.test(stop)) throw new Error(`unexpected stop: ${stop}`);
  const registersReply = await rsp.packet("g");
  if (!/^[0-9a-f]+$/i.test(registersReply)) throw new Error("register read failed");
  const registers = Buffer.from(registersReply, "hex");
  const eip = registers.readUInt32LE(8 * 4);
  const esp = registers.readUInt32LE(4 * 4);
  if (eip !== entry) throw new Error(`unexpected breakpoint PC 0x${eip.toString(16)}`);
  const stack = await read(esp, 12);
  const returnAddress = stack.readUInt32LE(0);
  const handle = stack.readUInt32LE(4);
  const stateAddress = stack.readUInt32LE(8);
  const lowRam = stateAddress >= 0x10000 && stateAddress <= 0x07ffffe9;
  const mappedAlias = stateAddress >= 0x80010000 && stateAddress <= 0xffffffe9;
  if ((!lowRam && !mappedAlias) || (stateAddress & 3)) {
    throw new Error(`invalid XInput state pointer 0x${stateAddress.toString(16)} at ESP 0x${esp.toString(16)} stack=${stack.toString("hex")}`);
  }

  const state = Buffer.alloc(22);
  state.writeUInt32LE(1, 0); // packet number
  const digital = { up: 0x0001, down: 0x0002, left: 0x0004, right: 0x0008, start: 0x0010 };
  if (action in digital) state.writeUInt16LE(digital[action], 4);
  if (action === "a") state[6] = 255;
  if (action === "b") state[7] = 255;
  await write(stateAddress, state);
  if (await rsp.packet(`z1,${entry.toString(16)},1`) !== "OK") throw new Error("hardware breakpoint removal failed");
  armed = false;
  registers.writeUInt32LE(0, 0);                  // ERROR_SUCCESS
  registers.writeUInt32LE((esp + 12) >>> 0, 4 * 4); // stdcall ret 8
  registers.writeUInt32LE(returnAddress, 8 * 4);
  if (await rsp.packet(`G${registers.toString("hex")}`) !== "OK") throw new Error("register write failed");
  const result = {
    schema: 1, source: "xemu-logical-pad", boundary: "DAMM XInputGetState 0x001DAB1C",
    action, value: 255, handle, stateAddress, returnAddress,
    directGameStateWrites: false, timingPerturbed: true, observedAt: new Date().toISOString()
  };
  fs.writeFileSync(out, JSON.stringify(result, null, 2) + "\n", { flag: "wx" });
  console.log(JSON.stringify(result));
  rsp.resume();
  running = true;
  await new Promise(resolve => setTimeout(resolve, 50));
} finally {
  if (!running && armed) {
    try { await rsp.packet(`z1,${entry.toString(16)},1`); } catch {}
  }
  if (!running) rsp.resume();
  socket.destroy();
}
