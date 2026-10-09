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
  // MainMenu's primary per-frame/update and navigation-event callbacks.
  // These are live vtable targets in the retail 0x001F89C0 table; leaving
  // either one unresolved makes the menu draw while ignoring controller input.
  0x000FA480, 0x000FA890, 0x00100450,
  // Retail Press Start/profile path, previously bypassed by the PC bring-up.
  0x0001C4A0, 0x0005E9A0, 0x00102390, 0x000EF100,
  0x000E9A80,
  // Frontend scene listener reached while the post-movie controller builds
  // its first presentation bundle.  Without it the async tail never emits
  // raw event 7, leaving the last startup frame held indefinitely.
  0x000E9E60,
  // Title-screen scene callbacks reached only when startup pushbuffers are
  // consumed continuously behind the movie overlay.  Omitting these leaves
  // the real PRESS START text over a cleared black render target.
  0x000E4820, 0x000E48C3, 0x000E48E7, 0x000F1070,
  0x000F0C30, 0x000E7340, 0x000E78E0,
  // World-loader callback reached once the title attract descriptor selects
  // a real city archive instead of the former empty ".zip" path.
  0x0003EF60, 0x000DE160, 0x000BB190, 0x0008B050,
  0x0007E880, 0x000C1DD0,
  0x001B15C0,
  // Profile/player-select event callback.  Retail installs this function in
  // the active listener table; without it the menu bus retries the event
  // forever and impatient Start/A input cannot advance to MainMenu.
  0x000E4730,
  // Thin retail event-listener thunk (jmp 0x00033F40) installed by the
  // profile/menu transition.  Missing it leaves the commit event queued.
  0x000141E0,
  0x00033F40,
  0x000154B0, 0x00034570, 0x00015040,
  // Boolean menu-event callback reached when a submenu is opened and
  // immediately cancelled.  Retail returns true and pops two arguments.
  0x00018E50,
  // Presentation/menu event callback reached when the active frontend screen
  // accepts Start/A.  This is a real vtable target at 0x001F7E1C; omitting it
  // silently discards the profile-screen accept event.
  0x000EF0A0,
  0x0004FA20, 0x00050B70, 0x00055BF0, 0x00059470,
  0x0005ECD0, 0x0005FBA0, 0x00060CB0, 0x00062310,
  0x00063260, 0x00063C50, 0x00064720, 0x00064BF0,
  0x00064DC0, 0x000653B0,
  0x0004F750, 0x00050200, 0x000604D0, 0x000608D0,
  0x00063EB0, 0x000643E0,
  // XONLINE installs three paired callback tables during frontend startup.
  // The original detector found the first member of each pair but treated
  // the second as padding, leaving live calls through 0x0018C45D unresolved.
  0x0018EF0D, 0x0019110C, 0x00197EE9,
  // Tail-dispatch continuation selected by the archive/parser state machine.
  // This is entered with the parent function's register frame intact.
  0x0007253D, 0x000725B3, 0x0007261E, 0x00072688,
  0x000726BC, 0x000726F2, 0x00072728, 0x00072765,
  0x0007276B, 0x00072784, 0x00072795, 0x000727C5,
  0x000727F7, 0x00072821, 0x0007285E, 0x00072883,
  0x0007288C, 0x00072897,
  0x00072C55,
  0x00073340, 0x00073358,
  0x00072C09, 0x00072C1C, 0x00072C46,
  0x00072CB4,
  0x00072D35,
  0x000734A7, 0x000733CF, 0x00072ECA,
  0x00073890, 0x0010ED60,
  // DSOUND/XPP callbacks reached from worker threads and early static
  // initialization. Several are packed directly after another function and
  // therefore need explicit seeds instead of ordinary prologue discovery.
  0x0015CF52, 0x0015D0AB,
  0x001D9B1C, 0x001D9C28, 0x001DA52D, 0x001DAEB2, 0x001DCF6C,
];
const symbol = (address) =>
  `sub_${address.toString(16).toUpperCase().padStart(8, "0")}`;

const bodyPath = path.join(root, "src", "game", "recomp_vtable_generated.c");
let bodies = fs.readFileSync(bodyPath, "utf8");
const manualBodies = fs.readFileSync(path.join(root, "src", "game", "recomp_manual.c"), "utf8");
const generatedHeader = fs.readFileSync(
  path.join(root, "src", "game", "recomp", "gen", "recomp_funcs.h"),
  "utf8",
);
const recovered = [];
for (const address of targets) {
  const name = symbol(address);
  if (
    bodies.includes(`void ${name}(void)`) ||
    manualBodies.includes(`void ${name}(void)`) ||
    generatedHeader.includes(`void ${name}(void);`)
  ) continue;
  const hex = `0x${address.toString(16).toUpperCase().padStart(8, "0")}`;
  const fragment = address === 0x0005E9A0;
  const args = [
    "-m", "tools.recomp", xbe,
    "--functions", fragment
      ? path.join(root, "analysis", "press_start_functions.json")
      : path.join(disasm, "functions.json"),
    "--labels", fragment
      ? path.join(root, "analysis", "press_start_labels.json")
      : path.join(disasm, "labels.json"),
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
  const body = result.stdout.slice(start).trimEnd();
  recovered.push(body);
  bodies = bodies.trimEnd() + "\n\n" + body + "\n";
  fs.writeFileSync(bodyPath, bodies, "utf8");
  process.stdout.write(`recovered ${name}\n`);
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
