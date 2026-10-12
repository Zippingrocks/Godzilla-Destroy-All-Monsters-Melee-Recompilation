# Repository guardrails

- Treat the retail executable, disc image, extracted game files, emulator state,
  decoded media, and captures as read-only local evidence. Never commit or
  redistribute them.
- Preserve the pinned USA retail Xbox executable identity in
  `fixtures/retail-xbox-us.json`. Do not generalize findings to another region
  or revision without a separate fixture and validation record.
- Keep the static recompilation split into generated guest code, handwritten
  runtime bridges, and upstream `xboxrecomp`. Do not hand-edit generated files
  when the change can be expressed in a recovery/generation tool.
- Prefer recovered retail callbacks and state transitions over replacement UI,
  prerecorded images, or hard-coded progression. Clearly label temporary host
  bridges and keep the original game responsible for frontend state.
- Xemu is a read-only behavioral oracle. A visual-parity claim requires the
  same retail build, logical state, input boundary, frame, and image stage.
- A successful build is not sufficient for frontend changes. Exercise the
  affected transition and soak each reached menu for at least one minute.
- Keep generated output in ignored build, analysis, capture, or log paths.
  Source, documentation, fixtures, and reproducible tools belong in Git.
- Do not weaken retail hash checks or parity-tool fail-closed checks merely to
  make a capture or test pass.
