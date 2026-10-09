import fs from "node:fs";

const file = "src/game/recomp_vtable_generated.c";
let source = fs.readFileSync(file, "utf8");
for (const name of [
  "sub_000EF14A", "sub_000EF16C", "sub_000EF18C",
  "sub_000EF1BC", "sub_000EF1EB",
]) {
  const namePosition = source.indexOf(` * ${name}`);
  if (namePosition < 0) continue;
  const start = source.lastIndexOf("/**", namePosition);
  const functionStart = source.indexOf(`void ${name}(void)`, namePosition);
  const braceStart = source.indexOf("{", functionStart);
  let depth = 0;
  let end = -1;
  for (let i = braceStart; i < source.length; ++i) {
    if (source[i] === "{") ++depth;
    else if (source[i] === "}" && --depth === 0) { end = i + 1; break; }
  }
  if (start < 0 || end < 0) throw new Error(`cannot remove ${name}`);
  source = source.slice(0, start) + source.slice(end).replace(/^\r?\n/, "");
}
fs.writeFileSync(file, source, "utf8");
console.log("removed superseded EF100 fragment bodies");
