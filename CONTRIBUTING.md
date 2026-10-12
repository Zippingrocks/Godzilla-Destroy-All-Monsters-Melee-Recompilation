# Contributing

Contributions are welcome, especially reproducible bug reports, retail callback
recovery, renderer corrections, test tooling, and documentation. You do not
need prior recompilation experience to help.

Please follow the [Code of Conduct](CODE_OF_CONDUCT.md).

## Before starting

- Read the [current status](docs/status.md), [known issues](README.md#known-issues),
  and [roadmap](docs/roadmap.md).
- Search open issues and pull requests before beginning overlapping work.
- For a substantial change, open an issue describing the evidence and intended
  boundary before implementing it.

The immediate goal is an accurate and stable frontend: real startup movies,
profile selection, and every first-level menu screen at 30 FPS. Gameplay work
is premature unless it directly unblocks that milestone.

## Repository rules

- Never commit an XBE, disc image, extracted game file, XMV, save, emulator
  state, memory dump, decoded frame, capture, or other retail-derived payload.
- Pin every supported game revision independently. Do not weaken the checks in
  `fixtures/retail-xbox-us.json` or `tools/parity/` to accept another build.
- Prefer recovering the retail callback/state path over replacing it with host
  UI, static images, hard-coded progression, or prerecorded output.
- Prefer a recovery/generation tool over directly editing generated files in
  `src/game/recomp/gen/`.
- Keep DAMM-specific bridges in this repository and reusable Xbox behavior in
  `xboxrecomp`.
- Preserve authorship and notices for reused open-source code.

## Building and checking changes

Follow [Build and run](docs/build-and-run.md), then run the repository checks:

```powershell
python -m unittest discover -s tests -v
cmake --build build --config Release
```

Exercise the exact path affected by the change. Frontend changes must remain
responsive for at least one minute on each unique reached screen. Rendering
claims must compare equivalent Xemu/recomp states, inputs, frames, and image
stages; include raw metrics instead of relying only on a visual impression.

Document anything you could not test. A successful build does not establish
runtime correctness or pixel parity.

## Bug reports

Use the repository's bug-report template and include:

- the commit tested;
- Windows version, CPU, GPU, and graphics driver;
- controller or keyboard input used;
- exact startup/menu state and reproduction steps;
- whether the issue occurs every time;
- the relevant log excerpt and a screenshot/video for visual issues.

Remove personal information from logs. Do not attach retail files, decoded
assets, disc images, executable data, RAM, or save data.

## Pull requests

Open pull requests against `main`. Keep each pull request focused, link related
issues, explain the retail/Xemu evidence, list checks performed, and describe
remaining limits. The CI repository checks must pass.
