# Roadmap

## 0. Evidence and recompilation baseline — complete

- [x] Pin the supported USA retail Xbox executable by SHA-256.
- [x] Recover the XBE section layout, functions, instructions, references, and
  ABI metadata.
- [x] Lift 5,277 functions into C and establish dispatch/stub generation.
- [x] Keep retail files and derived captures outside Git.

## 1. Native boot and startup media — current

- [x] Boot the translated executable through the native Windows runtime.
- [x] Decode the original startup XMV sequence at runtime.
- [x] Support a skip input without leaking the Start edge or crashing teardown.
- [x] Hold the startup-to-frontend transition for a one-minute stability soak.
- [ ] Replace the host FFmpeg bridge with recovered Xbox/MMX video decoding.
- [ ] Match retail audio and exact per-logo transition timing.

## 2. Frontend construction and navigation — current

- [x] Reach a visible animated PRESS START/frontend presentation.
- [x] Recover enough callback and vtable dispatch to reach the main-menu path.
- [x] Translate keyboard/controller input into retail XInput boundaries.
- [ ] Complete profile creation and selection through retail callbacks.
- [ ] Navigate every first-level menu entry and return without a crash.
- [ ] Pass a one-minute idle soak in every unique frontend screen.

## 3. Renderer parity

- [x] Submit retail Kelvin/NV2A menu geometry through D3D11.
- [x] Feed the original looping `mainmenu.xmv` into the retail movie texture.
- [x] Correct the major channel-order/color-cast failure.
- [ ] Eliminate remaining render-target corruption and transition black frames.
- [ ] Recover missing shader, texture, blend, lighting, and model paths.
- [ ] Produce synchronized, same-stage Xemu/recomp frame comparisons.
- [ ] Reach strict pixel equality for stable frontend checkpoints.

## 4. Frontend reliability

- [ ] Sustain 30 FPS without submenu transition dips.
- [ ] Stress rapid skip, accept, back, and direction inputs.
- [ ] Resolve all frontend indirect-call misses reached by normal navigation.
- [ ] Run repeatable cold-start and 60-second menu tests in CI-capable tooling.

## 5. Gameplay entry

Gameplay is outside the current acceptance target. It begins only after startup,
profile selection, and every first-level menu screen are stable and accurately
rendered.
