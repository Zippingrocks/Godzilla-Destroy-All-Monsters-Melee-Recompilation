import fs from "node:fs";
import path from "node:path";

const targets = process.argv.slice(2);
if (targets.length === 0) {
  throw new Error("pass one or more recomp_0000.c paths");
}

for (const target of targets) {
  const absolute = path.resolve(target);
  let source = fs.readFileSync(absolute, "utf8");
  if (source.includes("#if 0 /* Corrupt preserved splice")) {
    process.stdout.write(`already patched: ${absolute}\n`);
    continue;
  }

  const startMarker = "/**\r\n * sub_00040F90";
  const nextMarker = "/**\r\n * sub_00041270";
  const start = source.indexOf(startMarker);
  const next = source.indexOf(nextMarker, start + startMarker.length);
  if (start < 0 || next < 0) {
    throw new Error(`corrupt splice markers not found in ${absolute}`);
  }

  source =
    source.slice(0, start) +
    "#if 0 /* Corrupt preserved splice; exact bodies live in recomp_vtable_generated.c. */\r\n" +
    source.slice(start, next) +
    "#endif\r\n\r\n" +
    source.slice(next);
  fs.writeFileSync(absolute, source, "utf8");
  process.stdout.write(`patched: ${absolute}\n`);
}
