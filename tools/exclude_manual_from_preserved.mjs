import fs from "node:fs";
import path from "node:path";

const roots = process.argv.slice(2);
if (roots.length === 0) throw new Error("pass one or more preserved generated directories");

const targets = [
  "sub_0002A76D",
  "sub_0002A795",
  "sub_0002BDBA",
  "sub_0002C571",
  "sub_000DD600",
  "sub_00109EC0",
  "sub_0010FF6F",
  "sub_0012D75A",
  "sub_0012DF80",
  "sub_00154FF1",
  "sub_001559A9",
  "sub_0015A5AF",
  "sub_0015C9BE",
];

function functionEnd(text, open) {
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
    if (ch === "}" && --depth === 0) return index + 1;
  }
  throw new Error("unterminated generated function");
}

for (const root of roots) {
  const absoluteRoot = path.resolve(root);
  const files = fs.readdirSync(absoluteRoot)
    .filter((name) => /^recomp_\d+\.c$/.test(name))
    .map((name) => path.join(absoluteRoot, name));
  let patched = 0;
  for (const file of files) {
    let source = fs.readFileSync(file, "utf8");
    const edits = [];
    for (const target of targets) {
      const guard = `#if 0 /* Manual override: ${target} */`;
      if (source.includes(guard)) continue;
      const signature = `void ${target}(void)`;
      const start = source.indexOf(signature);
      if (start < 0) continue;
      const open = source.indexOf("{", start + signature.length);
      const end = functionEnd(source, open);
      edits.push({ start, end, guard });
    }
    for (const edit of edits.sort((a, b) => b.start - a.start)) {
      source = source.slice(0, edit.start) + edit.guard + "\n" +
        source.slice(edit.start, edit.end) + "\n#endif" + source.slice(edit.end);
    }
    if (edits.length > 0) {
      fs.writeFileSync(file, source, "utf8");
      patched += edits.length;
      process.stdout.write(`excluded ${edits.length}: ${file}\n`);
    }
  }
  const combined = files.map((file) => fs.readFileSync(file, "utf8")).join("\n");
  const missing = targets.filter((target) =>
    !combined.includes(`#if 0 /* Manual override: ${target} */`));
  if (missing.length > 0) {
    throw new Error(`manual bodies not excluded in ${absoluteRoot}: ${missing.join(", ")}`);
  }
}
