import fs from "node:fs";
import path from "node:path";

const [inputDir, outputFile] = process.argv.slice(2);
if (!inputDir || !outputFile) {
  throw new Error("usage: node extract_runtime_vtables.mjs <generated-dir> <output.c>");
}

const targets = [
  "sub_0010B520",
  "sub_0010B550",
  "sub_00030F60",
  "sub_000318D0",
  "sub_000EAC00",
  "sub_000E9CD0",
  "sub_000EA920",
  "sub_000DFCD0",
  "sub_000EAC20",
  "sub_000DFB70",
  "sub_000DA490",
  "sub_000E1330",
];

const sourceFiles = fs.readdirSync(inputDir)
  .filter((name) => /^recomp_\d+\.c$/.test(name))
  .sort()
  .map((name) => ({ name, text: fs.readFileSync(path.join(inputDir, name), "utf8") }));

function extractFunction(text, name) {
  const signature = `void ${name}(void)`;
  const start = text.indexOf(signature);
  if (start < 0) return null;
  const open = text.indexOf("{", start + signature.length);
  if (open < 0) throw new Error(`missing opening brace for ${name}`);

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
    if (ch === "}" && --depth === 0) return text.slice(start, index + 1);
  }
  throw new Error(`unterminated body for ${name}`);
}

const bodies = [];
for (const target of targets) {
  let body = null;
  for (const source of sourceFiles) {
    body = extractFunction(source.text, target);
    if (body) break;
  }
  if (!body) throw new Error(`generated body not found: ${target}`);
  bodies.push(body);
}

const output = [
  "/* Exact runtime-observed vtable bodies extracted from xboxrecomp output. */",
  "#define RECOMP_GENERATED_CODE",
  "#include \"recomp_funcs.h\"",
  "",
  bodies.join("\n\n"),
  "",
].join("\n");

fs.writeFileSync(outputFile, output);
process.stdout.write(`extracted ${bodies.length} functions to ${outputFile}\n`);
