# DAMM Xemu parity lab

This directory runs a separate, pinned retail reference for the native
recompilation. It does not attach automation to either user-owned Xemu process.

The launcher verifies the retail XBE and XISO hashes, copies the EEPROM into a
workspace-local runtime directory, uses an HDD snapshot, disables networking
and automatic input binding, and gives Xemu private QMP/GDB ports. `-Rendered`
runs the real GPU/video path on a private Windows desktop named
`GodzillaDammParityDesktop-<gdb-port>`; it never switches the visible desktop.

Dry-run validation:

```powershell
.\tools\parity\run_isolated_xemu.ps1
```

Start the hidden rendered oracle and verify its debugger endpoint:

```powershell
.\tools\parity\run_isolated_xemu.ps1 -Start -Rendered
node .\tools\parity\xemu_rsp_probe.mjs probe --port 1265
node .\tools\parity\xemu_qmp_control.mjs --port 4475 --execute query-status
```

Before accepting any capture as a DAMM reference, run the fail-closed live
verification. It checks the Xemu executable/PID, QMP listener ownership,
running state, mounted DVD path and size, and both retail hashes:

```powershell
.\tools\parity\verify_live_reference.ps1 -XemuPid <private-reference-pid>
```

The first movie work targets the retail XMV sequence. DAMM's startup assets are
`atari.xmv`, `dolby.xmv`, `pipeworks.xmv`, `toho.xmv`, and `gzintro.xmv`;
`mainmenu.xmv` is part of the menu presentation. These are Xbox XMV streams,
not Bink files.

Raw memory and image captures are local diagnostic evidence. Do not commit or
distribute retail RAM, disc images, executable data, or decoded movie frames.

## Method inherited from DAH1 and Save the Earth

This lab uses the stronger DAH1 method, with the Save the Earth port as a
cross-check:

1. Pin the exact retail XBE/XISO by SHA-256 and run a separate snapshot Xemu.
2. Keep the rendered oracle on a private Windows desktop with private QMP/GDB
   ports, no network, no automatic input binding, and no foreground focus.
3. Anchor both programs to the same retail state/input/presentation boundary.
4. Capture state and frames without resizing. Compare capture-free timing in a
   separate run because debugger stops and readbacks perturb wall-clock timing.
5. Require strict RGB equality for a pixel-parity claim. Alignment, overlays,
   and color fits are diagnostics only and never count as a pass.

`compare_frames.py` is the DAMM-native version of DAH1's strict comparator. It
also reports RMSE/PSNR and can search for an integer translation to diagnose a
viewport offset without concealing it:

```powershell
& 'C:\Users\Bilbo\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' `
  .\tools\parity\compare_frames.py reference.png recomp.png `
  --out .\build-parity-xemu\menu-compare.json `
  --diff .\build-parity-xemu\menu-diff.png `
  --overlay .\build-parity-xemu\menu-overlay.png --alignment-radius 8
```

The JSON deliberately leaves `timingVerified` and `captureStageVerified` false.
Those become valid only after the captures are independently proven to be the
same game frame and the same image stage.

## Xemu checkpoint limits

The DAH1/Save the Earth checkpoint sequence is retained for renderer diagnosis:
`savevm` flushes dirty GPU surfaces, QMP stops the CPU, host RAM is copied, and
`scanout.py` decodes the assumed linear 640x480 X8R8G8B8 surface. This is useful
evidence, but it is not an exact frame-boundary capture. The flush and stop are
separate operations, and the raw scanout precedes PVIDEO composition, DAC gamma,
aspect handling, and Xemu UI scaling. Never compare that PNG against a final
window capture and call the result pixel parity.

`capture_xemu_checkpoint.ps1` wraps that sequence, validates the QMP listener's
owning PID, discovers Xemu's 64 MiB RAM allocation using DAMM retail code at
`0x000E0820`, reads it with read-only process rights, resumes in `finally`, and
decodes the raw scanout:

```powershell
.\tools\parity\capture_xemu_checkpoint.ps1 -XemuPid <pid> `
  -Stem .\build-parity-xemu\menu-checkpoint
```

Never substitute a DAH1/Save the Earth signature address: the dumper validates
the bytes against DAMM's hash-pinned XBE before accepting a host RAM region.

To leave the title screen without foreground keyboard/controller input, use the
DAMM-specific counterpart to DAH1's logical-pad adapter. It validates the retail
function bytes, waits at `XInputGetState`, supplies one analog-A result, and
returns normally to the caller. It does not write menu or progression state:

```powershell
node .\tools\parity\xemu_press_start.mjs --port 1265 `
  --out .\build-parity-xemu\press-start-input.json
```

The same validated one-poll adapter accepts `--action a|b|up|down|left|right`
so both engines can traverse an identical menu route without foreground input.

## First DAMM baseline (2026-10-03)

The hidden rendered oracle was launched as Xemu 0.8.136 and both private
endpoints were verified. Read-only checkpoints captured, in order, the animated
PRESS START scene, SELECT PROFILE, the main-menu transition, settled VERSUS,
and ADVENTURE selected. The retail XBE hash was
`9D0BA935E89FC36D4C6895F5A9CC8AFAD2E05CDD17E9183517595E404DA300B8`.

At the recovered `0x000E0820` menu submission, retail reported a two-record
render object. The recomp's existing `[PWK-SUBMIT]` trace also reports the
active menu object with `render_count=2`, so scene-object count is aligned even
though final pixels are not.

An initial same-size comparison against the old recomp Adventure capture
`frame_0040.bmp` found zero integer viewport offset, 70.0687% differing pixels,
13.4766 mean absolute channel error, and 16.2956 dB PSNR. This is a diagnostic
baseline, not a parity assertion: the exact animation frame and final image
stage were not synchronized. Newer recomp frames 120/600 also show a separate
green/striped render-target corruption that must be fixed before meaningful
frame-sequence parity.
