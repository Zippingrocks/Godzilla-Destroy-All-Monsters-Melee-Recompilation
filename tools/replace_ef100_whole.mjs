import { spawnSync } from "node:child_process";
import fs from "node:fs";
import path from "node:path";

const root = process.cwd();
const recompRoot = path.resolve(root, "..", "..", "repos", "Repos", "xboxrecomp");
const args = [
  "-m", "tools.recomp", path.join(root, "game_files", "default.xbe"),
  "--functions", path.join(root, "analysis", "ef100_functions.json"),
  "--labels", path.join(root, "analysis", "ef100_labels.json"),
  "--identified", path.join(root, "analysis", "func_id", "identified_functions.json"),
  "--abi", path.join(root, "analysis", "abi", "abi_functions.json"),
  "--skip-binary-check", "-f", "0x000EF100",
];
const result = spawnSync("python", args, {
  cwd: recompRoot, encoding: "utf8", maxBuffer: 16 * 1024 * 1024,
});
if (result.status !== 0) throw new Error(result.stderr || result.stdout);
const replacementStart = result.stdout.indexOf("/**");
if (replacementStart < 0) throw new Error("whole EF100 body missing");
const replacement = result.stdout.slice(replacementStart).trimEnd();

const sourcePath = path.join(root, "src", "game", "recomp_vtable_generated.c");
let source = fs.readFileSync(sourcePath, "utf8");
const namePosition = source.indexOf(" * sub_000EF100");
const start = namePosition < 0 ? -1 : source.lastIndexOf("/**", namePosition);
if (start < 0) throw new Error("existing EF100 body missing");
const functionStart = source.indexOf("void sub_000EF100(void)", start);
const braceStart = source.indexOf("{", functionStart);
let depth = 0;
let end = -1;
for (let i = braceStart; i < source.length; ++i) {
  if (source[i] === "{") ++depth;
  else if (source[i] === "}" && --depth === 0) { end = i + 1; break; }
}
if (end < 0) throw new Error("existing EF100 closing brace missing");
source = source.slice(0, start) + replacement + source.slice(end);
fs.writeFileSync(sourcePath, source, "utf8");
console.log("replaced sub_000EF100 with the complete retail 0xEF100-0xEF2DD body");
