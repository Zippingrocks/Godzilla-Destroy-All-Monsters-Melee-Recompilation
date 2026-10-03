# Godzilla: Destroy All Monsters Melee recompilation

This directory contains the working artifacts for a static recompilation of the
retail original-Xbox executable. The original disc image remains in `../Game/`;
generated analysis and C sources live here.

## Verified input

- Title: `Godzilla: Melee`
- Title ID: `0x49470039`
- Executable SHA-256: `9D0BA935E89FC36D4C6895F5A9CC8AFAD2E05CDD17E9183517595E404DA300B8`
- XDK: `1.0.5233`
- Entry point: `0x0002A6D9`
- Image range: `0x00010000`–`0x004D3EA0`
- Original debug path: `c:\gz_xbox_final\DAM\release_xbox\Godzilla.exe`

## Current milestone

The recompilation now boots through the frontend and reaches a stable, visible
main menu. The retail menu background and reconstructed menu geometry are
submitted through the native D3D11/NV2A translation path. The menu's looping
XMV background currently uses a local host-decoded YUY2 cache while the missing
MMX video-reconstruction operations are being recovered.

Completed foundations include:

- `game_files/default.xbe` — user-supplied extracted retail executable
- `analysis/xbe_analysis.json` — XBE metadata and section layout
- `analysis/disasm/` — 6,158 detected functions, 371,961 instructions,
  66,380 cross-references, and 2,678 strings
- `analysis/func_id/` — CRT and vtable classifications
- `analysis/abi/abi_functions.json` — calling-convention recovery
- `src/game/recomp/gen/` — 5,277 functions lifted into 587,442 lines of C,
  plus dispatch code and 416 unresolved-target stubs

Retail game files, decoded movies, emulator state, captures, logs, and build
products are deliberately excluded from this repository.

## Build

Install Visual Studio 2022 with the Desktop development with C++ workload and
CMake. Clone `xboxrecomp`, then point this project at it during configuration:

```powershell
cmake -S . -B build -A x64 -DXBOXRECOMP_DIR=C:/path/to/xboxrecomp
cmake --build build --config Release
```

The executable is written to `bin/godzilla_damm.exe`. To use the current stable
main-menu path, first generate the local movie cache described in
[`assets/README.md`](assets/README.md), then launch with:

```powershell
$env:GODZILLA_SKIP_MOVIES = '1'
.\bin\godzilla_damm.exe
```

## Important analysis note

The generic function identifier still contains some Burnout-3-oriented
RenderWare heuristics. For this executable it reported no RenderWare symbols and
printed an incorrect hard-coded `.rdata` range during that heuristic phase.
The XBE parser, disassembler, ABI pass, and recompiler used the actual section
layout from `xbe_analysis.json`/`default.xbe`; do not use the function
identifier's printed `.rdata` range as a memory-layout source.

## Toolchain

The current toolkit checkout is `../../repos/Repos/xboxrecomp`. Capstone 5.0.9
was installed into Codex's bundled Python runtime for disassembly.
