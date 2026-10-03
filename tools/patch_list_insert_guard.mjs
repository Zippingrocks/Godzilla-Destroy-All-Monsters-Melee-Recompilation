import fs from "node:fs";

const path = "src/game/recomp/gen/recomp_0002.c";
let source = fs.readFileSync(path, "utf8");

const oldTrace = "if (insert_number <= 128 || (entry_node & 3u) != 0 || entry_node == 0)";
const newTrace = "if (insert_number <= 128 || !entry_node || (entry_node & 3u) != 0 ||\r\n        !((entry_node >= 0x00010000u && entry_node < 0x04000000u) ||\r\n          (entry_node >= 0x80000000u && entry_node < 0x84000000u)) ||\r\n        (entry_owner & 3u) != 0)";
if (source.includes(oldTrace)) source = source.replace(oldTrace, newTrace);

const oldGuard = "if (entry_node == 0 || (entry_node & 3u) != 0)";
const newGuard = "if (!entry_node || (entry_node & 3u) != 0 || (entry_owner & 3u) != 0 ||\r\n        !((entry_node >= 0x00010000u && entry_node < 0x04000000u) ||\r\n          (entry_node >= 0x80000000u && entry_node < 0x84000000u)) ||\r\n        !((entry_owner >= 0x00010000u && entry_owner < 0x04000000u) ||\r\n          (entry_owner >= 0x80000000u && entry_owner < 0x84000000u)))";
if (source.includes(oldGuard)) source = source.replace(oldGuard, newGuard);

if (!source.includes("!((entry_node >= 0x00010000u")) {
  throw new Error("list insert canonical-pointer guard was not applied");
}

source = source.replace(
  "An\r\n       unaligned pointer can only be corrupt",
  "A null, unaligned, or non-canonical pointer can only be corrupt",
);
fs.writeFileSync(path, source);
console.log("strengthened sub_000DE8C0 list-insert pointer guard");
