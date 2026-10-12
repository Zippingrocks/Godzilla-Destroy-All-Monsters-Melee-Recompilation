# Local runtime assets

This repository intentionally contains no retail game data. Extract files from
your own copy of *Godzilla: Destroy All Monsters Melee* into `game_files/`.

The current startup and main-menu paths read the original Xbox XMV streams from
`game_files/shelldata/` at runtime. They do not load a predecoded image or frame
cache. Until the title's MMX-based WMV2 routines are fully lifted, place
`ffmpeg.exe` in `tools/bin/`, make it available on `PATH`, or set `FFMPEG_PATH`
to an FFmpeg executable. That local binary and all decoded media are ignored by
Git.

Required startup/menu streams currently include:

- `atari.xmv`
- `toho.xmv`
- `pipeworks.xmv`
- `gzintro.xmv`
- `dolby.xmv`
- `mainmenu.xmv`

These files are Xbox XMV streams, not Bink videos.
