# Current status

## Working

- The translated game builds as a native Windows executable.
- The original startup XMV files play through a paced 30 FPS host bridge.
- Startup skip now completes the frontend handoff before decoder teardown.
- The frontend and animated menu path render through the NV2A/D3D11 runtime.
- Main-menu movie frames come from the original `mainmenu.xmv`, not a PNG or
  static replacement.
- A hash-pinned, isolated Xemu parity lab can capture state and inject matching
  logical controller edges.

## Incomplete

- Profile creation/selection and full menu navigation still depend on missing
  callbacks and indirect-call targets.
- Menu pixels are not yet Xemu-identical; shader, render-target, texture,
  lighting, and transition differences remain.
- The current XMV bridge uses FFmpeg because the title's MMX-heavy decoder is
  not fully lifted.
- Gameplay is not an achieved milestone.

## Definition of the next milestone

The frontend milestone is complete only when a cold launch plays/skips the real
startup movies, reaches the genuine menu flow, traverses every first-level
option and returns, holds each unique screen for one minute, remains responsive,
and sustains 30 FPS without crashes or black/flickering transitions.
