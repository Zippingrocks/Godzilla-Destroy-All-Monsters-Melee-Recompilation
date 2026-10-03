# DAMM Xemu parity lab

This directory runs a separate, pinned retail reference for the native
recompilation. It does not attach automation to either user-owned Xemu process.

The launcher verifies the retail XBE and XISO hashes, copies the EEPROM into a
workspace-local runtime directory, uses an HDD snapshot, disables networking
and automatic input binding, and gives Xemu private QMP/GDB ports. `-Rendered`
runs the real GPU/video path on a private Windows desktop named
`GodzillaDammParityDesktop-<gdb-port>`; it never switches the visible desktop.

Dry-run validation:

```powershell
.\tools\parity\run_isolated_xemu.ps1
```

Start the hidden rendered oracle and verify its debugger endpoint:

```powershell
.\tools\parity\run_isolated_xemu.ps1 -Start -Rendered
node .\tools\parity\xemu_rsp_probe.mjs probe --port 1265
node .\tools\parity\xemu_qmp_control.mjs --port 4475 --execute query-status
```

The first movie work targets the retail XMV sequence. DAMM's startup assets are
`atari.xmv`, `dolby.xmv`, `pipeworks.xmv`, `toho.xmv`, and `gzintro.xmv`;
`mainmenu.xmv` is part of the menu presentation. These are Xbox XMV streams,
not Bink files.

Raw memory and image captures are local diagnostic evidence. Do not commit or
distribute retail RAM, disc images, executable data, or decoded movie frames.
