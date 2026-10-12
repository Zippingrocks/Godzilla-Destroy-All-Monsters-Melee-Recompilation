# Architecture

The project keeps four boundaries explicit: retail evidence, generated guest
code, handwritten compatibility bridges, and the reusable `xboxrecomp`
runtime. A change is considered accurate only when it preserves those
boundaries and can be compared against the pinned retail build.

```text
read-only retail files
        |
        v
analysis and recovery tools
        |
        v
generated guest C in src/game/recomp/gen
        |
        +--> handwritten ABI/runtime bridges in recomp_manual.c
        |
        v
xboxrecomp kernel + NV2A + audio + input runtime
        |
        v
native Windows executable
```

## Generated guest code

`src/game/recomp/gen/` contains lifted functions, dispatch tables, function
declarations, and unresolved-target stubs. These files represent the Xbox
program and are intentionally large. Recovery scripts in `tools/` document and
reproduce corrections to generated regions.

## Handwritten game boundary

`src/game/main.c` establishes the guest address space and starts the translated
entry point. `src/game/recomp_manual.c` contains narrowly scoped host bridges
for ABI gaps, timing, input, XMV playback, and renderer submission. Each bridge
should converge toward recovered retail behavior instead of becoming a second
game implementation.

## Runtime boundary

The project links against `xboxrecomp`, which supplies replacement Xbox kernel,
Direct3D/NV2A, DirectSound, and input services. DAMM-specific behavior belongs
here only when it cannot be expressed generically upstream.

## Evidence boundary

`fixtures/retail-xbox-us.json` pins the supported executable. Local analysis,
Xemu snapshots, RAM, captures, and extracted game content remain ignored.
Parity tools validate the reference process and hashes before accepting data.

## Acceptance gates

1. The Release target builds from a clean checkout with an explicit
   `XBOXRECOMP_DIR`.
2. The affected retail transition is exercised through its real callback or
   input boundary.
3. The resulting screen remains responsive for at least one minute.
4. Timing and pixels are compared only at equivalent states and image stages.
5. No retail data, decoded media, or machine-specific state enters Git.
