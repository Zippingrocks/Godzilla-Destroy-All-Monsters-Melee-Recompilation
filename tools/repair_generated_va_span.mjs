import fs from "node:fs";

function fail(message) {
  process.stderr.write(`${message}\n`);
  process.exit(1);
}

const [targetPath, donorPath, dispatchPath, startText, endText, mode] =
  process.argv.slice(2);

if (!targetPath || !donorPath || !dispatchPath || !startText || !endText) {
  fail(
    "usage: node repair_generated_va_span.mjs <target.c> <donor.c> " +
      "<dispatch.c> <start-va> <end-va-exclusive> [--write]",
  );
}

const startVa = Number.parseInt(startText, 0);
const endVa = Number.parseInt(endText, 0);
if (!Number.isInteger(startVa) || !Number.isInteger(endVa) || startVa >= endVa)
  fail("invalid VA span");

const target = fs.readFileSync(targetPath, "utf8");
const donor = fs.readFileSync(donorPath, "utf8");
const dispatch = fs.readFileSync(dispatchPath, "utf8");

function marker(va) {
  return new RegExp(
    `^/\\*\\*\\r?\\n \\* sub_${va.toString(16).toUpperCase().padStart(8, "0")}\\r?$`,
    "m",
  );
}

function findMarker(text, va) {
  const match = marker(va).exec(text);
  if (!match) fail(`missing function marker for 0x${va.toString(16)}`);
  return match.index;
}

function parseBlocks(text) {
  const starts = [];
  const re = /^\/\*\*\r?\n \* (sub_([0-9A-F]{8}))\r?$/gm;
  for (let match; (match = re.exec(text)); ) {
    starts.push({ name: match[1], va: Number.parseInt(match[2], 16), start: match.index });
  }

  const blocks = new Map();
  for (let i = 0; i < starts.length; i += 1) {
    const item = starts[i];
    const end = i + 1 < starts.length ? starts[i + 1].start : text.length;
    blocks.set(item.name, { ...item, text: text.slice(item.start, end).trimEnd() + "\n\n" });
  }
  return blocks;
}

const targetStart = findMarker(target, startVa);
const targetEnd = findMarker(target, endVa);
if (targetStart >= targetEnd) fail("target markers are out of order");

const targetSpan = target.slice(targetStart, targetEnd);
const targetBlocks = parseBlocks(targetSpan);
const donorBlocks = parseBlocks(donor);
const wanted = new Map();

for (const block of targetBlocks.values()) {
  if (block.va >= startVa && block.va < endVa)
    wanted.set(block.name, block.va);
}

const dispatchRe = /\{\s*0x([0-9A-F]{8})u,\s*\(recomp_func_t\)(sub_[0-9A-F]{8})\s*\}/g;
for (let match; (match = dispatchRe.exec(dispatch)); ) {
  const va = Number.parseInt(match[1], 16);
  if (va >= startVa && va < endVa) wanted.set(match[2], va);
}

const missing = [...wanted]
  .filter(([name]) => !donorBlocks.has(name))
  .map(([name]) => name);
if (missing.length)
  fail(`donor is missing ${missing.length} required function(s): ${missing.join(", ")}`);

const ordered = [...wanted]
  .map(([name, va]) => ({ name, va, block: donorBlocks.get(name).text }))
  .sort((a, b) => a.va - b.va);

for (let i = 1; i < ordered.length; i += 1) {
  if (ordered[i - 1].va === ordered[i].va)
    fail(`duplicate VA 0x${ordered[i].va.toString(16)}`);
}

const replacement = ordered.map((item) => item.block).join("");
const repaired = target.slice(0, targetStart) + replacement + target.slice(targetEnd);
const report = {
  startVa: `0x${startVa.toString(16).toUpperCase()}`,
  endVaExclusive: `0x${endVa.toString(16).toUpperCase()}`,
  originalBytes: targetEnd - targetStart,
  replacementBytes: replacement.length,
  originalNamedFunctions: targetBlocks.size,
  repairedFunctions: ordered.length,
  addedFromDispatch: ordered.length - targetBlocks.size,
  write: mode === "--write",
};

if (mode === "--write") fs.writeFileSync(targetPath, repaired, "utf8");
process.stdout.write(`${JSON.stringify(report)}\n`);
