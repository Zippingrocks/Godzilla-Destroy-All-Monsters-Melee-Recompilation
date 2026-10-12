# Build and run

## Requirements

- Windows 10 or 11
- Visual Studio 2022 with **Desktop development with C++**
- CMake 3.20 or newer
- A local checkout of `xboxrecomp`
- FFmpeg for the current host XMV bridge
- Files extracted from a legally obtained retail copy of the game

## Retail input

Place the supported executable at `game_files/default.xbe` and the extracted
disc filesystem below `game_files/`. Verify the executable before debugging:

```powershell
Get-FileHash .\game_files\default.xbe -Algorithm SHA256
```

The expected digest is recorded in
[`fixtures/retail-xbox-us.json`](../fixtures/retail-xbox-us.json). Other builds
are not currently supported.

## Configure and build

```powershell
cmake -S . -B build -A x64 -DXBOXRECOMP_DIR=C:/path/to/xboxrecomp
cmake --build build --config Release
```

The executable is written to `bin/godzilla_damm.exe`.

## Runtime media

Place `ffmpeg.exe` in `tools/bin/`, add FFmpeg to `PATH`, or set `FFMPEG_PATH`
to the executable. The bridge decodes the original XMV streams at runtime; the
repository does not contain predecoded frames or replacement menu artwork.

## Launch

```powershell
.\tools\launch-menu.cmd
```

The launcher clears diagnostic overrides and starts the normal retail movie
sequence. `GODZILLA_SKIP_MOVIES` is a development switch, not the default user
path.

## Local output

Build directories, executables, saves, logs, dumps, captures, analysis data,
and extracted retail files are ignored. Keep reproducible source changes in
`src/`, tests in `tests/`, and research/repair tools in `tools/`.
