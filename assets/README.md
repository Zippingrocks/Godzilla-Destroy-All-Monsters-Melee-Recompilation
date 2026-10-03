# Local runtime assets

This directory intentionally does not contain retail game data. Extract the
files from your own copy of *Godzilla: Destroy All Monsters Melee* into
`game_files/`.

The stable main-menu path reads the original
`game_files/shelldata/mainmenu.xmv` at runtime. It does not require or load a
predecoded image or frame cache. Until the title's MMX-based WMV2 routines are
fully lifted, place `ffmpeg.exe` in `tools/bin/` or set `FFMPEG_PATH` to an
FFmpeg executable. That local binary is ignored by Git.
