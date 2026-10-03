import fs from "node:fs";
import path from "node:path";

const workRoot = process.cwd();
const recoveryDir = path.join(workRoot, "analysis", "recovery_gen");
const destinationPath = path.join(workRoot, "src", "game", "recomp_vtable_generated.c");
const damagedPaths = [
  path.join(workRoot, "analysis", "gen_staged", "recomp_0000.c"),
  path.join(workRoot, "src", "game", "recomp", "gen", "recomp_0000.c"),
];
const rangeStart = 0x000412F0;
const rangeEnd = 0x000446B0;

for (const damagedPath of damagedPaths) {
  let source = fs.readFileSync(damagedPath, "utf8");
  if (source.includes("#if 0 /* Corrupt preserved region 000412F0-000446AF")) {
    process.stdout.write(`already disabled: ${damagedPath}\n`);
    continue;
  }
  const startMarker = "/**\r\n * sub_000412F0";
  const nextMarker = "/**\r\n * sub_000446B0";
  const start = source.indexOf(startMarker);
  const next = source.indexOf(nextMarker, start + startMarker.length);
  if (start < 0 || next < 0) {
    throw new Error(`damaged region markers not found in ${damagedPath}`);
  }
  source =
    source.slice(0, start) +
    "#if 0 /* Corrupt preserved region 000412F0-000446AF; exact bodies live in recomp_vtable_generated.c. */\r\n" +
    source.slice(start, next) +
    "#endif\r\n\r\n" +
    source.slice(next);
  fs.writeFileSync(damagedPath, source, "utf8");
  process.stdout.write(`disabled damaged region: ${damagedPath}\n`);
}

const functions = JSON.parse(fs.readFileSync(
  path.join(workRoot, "analysis", "disasm", "functions.json"), "utf8"));
const targets = functions
  .map((entry) => Number.parseInt(entry.start, 16))
  .filter((address) => address >= rangeStart && address < rangeEnd)
  .sort((a, b) => a - b)
  .map((address) => `sub_${address.toString(16).toUpperCase().padStart(8, "0")}`);

const sourceFiles = fs.readdirSync(recoveryDir)
  .filter((name) => /^recomp_\d+\.c$/.test(name))
  .sort()
  .map((name) => fs.readFileSync(path.join(recoveryDir, name), "utf8"));

function extractFunction(text, name) {
  const signature = `void ${name}(void)`;
  const start = text.indexOf(signature);
  if (start < 0) return null;
  const open = text.indexOf("{", start + signature.length);
  if (open < 0) throw new Error(`missing opening brace for ${name}`);

  let depth = 0;
  let state = "code";
  for (let index = open; index < text.length; ++index) {
    const ch = text[index];
    const next = text[index + 1] ?? "";
    if (state === "line-comment") {
      if (ch === "\n") state = "code";
      continue;
    }
    if (state === "block-comment") {
      if (ch === "*" && next === "/") { state = "code"; ++index; }
      continue;
    }
    if (state === "string" || state === "character") {
      if (ch === "\\") { ++index; continue; }
      if ((state === "string" && ch === "\"") ||
          (state === "character" && ch === "'")) state = "code";
      continue;
    }
    if (ch === "/" && next === "/") { state = "line-comment"; ++index; continue; }
    if (ch === "/" && next === "*") { state = "block-comment"; ++index; continue; }
    if (ch === "\"") { state = "string"; continue; }
    if (ch === "'") { state = "character"; continue; }
    if (ch === "{") ++depth;
    if (ch === "}" && --depth === 0) return text.slice(start, index + 1);
  }
  throw new Error(`unterminated body for ${name}`);
}

let destination = fs.readFileSync(destinationPath, "utf8");
const bodies = [];
for (const target of targets) {
  if (destination.includes(`void ${target}(void)`)) continue;
  let body = null;
  for (const source of sourceFiles) {
    body = extractFunction(source, target);
    if (body) break;
  }
  if (!body) throw new Error(`generated body not found: ${target}`);
  bodies.push(body);
}
if (bodies.length > 0) {
  destination = destination.trimEnd() + "\n\n" + bodies.join("\n\n") + "\n";
  fs.writeFileSync(destinationPath, destination, "utf8");
}
process.stdout.write(`recovered ${bodies.length}/${targets.length} functions from damaged region\n`);
