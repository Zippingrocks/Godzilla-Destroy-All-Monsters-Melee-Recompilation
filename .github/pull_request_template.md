## What changed?

Describe the problem and the resulting behavior. Link related issues.

## Retail/Xemu evidence

Explain the callback, state, trace, or rendering evidence used. State the exact
retail build and whether the comparison used equivalent input/frame/image-stage
boundaries.

## How was it checked?

List builds, repository tests, runtime paths, soak duration, and parity results.
For rendering work, include raw comparison metrics. For performance work,
compare the same state and settings before and after.

## Remaining limits

List untested cases, known differences, and follow-up work. Write `None` if
there are none.

## Checklist

- [ ] This targets `main` and keeps the change focused.
- [ ] I followed [CONTRIBUTING.md](../CONTRIBUTING.md).
- [ ] I included no retail game data, decoded media, captures, saves, dumps,
      build output, or runtime binaries.
- [ ] I did not weaken fixture hashes or parity validation.
- [ ] I ran the relevant checks and documented anything I could not test.
