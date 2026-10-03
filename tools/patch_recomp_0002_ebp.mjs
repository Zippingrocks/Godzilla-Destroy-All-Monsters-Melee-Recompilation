import fs from "node:fs";

const path = "src/game/recomp/gen/recomp_0002.c";
let source = fs.readFileSync(path, "utf8");
const needle = `void sub_00108030(void)\r\n{\r\n    int _flags = 0; /* fallback flag var */`;
const replacement = `void sub_00108030(void)\r\n{\r\n    /* Recovered fall-through fragment below uses EBP as its zero register. */\r\n    uint32_t ebp = 0;\r\n    int _flags = 0; /* fallback flag var */`;

if (!source.includes(needle)) {
  if (source.includes("Recovered fall-through fragment below uses EBP")) {
    console.log("patch already applied");
  } else {
    throw new Error("target function prologue not found");
  }
} else {
  source = source.replace(needle, replacement);
  console.log("patched sub_00108030 EBP declaration");
}

const splitNeedle = `    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstse: equal / zero */\r\n\r\nloc_00108A3F: ;`;
const splitReplacement = `    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstse: equal / zero */\r\n\r\nloc_001080FA: ;\r\n    POP32(esp, esi);\r\n    esp += 0x64; return; /* recovered function boundary */\r\n\r\nloc_00108A0D: ;\r\nloc_00108A3F: ;`;

if (!source.includes(splitNeedle)) {
  if (!source.includes("recovered function boundary")) {
    throw new Error("missing generated function boundary target not found");
  }
} else {
  source = source.replace(splitNeedle, splitReplacement);
  console.log("restored missing compile-time labels at recovered boundary");
}

fs.writeFileSync(path, source);
