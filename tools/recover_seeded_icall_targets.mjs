import { spawnSync } from "node:child_process";
import fs from "node:fs";
import path from "node:path";

const workRoot = process.cwd();
const xboxrecompRoot = path.resolve(workRoot, "..", "..", "repos", "Repos", "xboxrecomp");
const xbe = path.join(workRoot, "game_files", "default.xbe");
const disasm = path.join(workRoot, "analysis", "disasm_seeded");
const identified = path.join(workRoot, "analysis", "func_id", "identified_functions.json");
const output = path.join(workRoot, "src", "game", "recomp_vtable_generated.c");
const addresses = [
  "0x00013A50",
  "0x000125E0",
  "0x00030600",
  "0x000304B0",
  "0x000304C0",
  "0x00030670",
  "0x000306A0",
  "0x00031570",
  "0x000336A0",
  "0x00033720",
  "0x00037B80",
  "0x000386A0",
  "0x0003EE90",
  "0x0003EDE0",
  "0x0003F320",
  "0x000688D0",
  "0x00068AE0",
  "0x00073870",
  "0x000BAF80",
  "0x000E2390",
  "0x000DBA30",
  "0x000DA450",
  "0x000DBA98",
  "0x000DBAC2",
  "0x000DBAEB",
  "0x000DBB24",
  "0x000DBB91",
  "0x000DD4D0",
  "0x000DD430",
  "0x000DFB90",
  "0x000DFE70",
  "0x000DEB80",
  "0x000DE5C0",
  "0x000EA980",
  "0x000EA1B0",
  "0x000E9E00",
  "0x000E9E90",
  "0x000EA9A0",
  "0x000E9DE0",
  "0x000E9DF0",
  "0x000EAC60",
  "0x000EF2F0",
  "0x000EF780",
  "0x000F0210",
  "0x000F2B40",
  "0x000DFB60",
  "0x000E0430",
  "0x000E0860",
  "0x000EA9D0",
  "0x000EAAA0",
  "0x000ECCA0",
  "0x001023E0",
  "0x0010C760",
  "0x00102AE0",
  "0x00103340",
  "0x00109D50",
  "0x0010ED00",
  "0x0010F317",
  "0x0011F1C0",
  "0x0011F530",
  "0x0011EEF0",
  "0x00129750",
  "0x00129798",
  "0x0012979A",
  "0x0012983E",
  "0x00129860",
  "0x0012A190",
  "0x0012A1A0",
  "0x0012A200",
  "0x0012A218",
  "0x0012A246",
  "0x00154BFD",
  "0x00155132",
  "0x00155159",
  "0x00155176",
  "0x001552F5",
  "0x0015533C",
  "0x001553F1",
  "0x00155489",
  "0x0015598E",
  "0x00159900",
  "0x00159EE5",
  "0x00159E00",
  "0x0015A130",
  "0x001A3AB7",
  "0x001A3D84",
  "0x001AA633",
  "0x001AA6E3",
  "0x001AA710",
  "0x001AA832",
  "0x001AA738",
  "0x001AA831",
  "0x001AA87D",
  "0x001AA880",
  "0x001AA885",
  "0x001B13CB",
  "0x001B1573",
  "0x001B157F",
  "0x001B1584",
  "0x001B1589",
  "0x001B158E",
  "0x001B1593",
  "0x001B1598",
  "0x001B159D",
  "0x001B15A2",
  "0x001B15A7",
  "0x001B15AC",
  "0x001B15B1",
  "0x001B15B6",
  "0x001B15BB",
  "0x001B15C0",
  "0x001B15C5",
  "0x001B1AF4",
  "0x001B1B2D",
  "0x001B1B75",
  "0x001B1B86",
  "0x001B1B89",
];

let destination = fs.readFileSync(output, "utf8");
const recovered = [];

for (const address of addresses) {
  const symbol = `sub_${address.slice(2)}`;
  if (destination.includes(`void ${symbol}(void)`)) {
    process.stdout.write(`already present: ${symbol}\n`);
    continue;
  }

  const args = [
    "-m", "tools.recomp", xbe,
    /* The identified superset includes vtable entry points which were absent
     * from the original direct-call seed list. */
    "--functions", identified,
    "--labels", path.join(disasm, "labels.json"),
    "--identified", identified,
    "--abi", path.join(workRoot, "analysis", "abi", "abi_functions.json"),
    "--skip-binary-check", "-f", address,
  ];
  const result = spawnSync("python", args, {
    cwd: xboxrecompRoot,
    encoding: "utf8",
    maxBuffer: 16 * 1024 * 1024,
  });
  if (result.status !== 0) {
    process.stderr.write(`skipped ${address}: ${result.stderr || result.stdout}\n`);
    continue;
  }
  const start = result.stdout.indexOf("/**");
  if (start < 0 || !result.stdout.includes(`void ${symbol}(void)`)) {
    throw new Error(`recompiler did not emit ${symbol}`);
  }
  recovered.push(result.stdout.slice(start).trimEnd());
  process.stdout.write(`recovered: ${symbol}\n`);
}

if (recovered.length > 0) {
  destination = destination.trimEnd() + "\n\n" + recovered.join("\n\n") + "\n";
  fs.writeFileSync(output, destination, "utf8");
}
