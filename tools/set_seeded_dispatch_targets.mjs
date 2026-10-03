import fs from "node:fs";

const allTargets = [
  0x000125E0, 0x00013A50, 0x000304B0, 0x000304C0, 0x00030600, 0x00030670,
  0x000306A0, 0x00031570,
  0x000336A0, 0x00033720, 0x00037B80, 0x000386A0, 0x000DBA30,
  0x000DBA98, 0x000DBAC2, 0x000DBAEB, 0x000DBB24, 0x000DBB91,
  0x000DBBFA, 0x000DD4D0, 0x000DFB90, 0x000DEB80, 0x000E9E00, 0x000E9E90, 0x000EA1B0,
  0x000EA9A0, 0x001023E0, 0x00103340, 0x00109D50, 0x0010ED00,
  0x0010F317, 0x0011EEF0, 0x0011F1C0, 0x0011F530, 0x00129750, 0x00129798, 0x0012979A,
  0x0012983E, 0x00129860, 0x0012A190, 0x0012A1A0, 0x0012A200, 0x0012A218,
  0x0012A246, 0x00154BFD, 0x00155132, 0x00155159, 0x00155176,
  0x001552F5, 0x0015533C, 0x001553F1, 0x00155489, 0x0015598E, 0x00159900, 0x00159E00, 0x00159EE5, 0x0015A130,
  0x001A3AB7, 0x001A3D84, 0x001AA633, 0x001AA6E3,
  0x001AA710, 0x001AA738, 0x001AA831, 0x001AA832, 0x001AA87D,
  0x001AA880, 0x001AA885, 0x001B13CB, 0x001B1573, 0x001B157F,
  0x001B1584, 0x001B1589, 0x001B158E, 0x001B1593, 0x001B1598,
  0x001B159D, 0x001B15A2, 0x001B15A7, 0x001B15AC, 0x001B15B1,
  0x001B15B6, 0x001B15BB, 0x001B15C0, 0x001B15C5, 0x001B1AF4,
  0x001B1B2D, 0x001B1B75, 0x001B1B86,
  0x001B1B89,
];
const presets = {
  core: [
    0x00013A50, 0x000304B0, 0x000304C0, 0x00030670, 0x00031570, 0x000336A0,
    0x00033720, 0x000DBA30, 0x000DBA98,
    0x000DBAC2, 0x000DBAEB, 0x000DBB24, 0x000DBB91, 0x000DBBFA,
    0x000DD4D0, 0x000DFB90,
    0x000DEB80, 0x000E9E00, 0x000E9E90, 0x000EA1B0, 0x000EA9A0,
    0x001023E0, 0x00103340, 0x00109D50, 0x0010ED00, 0x0010F317,
    0x0011F1C0, 0x0011F530, 0x00129750, 0x00129798, 0x0012979A, 0x0012983E,
    0x00129860, 0x0012A190, 0x0012A1A0, 0x0012A200, 0x0012A218, 0x0012A246,
    0x00154BFD, 0x00155132, 0x00155159, 0x00155176, 0x001552F5,
    0x0015533C, 0x00155489, 0x0015598E, 0x00159900, 0x00159EE5, 0x0015A130, 0x001A3AB7,
    0x001A3D84, 0x001AA633, 0x001AA6E3,
    0x001AA710, 0x001AA738, 0x001AA831, 0x001AA832, 0x001AA87D,
    0x001AA880, 0x001AA885, 0x001B13CB, 0x001B1573, 0x001B157F,
    0x001B1584, 0x001B1589, 0x001B158E, 0x001B1593, 0x001B1598,
    0x001B159D, 0x001B15A2, 0x001B15A7, 0x001B15AC, 0x001B15B1,
    0x001B15B6, 0x001B15BB, 0x001B15C0, 0x001B15C5,
    0x001B1AF4, 0x001B1B2D, 0x001B1B75, 0x001B1B86, 0x001B1B89,
  ],
  constructors: [0x000336A0, 0x00033720],
  add_only: [0x000336A0],
  remove_only: [0x00033720],
  all: allTargets,
  none: [],
};
const preset = process.argv[2] ?? "core";
if (!(preset in presets)) throw new Error(`unknown preset: ${preset}`);
const enabled = new Set(presets[preset]);
const symbol = (address) => `sub_${address.toString(16).toUpperCase().padStart(8, "0")}`;

const path = "src/game/recomp/gen/recomp_dispatch.c";
let source = fs.readFileSync(path, "utf8");
for (const address of allTargets) {
  const addressText = address.toString(16).toUpperCase().padStart(8, "0");
  const line = `    { 0x${addressText}u, (recomp_func_t)${symbol(address)} },\r\n`;
  source = source.replace(line, "");
}

for (const address of [...enabled].sort((a, b) => a - b)) {
  const addressText = address.toString(16).toUpperCase().padStart(8, "0");
  const line = `    { 0x${addressText}u, (recomp_func_t)${symbol(address)} },\r\n`;
  const pattern = /^    \{ 0x([0-9A-F]{8})u, \(recomp_func_t\)sub_[0-9A-F]{8} \},\r?$/gm;
  let match;
  let insertion = -1;
  while ((match = pattern.exec(source)) !== null) {
    if (Number.parseInt(match[1], 16) > address) {
      insertion = match.index;
      break;
    }
  }
  if (insertion < 0) throw new Error(`insertion point missing for ${symbol(address)}`);
  source = source.slice(0, insertion) + line + source.slice(insertion);
}

fs.writeFileSync(path, source);
console.log(`enabled seeded dispatch preset '${preset}' (${enabled.size} targets)`);
