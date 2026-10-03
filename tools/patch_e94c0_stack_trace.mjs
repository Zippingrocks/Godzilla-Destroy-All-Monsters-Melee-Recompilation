import fs from "node:fs";

const path = "src/game/recomp/gen/recomp_0002.c";
let source = fs.readFileSync(path, "utf8");

const prologue = `void sub_000E94C0(void)\r\n{\r\n    uint32_t ebp;`;
const tracedPrologue = `void sub_000E94C0(void)\r\n{\r\n    uint32_t e94_entry_sp = esp;\r\n    uint32_t ebp;`;
if (source.includes(prologue)) source = source.replace(prologue, tracedPrologue);

if (!source.includes("[E94-STACK]")) {
  for (const label of ["000E94DA", "000E94E9", "000E94F7", "000E9504", "000E99AD"]) {
    const marker = `loc_${label}: ;\r\n`;
    if (!source.includes(marker)) throw new Error(`missing E94 trace label ${label}`);
    const trace = `${marker}    fprintf(stderr, "[E94-STACK] loc=${label} entry=%08X esp=%08X delta=%d esi=%08X edi=%08X\\n",\r\n            e94_entry_sp, esp, (int32_t)(esp - e94_entry_sp), esi, edi);\r\n`;
    source = source.replace(marker, trace);
  }
}

if (!source.includes("uint32_t e94_entry_sp = esp;")) {
  throw new Error("E94 stack trace prologue not installed");
}
fs.writeFileSync(path, source);
console.log("instrumented sub_000E94C0 stack balance");
