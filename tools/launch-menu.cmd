@echo off
set "GODZILLA_SKIP_MOVIES="
set "GODZILLA_TRACE_FRAME="
set "XBOXRECOMP_CAPTURE="
set "FFMPEG_PATH="
set "GODZILLA_XMV_UNTHROTTLED="
cd /d "%~dp0.."
"%CD%\bin\godzilla_damm.exe" 1>"%CD%\run-visible.out.log" 2>"%CD%\run-visible.err.log"
