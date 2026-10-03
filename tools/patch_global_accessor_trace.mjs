import fs from "node:fs";

const path = "src/game/recomp/gen/recomp_0000.c";
let source = fs.readFileSync(path, "utf8");
if (!source.includes("#include <stdio.h>")) {
  source = source.replace("#include <math.h>\r\n", "#include <math.h>\r\n#include <stdio.h>\r\n");
}

const oldBody = `loc_00029933: ;\r\n    eax = MEM32(0x1E11C8);\r\n    eax = MEM32(eax);\r\n    esp += 4; return; /* ret */`;
const newBody = `loc_00029933: ;\r\n    {\r\n        static uint64_t accessor_count;\r\n        uint32_t return_va = MEM32(esp);\r\n        ++accessor_count;\r\n        eax = MEM32(0x1E11C8);\r\n        eax = MEM32(eax);\r\n        if (accessor_count <= 32 || (accessor_count % 1000000u) == 0) {\r\n            fprintf(stderr, "[GLOBAL-ACCESSOR] count=%llu ret=%08X value=%08X esp=%08X\\n",\r\n                    (unsigned long long)accessor_count, return_va, eax, esp);\r\n        }\r\n    }\r\n    esp += 4; return; /* ret */`;
if (source.includes(oldBody)) {
  source = source.replace(oldBody, newBody);
} else if (!source.includes("[GLOBAL-ACCESSOR]")) {
  throw new Error("sub_00029933 body not found");
}

const waitMarker = `loc_000125BD: ;\r\n    /* nop */`;
const waitTrace = `loc_000125BD: ;\r\n    {\r\n        static int wait_logged;\r\n        if (!wait_logged) {\r\n            wait_logged = 1;\r\n            fprintf(stderr, "[BOOT-WAIT] deadline=%08X timer=%08X object=%08X\\n",\r\n                    MEM32(esi + 0xA8), MEM32(MEM32(0x1E11C8)), esi);\r\n        }\r\n    }`;
if (source.includes(waitMarker)) {
  source = source.replace(waitMarker, waitTrace);
} else if (!source.includes("[BOOT-WAIT]")) {
  throw new Error("sub_00012490 wait-loop marker not found");
}

const entryMarker = `loc_00012490: ;\r\n    PUSH32(esp, ecx);`;
const entryTrace = `loc_00012490: ;\r\n    {\r\n        static uint32_t entry_count;\r\n        ++entry_count;\r\n        fprintf(stderr, "[BOOT-ENTRY] #%u object=%08X ret=%08X esp=%08X\\n",\r\n                entry_count, ecx, MEM32(esp), esp);\r\n    }\r\n    PUSH32(esp, ecx);`;
if (source.includes(entryMarker)) {
  source = source.replace(entryMarker, entryTrace);
} else if (!source.includes("[BOOT-ENTRY]")) {
  throw new Error("sub_00012490 entry marker not found");
}

if (!source.includes("[BOOT-ESI]")) {
  for (const label of [
    "000124A2", "000124B4", "000124D5", "00012511", "0001251B",
    "0001252E", "00012549", "00012554", "0001255E", "0001259B",
  ]) {
    const marker = `loc_${label}: ;\r\n`;
    if (!source.includes(marker)) throw new Error(`missing trace label ${label}`);
    const trace = `${marker}    fprintf(stderr, "[BOOT-ESI] loc=${label} esi=%08X eax=%08X ecx=%08X esp=%08X\\n", esi, eax, ecx, esp);\r\n`;
    source = source.replace(marker, trace);
  }
}

fs.writeFileSync(path, source);
console.log("instrumented sub_00029933 global accessor");
