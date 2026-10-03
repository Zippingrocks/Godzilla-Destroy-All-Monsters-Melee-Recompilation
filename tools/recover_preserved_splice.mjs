import { spawnSync } from "node:child_process";
import fs from "node:fs";
import path from "node:path";

const workRoot = process.cwd();
const xboxrecompRoot = path.resolve(workRoot, "..", "..", "repos", "Repos", "xboxrecomp");
const xbe = path.join(workRoot, "game_files", "default.xbe");
const disasm = path.join(workRoot, "analysis", "disasm");
const output = path.join(workRoot, "src", "game", "recomp_vtable_generated.c");
const addresses = ["0x00040F90", "0x000410E0"];

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
    "--functions", path.join(disasm, "functions.json"),
    "--labels", path.join(disasm, "labels.json"),
    "--identified", path.join(workRoot, "analysis", "func_id", "identified_functions.json"),
    "--abi", path.join(workRoot, "analysis", "abi", "abi_functions.json"),
    "--skip-binary-check", "-f", address,
  ];
  const result = spawnSync("python", args, {
    cwd: xboxrecompRoot,
    encoding: "utf8",
    maxBuffer: 16 * 1024 * 1024,
  });
  if (result.status !== 0) {
    throw new Error(`recompiler failed for ${address}:\n${result.stderr}\n${result.stdout}`);
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
