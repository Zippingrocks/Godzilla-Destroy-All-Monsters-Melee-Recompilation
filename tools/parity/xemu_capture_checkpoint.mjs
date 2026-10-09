import net from "node:net";
import fs from "node:fs";

const argv = process.argv.slice(2);
const option = (name, fallback) => argv.includes(name) ? argv[argv.indexOf(name) + 1] : fallback;
const port = Number(option("--port", "4475"));
const out = option("--out");
if (!out || fs.existsSync(out)) throw new Error("--out must name a new metadata file");

const socket = net.createConnection({ host: "127.0.0.1", port });
socket.setEncoding("utf8");
let buffer = "", serial = 0, greetingResolve;
const pending = new Map();
const greeting = new Promise(resolve => { greetingResolve = resolve; });
socket.on("data", chunk => {
  buffer += chunk;
  for (;;) {
    const end = buffer.indexOf("\n");
    if (end < 0) break;
    const line = buffer.slice(0, end).trim();
    buffer = buffer.slice(end + 1);
    if (!line) continue;
    const value = JSON.parse(line);
    if (value.QMP) greetingResolve(value);
    if (value.id && pending.has(value.id)) {
      const request = pending.get(value.id);
      pending.delete(value.id);
      clearTimeout(request.timer);
      value.error ? request.reject(new Error(JSON.stringify(value.error))) : request.resolve(value.return);
    }
  }
});
socket.on("error", error => {
  for (const request of pending.values()) request.reject(error);
  pending.clear();
});
await new Promise((resolve, reject) => {
  const timer = setTimeout(() => reject(new Error("connect timeout")), 5000);
  socket.once("connect", () => { clearTimeout(timer); resolve(); });
  socket.once("error", reject);
});
await greeting;

function command(execute, args) {
  const id = ++serial;
  return new Promise((resolve, reject) => {
    const timer = setTimeout(() => { pending.delete(id); reject(new Error(`${execute} timed out`)); }, 20000);
    pending.set(id, { resolve, reject, timer });
    socket.write(JSON.stringify({ execute, arguments: args, id }) + "\n");
  });
}

let stopped = false;
try {
  await command("qmp_capabilities");
  const status = await command("query-status");
  if (!status.running) throw new Error("reference must be running; paused savevm can deadlock this Xemu build");
  const snapshot = `damm-parity-${Date.now()}`;
  const saved = await command("human-monitor-command", { "command-line": `savevm ${snapshot}` });
  if (saved.trim()) throw new Error(`savevm: ${saved}`);
  await command("stop");
  stopped = true;
  const registers = await command("human-monitor-command", { "command-line": "info registers" });
  const scanout = await command("human-monitor-command", { "command-line": "xp /1wx 0xfd600800" });
  const cr3 = /CR3=([0-9a-f]+)/i.exec(registers);
  const start = /: 0x([0-9a-f]+)/i.exec(scanout);
  if (!cr3 || !start) throw new Error("could not decode CR3/PCRTC_START");
  const metadata = {
    schema: 1, source: "xemu", imageStage: "raw-scanout-before-pvideo-dac-gamma-and-ui-scaling",
    capturedAt: new Date().toISOString(), snapshot, port,
    cr3: parseInt(cr3[1], 16), pcrtcStart: parseInt(start[1], 16), registers,
    timingVerified: false,
    note: "savevm flushes GPU surfaces while running, then stop pauses the CPU. These are not one atomic frame boundary."
  };
  fs.writeFileSync(out, JSON.stringify(metadata, null, 2) + "\n", { flag: "wx" });
  console.log(JSON.stringify({ out, snapshot, cr3: metadata.cr3, pcrtcStart: metadata.pcrtcStart, paused: true }));
  stopped = false;
} finally {
  if (stopped) await command("cont").catch(() => {});
  socket.destroy();
}
