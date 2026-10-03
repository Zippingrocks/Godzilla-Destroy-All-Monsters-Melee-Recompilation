import fs from "node:fs";

const targets = [
  0x00013A50,
  0x000125E0,
  0x00030600,
  0x000304B0,
  0x000304C0,
  0x00030670,
  0x000306A0,
  0x00031570,
  0x000336A0,
  0x00033720,
  0x00037B80,
  0x000386A0,
  0x000DBA30,
  0x000DBA98,
  0x000DBAC2,
  0x000DBAEB,
  0x000DBB24,
  0x000DBB91,
  0x000DD4D0,
  0x000DFB90,
  0x000DBBFA,
  0x000DEB80,
  0x000EA1B0,
  0x000E9E00,
  0x000E9E90,
  0x000EA9A0,
  0x001023E0,
  0x00103340,
  0x00109D50,
  0x0010ED00,
  0x0010F317,
  0x0011F1C0,
  0x0011F530,
  0x0011EEF0,
  0x00129750,
  0x00129798,
  0x0012979A,
  0x0012983E,
  0x00129860,
  0x0012A190,
  0x0012A1A0,
  0x0012A200,
  0x0012A218,
  0x0012A246,
  0x00154BFD,
  0x00155132,
  0x00155159,
  0x00155176,
  0x001552F5,
  0x0015533C,
  0x001553F1,
  0x00155489,
  0x0015598E,
  0x00159900,
  0x00159EE5,
  0x00159E00,
  0x0015A130,
  0x001A3AB7,
  0x001A3D84,
  0x001AA633,
  0x001AA6E3,
  0x001AA710,
  0x001AA832,
  0x001AA738,
  0x001AA831,
  0x001AA87D,
  0x001AA880,
  0x001AA885,
  0x001B13CB,
  0x001B1573,
  0x001B157F,
  0x001B1584,
  0x001B1589,
  0x001B158E,
  0x001B1593,
  0x001B1598,
  0x001B159D,
  0x001B15A2,
  0x001B15A7,
  0x001B15AC,
  0x001B15B1,
  0x001B15B6,
  0x001B15BB,
  0x001B15C0,
  0x001B15C5,
  0x001B1AF4,
  0x001B1B2D,
  0x001B1B75,
  0x001B1B86,
  0x001B1B89,
];

const symbol = (address) => `sub_${address.toString(16).toUpperCase().padStart(8, "0")}`;

const headerPath = "src/game/recomp/gen/recomp_funcs.h";
let header = fs.readFileSync(headerPath, "utf8");
const newPrototypes = targets
  .filter((address) => !header.includes(`void ${symbol(address)}(void);`))
  .map((address) => `void ${symbol(address)}(void);`);
if (newPrototypes.length) {
  const marker = "\r\n/* Unresolved call targets (stubbed) */";
  if (!header.includes(marker)) throw new Error("header insertion marker not found");
  header = header.replace(marker, `\r\n${newPrototypes.join("\r\n")}\r\n${marker}`);
  fs.writeFileSync(headerPath, header);
}

const dispatchPath = "src/game/recomp/gen/recomp_dispatch.c";
let dispatch = fs.readFileSync(dispatchPath, "utf8");
for (const address of targets) {
  const name = symbol(address);
  const addressText = address.toString(16).toUpperCase().padStart(8, "0");
  if (dispatch.includes(`(recomp_func_t)${name} }`)) continue;
  const entry = `    { 0x${addressText}u, (recomp_func_t)${name} },\r\n`;
  const entryPattern = /^    \{ 0x([0-9A-F]{8})u, \(recomp_func_t\)sub_[0-9A-F]{8} \},\r?$/gm;
  let match;
  let insertion = -1;
  while ((match = entryPattern.exec(dispatch)) !== null) {
    if (Number.parseInt(match[1], 16) > address) {
      insertion = match.index;
      break;
    }
  }
  if (insertion < 0) throw new Error(`sorted insertion point not found for ${name}`);
  dispatch = dispatch.slice(0, insertion) + entry + dispatch.slice(insertion);
}
fs.writeFileSync(dispatchPath, dispatch);

console.log(`registered ${targets.length} seeded indirect-call targets`);
