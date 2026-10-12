# Xemu parity workflow

Xemu is the reference implementation for behavior and rendering, not a source
of redistributable assets. The DAMM parity lab is designed to compare the same
retail build at the same state and logical input boundary.

## Rules

- Verify the XBE and disc hashes before accepting reference data.
- Use a separate Xemu instance with private QMP/GDB ports and isolated state.
- Inject equivalent controller edges through `XInputGetState`; do not write
  menu or progression state directly.
- Compare unscaled frames from the same animation frame and image stage.
- Keep timing validation capture-free because debugger stops and readbacks
  disturb wall-clock behavior.
- Require strict RGB equality for a pixel-parity claim. RMSE, PSNR, overlays,
  and alignment searches are diagnostics, not passes.

The command reference, safety checks, and known scanout limitations live beside
the implementation in [`tools/parity/README.md`](../tools/parity/README.md).
