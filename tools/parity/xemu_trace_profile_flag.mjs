#!/usr/bin/env node
import net from "node:net";
import { RspClient } from "./rsp_client.mjs";

const port = Number(process.argv.includes("--port") ?
  process.argv[process.argv.indexOf("--port") + 1] : "1265");
const inputEntry = 0x001DAB1C;
const flagAddress = 0x002C2AF0;
const socket = net.createConnection({ host: "127.0.0.1", port });
await new Promise((resolve, reject) => {
  socket.once("connect", resolve); socket.once("error", reject);
});
socket.setNoDelay(true);
const rsp = new RspClient(socket);
let running = false, inputBreak = false, watchBreak = false;

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
  for (let i = 0; i < 4 && !supported.includes("PacketSize"); ++i)
    supported = await rsp.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  await rsp.halt();
  if (await rsp.packet(`Z1,${inputEntry.toString(16)},1`) !== "OK")
    throw new Error("input breakpoint rejected");
  inputBreak = true;
  rsp.resume(); running = true;
  await rsp.nextPacket(30000); running = false;
  let registers = Buffer.from(await rsp.packet("g"), "hex");
  const esp = registers.readUInt32LE(4 * 4);
  const stack = await read(esp, 12);
  const stateAddress = stack.readUInt32LE(8);
  const state = Buffer.alloc(22);
  state.writeUInt32LE(1, 0); state[6] = 255;
  await write(stateAddress, state);
  await rsp.packet(`z1,${inputEntry.toString(16)},1`); inputBreak = false;
  // The main object consumes this as a byte, but the profile callback may
  // store a full dword.  Xemu/QEMU's x86 watchpoint matching is reliable when
  // the watched width matches that store, so cover the naturally aligned word.
  if (await rsp.packet(`Z2,${flagAddress.toString(16)},4`) !== "OK")
    throw new Error("write watchpoint rejected");
  watchBreak = true;
  registers.writeUInt32LE(0, 0);
  registers.writeUInt32LE((esp + 12) >>> 0, 4 * 4);
  registers.writeUInt32LE(stack.readUInt32LE(0), 8 * 4);
  if (await rsp.packet(`G${registers.toString("hex")}`) !== "OK")
    throw new Error("register write failed");
  rsp.resume(); running = true;
  const stop = await rsp.nextPacket(30000); running = false;
  if (!stop) throw new Error("profile flag watchpoint timed out");
  registers = Buffer.from(await rsp.packet("g"), "hex");
  const eip = registers.readUInt32LE(8 * 4);
  const hitEsp = registers.readUInt32LE(4 * 4);
  console.log(JSON.stringify({ stop, eip: `0x${eip.toString(16)}`,
    esp: `0x${hitEsp.toString(16)}`, flag: (await read(flagAddress, 1))[0],
    stack: (await read(hitEsp, 32)).toString("hex") }, null, 2));
} finally {
  if (running) { try { await rsp.halt(); } catch {} }
  if (inputBreak) { try { await rsp.packet(`z1,${inputEntry.toString(16)},1`); } catch {} }
  if (watchBreak) { try { await rsp.packet(`z2,${flagAddress.toString(16)},4`); } catch {} }
  rsp.resume(); socket.destroy();
}
