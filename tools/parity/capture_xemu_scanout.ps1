param(
    [Parameter(Mandatory)][int]$XemuPid,
    [Parameter(Mandatory)][string]$Stem,
    [UInt64]$RamBase,
    [string]$Python = 'C:\Users\Bilbo\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe',
    [int]$Port = 4475
)
$ErrorActionPreference = 'Stop'
$reference = Get-Process -Id $XemuPid -ErrorAction Stop
if ($reference.Path -ne 'C:\Users\Bilbo\Desktop\Emulation\XEMU\xemu.exe') {
    throw 'PID is not the pinned DAMM parity Xemu executable.'
}
$fullStem = [IO.Path]::GetFullPath($Stem)
foreach ($suffix in @('.checkpoint.json', '.ram.bin', '.ram.bin.json', '.png')) {
    if (Test-Path -LiteralPath ($fullStem + $suffix)) { throw "Capture already exists: $fullStem$suffix" }
}
$paused = $false
try {
    & node (Join-Path $PSScriptRoot 'xemu_capture_checkpoint.mjs') --port $Port --out ($fullStem + '.checkpoint.json')
    if ($LASTEXITCODE -ne 0) { throw 'Reference checkpoint failed.' }
    $paused = $true
    $metadata = Get-Content -LiteralPath ($fullStem + '.checkpoint.json') -Raw | ConvertFrom-Json
    $start = [UInt64]$metadata.pcrtcStart -band 0x03FFFFFF
    & (Join-Path $PSScriptRoot 'read_xemu_ram.ps1') -XemuPid $XemuPid -Out ($fullStem + '.ram.bin') `
        -GuestAddress $start -Length (2560 * 480) -RamBase $RamBase -Cr3 $metadata.cr3
    if ($LASTEXITCODE -ne 0) { throw 'Reference scanout RAM read failed.' }
} finally {
    if ($paused) {
        & node (Join-Path $PSScriptRoot 'xemu_qmp_control.mjs') --port $Port --execute cont
    }
}
& $Python (Join-Path $PSScriptRoot 'scanout.py') $fullStem --ram-guest-base ("0x{0:X}" -f $start)
if ($LASTEXITCODE -ne 0) { throw 'Reference scanout decode failed.' }
