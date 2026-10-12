# Repository layout

```text
.github/workflows/   automated repository checks
docs/                architecture, build, parity, status, and roadmap
fixtures/            hashes and expected facts for supported retail builds
src/game/             host entry point and DAMM-specific runtime bridges
src/game/recomp/gen/  generated guest C and dispatch data
tests/                repository and fixture guardrails
tools/                reproducible recovery, repair, and diagnostic tools
tools/parity/         isolated Xemu comparison lab
```

The following paths are intentionally local and ignored:

- `game_files/` — extracted retail content;
- `analysis/` — disassembly and analysis databases;
- `bin/`, `build*/` — compiled output;
- `SaveData/` — emulated title saves;
- `dumps/`, `out/`, logs, images, and captures — runtime evidence;
- `.tools/`, `tools/bin/` — downloaded local tooling.

Large generated C files remain tracked because they are the portable product of
the recompilation pipeline. Large generated diagnostics and retail-derived
content do not.
