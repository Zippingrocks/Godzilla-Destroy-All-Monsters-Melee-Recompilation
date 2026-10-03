# Local runtime assets

This directory intentionally does not contain retail game data. Extract the
files from your own copy of *Godzilla: Destroy All Monsters Melee* into
`game_files/`.

The current main-menu bring-up path uses a temporary host-decoded YUY2 cache
until the title's MMX-based WMV2 reconstruction routines are fully lifted. With
FFmpeg installed, generate that cache from the original Xbox movie:

```powershell
ffmpeg -y -i game_files/shelldata/mainmenu.xmv -an `
  -pix_fmt yuyv422 -f rawvideo assets/mainmenu_frames.yuy2
```

For the verified North American retail asset this produces 90 frames at
640x480 and 30 FPS. The cache is ignored by Git because it contains decoded
retail content.
