param(
    [Parameter(Mandatory)][int]$XemuPid,
    [Parameter(Mandatory)][string]$Stem,
    [string]$Python = 'C:\Users\Bilbo\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe',
    [UInt64]$RamBase = 0,
    [int]$Port = 4475
)
$ErrorActionPreference = 'Stop'
$reference = Get-Process -Id $XemuPid -ErrorAction Stop
$expectedXemu = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\xemu.exe'
if ($reference.Path -ne $expectedXemu) { throw 'PID is not the pinned DAMM parity Xemu executable.' }
$listener = Get-NetTCPConnection -LocalPort $Port -State Listen -ErrorAction Stop
if (!($listener | Where-Object { $_.OwningProcess -eq $XemuPid })) {
    throw 'QMP listener does not belong to the requested Xemu process.'
}
$fullStem = [IO.Path]::GetFullPath($Stem)
foreach ($suffix in @('.checkpoint.json', '.ram.bin', '.ram.bin.json', '.png')) {
    if (Test-Path -LiteralPath ($fullStem + $suffix)) { throw "Capture already exists: $fullStem$suffix" }
}
if (!(Test-Path -LiteralPath $Python)) { throw 'Python runtime not found.' }

$paused = $false
try {
    & node (Join-Path $PSScriptRoot 'xemu_capture_checkpoint.mjs') --port $Port --out ($fullStem + '.checkpoint.json')
    if ($LASTEXITCODE -ne 0) { throw 'Reference checkpoint failed.' }
    $paused = $true
    $metadata = Get-Content -LiteralPath ($fullStem + '.checkpoint.json') -Raw | ConvertFrom-Json
    & (Join-Path $PSScriptRoot 'read_xemu_ram.ps1') -XemuPid $XemuPid -Out ($fullStem + '.ram.bin') -RamBase $RamBase -Cr3 $metadata.cr3
    if ($LASTEXITCODE -ne 0) { throw 'Reference RAM read failed.' }
} finally {
    if ($paused) {
        & node (Join-Path $PSScriptRoot 'xemu_qmp_control.mjs') --port $Port --execute cont
        if ($LASTEXITCODE -ne 0) { Write-Warning 'Reference resume failed; inspect QMP status.' }
    }
}
& $Python (Join-Path $PSScriptRoot 'scanout.py') $fullStem
if ($LASTEXITCODE -ne 0) { throw 'Reference scanout decode failed.' }
