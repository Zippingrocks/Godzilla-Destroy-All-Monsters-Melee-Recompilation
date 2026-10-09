param(
    [Parameter(Mandatory)][int]$XemuPid,
    [int]$QmpPort = 4475
)
$ErrorActionPreference = 'Stop'

$expectedXemu = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\xemu.exe'
$workRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$expectedXbe = Join-Path $workRoot 'game_files\default.xbe'
$expectedDisc = [IO.Path]::GetFullPath((Join-Path $workRoot '..\Game\Godzilla - Destroy All Monsters Melee (USA, Europe) (En,Fr,De,Es,It).xiso.iso'))
$expectedXbeHash = '9D0BA935E89FC36D4C6895F5A9CC8AFAD2E05CDD17E9183517595E404DA300B8'
$expectedDiscHash = '12B6BD445D7F25B4F4836B75BED73471D2B10C0F12B3183FE0C00516A5DCBED8'

$process = Get-Process -Id $XemuPid -ErrorAction Stop
if ($process.Path -ne $expectedXemu) { throw 'PID is not the pinned parity Xemu executable.' }
$listener = Get-NetTCPConnection -LocalPort $QmpPort -State Listen -ErrorAction Stop
if (!($listener | Where-Object { $_.OwningProcess -eq $XemuPid })) {
    throw 'QMP listener is not owned by the requested Xemu PID.'
}

$xbeHash = (Get-FileHash -LiteralPath $expectedXbe -Algorithm SHA256).Hash
$discHash = (Get-FileHash -LiteralPath $expectedDisc -Algorithm SHA256).Hash
if ($xbeHash -ne $expectedXbeHash) { throw "DAMM XBE hash mismatch: $xbeHash" }
if ($discHash -ne $expectedDiscHash) { throw "DAMM XISO hash mismatch: $discHash" }

$qmp = Join-Path $PSScriptRoot 'xemu_qmp_control.mjs'
$status = (& node $qmp --port $QmpPort --execute query-status | Out-String) | ConvertFrom-Json
if (!$status.response.return.running) { throw "Xemu is not running: $($status.response.return.status)" }
$blocks = (& node $qmp --port $QmpPort --execute query-block | Out-String) | ConvertFrom-Json
$dvd = $blocks.response.return | Where-Object { $_.device -eq 'ide0-cd1' }
if (!$dvd -or !$dvd.inserted) { throw 'Xemu DVD drive has no mounted disc.' }
$mountedDisc = $dvd.inserted.backing_file
if (!$mountedDisc) { $mountedDisc = $dvd.inserted.image.'backing-image'.filename }
if ([IO.Path]::GetFullPath($mountedDisc) -ne $expectedDisc) {
    throw "Wrong Xemu disc mounted: $mountedDisc"
}
if ([UInt64]$dvd.inserted.image.'backing-image'.'virtual-size' -ne 1022033920) {
    throw 'Mounted DAMM disc size does not match the pinned image.'
}

[ordered]@{
    schema = 1
    verified = $true
    title = 'Godzilla: Destroy All Monsters Melee'
    region = 'USA, Europe (En,Fr,De,Es,It)'
    xemuPid = $XemuPid
    qmpPort = $QmpPort
    status = $status.response.return.status
    mountedDisc = $mountedDisc
    discBytes = [UInt64]$dvd.inserted.image.'backing-image'.'virtual-size'
    xisoSha256 = $discHash
    xbeSha256 = $xbeHash
    verifiedAt = [DateTime]::UtcNow.ToString('o')
} | ConvertTo-Json
