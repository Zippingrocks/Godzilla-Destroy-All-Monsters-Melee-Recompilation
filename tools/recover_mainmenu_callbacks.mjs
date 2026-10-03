import { spawnSync } from "node:child_process";
import fs from "node:fs";
import path from "node:path";

const root = process.cwd();
const recompRoot = path.resolve(root, "..", "..", "repos", "Repos", "xboxrecomp");
const xbe = path.join(root, "game_files", "default.xbe");
const disasm = path.join(root, "analysis", "disasm_menu");
const targets = [
  0x0010BC70, 0x000454C0, 0x000F9DC0, 0x00047D60,
  0x00045DA0, 0x00047DB0, 0x0003B4D0,
  0x000E07E0, 0x000E07F0, 0x000E0810, 0x000E0820,
  0x000E0FB0, 0x000DD250,
  0x00047BF0, 0x00047D10, 0x00047D20, 0x0003F320,
  0x0003EAB0, 0x0002E7C0,
];
const symbol = (address) =>
  `sub_${address.toString(16).toUpperCase().padStart(8, "0")}`;

const bodyPath = path.join(root, "src", "game", "recomp_vtable_generated.c");
let bodies = fs.readFileSync(bodyPath, "utf8");
const manualBodies = fs.readFileSync(path.join(root, "src", "game", "recomp_manual.c"), "utf8");
const recovered = [];
for (const address of targets) {
  const name = symbol(address);
  if (bodies.includes(`void ${name}(void)`) || manualBodies.includes(`void ${name}(void)`)) continue;
  const hex = `0x${address.toString(16).toUpperCase().padStart(8, "0")}`;
  const args = [
    "-m", "tools.recomp", xbe,
    "--functions", path.join(disasm, "functions.json"),
    "--labels", path.join(disasm, "labels.json"),
    "--identified", path.join(root, "analysis", "func_id", "identified_functions.json"),
    "--abi", path.join(root, "analysis", "abi", "abi_functions.json"),
    "--skip-binary-check", "-f", hex,
  ];
  const result = spawnSync("python", args, {
    cwd: recompRoot, encoding: "utf8", maxBuffer: 32 * 1024 * 1024,
  });
  if (result.status !== 0) {
    throw new Error(`failed to lift ${hex}: ${result.stderr || result.stdout}`);
  }
  const start = result.stdout.indexOf("/**");
  if (start < 0 || !result.stdout.includes(`void ${name}(void)`))
    throw new Error(`missing body for ${name}`);
  recovered.push(result.stdout.slice(start).trimEnd());
  process.stdout.write(`recovered ${name}\n`);
}
if (recovered.length) {
  bodies = bodies.trimEnd() + "\n\n" + recovered.join("\n\n") + "\n";
  fs.writeFileSync(bodyPath, bodies, "utf8");
}

const headerPath = path.join(root, "src", "game", "recomp", "gen", "recomp_funcs.h");
let header = fs.readFileSync(headerPath, "utf8");
const prototypes = targets
  .filter((address) => !header.includes(`void ${symbol(address)}(void);`))
  .map((address) => `void ${symbol(address)}(void);`);
if (prototypes.length) {
  const marker = "\r\n/* Unresolved call targets (stubbed) */";
  if (!header.includes(marker)) throw new Error("header marker missing");
  header = header.replace(marker, `\r\n${prototypes.join("\r\n")}\r\n${marker}`);
  fs.writeFileSync(headerPath, header, "utf8");
}

const dispatchPath = path.join(root, "src", "game", "recomp", "gen", "recomp_dispatch.c");
let dispatch = fs.readFileSync(dispatchPath, "utf8");
for (const address of targets) {
  const name = symbol(address);
  if (dispatch.includes(`(recomp_func_t)${name} }`)) continue;
  const addressText = address.toString(16).toUpperCase().padStart(8, "0");
  const entry = `    { 0x${addressText}u, (recomp_func_t)${name} },\r\n`;
  const pattern = /^    \{ 0x([0-9A-F]{8})u, \(recomp_func_t\)sub_[0-9A-F]{8} \},\r?$/gm;
  let match;
  let insertion = -1;
  while ((match = pattern.exec(dispatch)) !== null) {
    if (Number.parseInt(match[1], 16) > address) {
      insertion = match.index;
      break;
    }
  }
  if (insertion < 0) throw new Error(`dispatch insertion missing for ${name}`);
  dispatch = dispatch.slice(0, insertion) + entry + dispatch.slice(insertion);
}
fs.writeFileSync(dispatchPath, dispatch, "utf8");

console.log(`registered ${targets.length} MainMenu callbacks`);
