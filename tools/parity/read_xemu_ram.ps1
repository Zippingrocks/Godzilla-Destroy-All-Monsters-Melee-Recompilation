param(
    [Parameter(Mandatory)][int]$XemuPid,
    [Parameter(Mandatory)][string]$Out,
    [UInt64]$GuestAddress = 0,
    [ValidateRange(1,67108864)][int]$Length = 67108864,
    [UInt64]$RamBase = 0,
    [UInt32]$Cr3 = 0xF000,
    [UInt32]$SignatureAddress = 0x000E0820,
    [string]$Xbe = (Join-Path $PSScriptRoot '..\..\game_files\default.xbe')
)
$ErrorActionPreference = 'Stop'
$reference = Get-Process -Id $XemuPid -ErrorAction Stop
if ($reference.ProcessName -ne 'xemu') { throw 'Target is not Xemu.' }
$output = [IO.Path]::GetFullPath($Out)
if (Test-Path -LiteralPath $output) { throw 'Output already exists.' }
if ($GuestAddress + $Length -gt 67108864) { throw 'Read exceeds 64 MiB Xbox RAM.' }

if (!('GodzillaDammParityHostRam.Reader' -as [type])) {
Add-Type -TypeDefinition @'
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
namespace GodzillaDammParityHostRam {
 public static class Reader {
  [StructLayout(LayoutKind.Sequential)] struct Region {
   public ulong BaseAddress, AllocationBase; public uint AllocationProtect;
   public ushort PartitionId, Padding; public ulong RegionSize;
   public uint State, Protect, Type, Padding2;
  }
  [DllImport("kernel32.dll", SetLastError=true)] static extern IntPtr OpenProcess(uint access, bool inherit, int pid);
  [DllImport("kernel32.dll", SetLastError=true)] static extern bool ReadProcessMemory(IntPtr process, ulong address, byte[] data, UIntPtr size, out UIntPtr read);
  [DllImport("kernel32.dll", SetLastError=true)] static extern UIntPtr VirtualQueryEx(IntPtr process, ulong address, out Region region, UIntPtr size);
  [DllImport("kernel32.dll")] static extern bool CloseHandle(IntPtr handle);
  static byte[] Read(IntPtr handle, ulong address, int length) {
   var data = new byte[length]; UIntPtr actual;
   if (!ReadProcessMemory(handle, address, data, (UIntPtr)length, out actual) || actual.ToUInt64() != (ulong)length)
    throw new Win32Exception(Marshal.GetLastWin32Error(), "ReadProcessMemory");
   return data;
  }
  static uint Physical(byte[] ram, uint cr3, uint va) {
   uint pde = BitConverter.ToUInt32(ram, (int)((cr3 & 0xfffff000) + (va >> 22) * 4));
   if ((pde & 1) == 0) return uint.MaxValue;
   if ((pde & 128) != 0) return (pde & 0xffc00000) + (va & 0x3fffff);
   uint table = pde & 0xfffff000;
   if (table > ram.Length - 4096) return uint.MaxValue;
   uint pte = BitConverter.ToUInt32(ram, (int)(table + ((va >> 12) & 1023) * 4));
   return (pte & 1) != 0 ? (pte & 0xfffff000) + (va & 4095) : uint.MaxValue;
  }
  static bool Matches(byte[] ram, uint cr3, uint va, byte[] expected) {
   uint physical = Physical(ram, cr3, va);
   if (physical > ram.Length - expected.Length) return false;
   for (int i = 0; i < expected.Length; ++i) if (ram[physical + i] != expected[i]) return false;
   return true;
  }
  static bool MatchesHost(IntPtr handle, ulong ramBase, uint cr3, uint va, byte[] expected) {
   uint pde = BitConverter.ToUInt32(Read(handle, ramBase + (cr3 & 0xfffff000) + (va >> 22) * 4, 4), 0);
   if ((pde & 1) == 0) return false;
   uint physical;
   if ((pde & 128) != 0) physical = (pde & 0xffc00000) + (va & 0x3fffff);
   else {
    uint table = pde & 0xfffff000;
    uint pte = BitConverter.ToUInt32(Read(handle, ramBase + table + ((va >> 12) & 1023) * 4, 4), 0);
    if ((pte & 1) == 0) return false;
    physical = (pte & 0xfffff000) + (va & 4095);
   }
   byte[] actual = Read(handle, ramBase + physical, expected.Length);
   for (int i = 0; i < expected.Length; ++i) if (actual[i] != expected[i]) return false;
   return true;
  }
  public static byte[] Capture(int pid, ulong requestedBase, ulong offset, int length, uint cr3, uint signatureVa, byte[] expected, out ulong found) {
   IntPtr handle = OpenProcess(0x410, false, pid); // PROCESS_QUERY_INFORMATION | PROCESS_VM_READ
   if (handle == IntPtr.Zero) throw new Win32Exception(Marshal.GetLastWin32Error(), "OpenProcess read only");
   try {
    found = requestedBase;
    if (found == 0) {
     ulong address = 0;
     while (address < 0x00007fffffffffff) {
      Region region;
      if (VirtualQueryEx(handle, address, out region, (UIntPtr)Marshal.SizeOf<Region>()) == UIntPtr.Zero) break;
      if (region.State == 0x1000 && region.RegionSize == 0x4000000 && (region.Protect & 0x101) == 0) {
       try {
        byte[] ram = Read(handle, region.BaseAddress, 0x4000000);
        if (Matches(ram, cr3, signatureVa, expected)) {
         if (found != 0 && found != region.BaseAddress) throw new InvalidOperationException("Multiple validated Xbox RAM candidates.");
         found = region.BaseAddress;
        }
       } catch (Win32Exception) {}
      }
      ulong next = region.BaseAddress + region.RegionSize;
      if (next <= address) break;
      address = next;
     }
    }
    if (found == 0) throw new InvalidOperationException("No validated Xbox RAM allocation found.");
    if (!MatchesHost(handle, found, cr3, signatureVa, expected)) throw new InvalidOperationException("RAM code signature mismatch.");
    return Read(handle, found + offset, length);
   } finally { CloseHandle(handle); }
  }
 }
}
'@
}

$xbePath = [IO.Path]::GetFullPath($Xbe)
$xbeBytes = [IO.File]::ReadAllBytes($xbePath)
$imageBase = [BitConverter]::ToUInt32($xbeBytes, 0x104)
$sectionCount = [BitConverter]::ToUInt32($xbeBytes, 0x11C)
$sectionTable = [BitConverter]::ToUInt32($xbeBytes, 0x120) - $imageBase
$expected = $null
for ($i = 0; $i -lt $sectionCount; ++$i) {
    $section = $sectionTable + $i * 56
    $va = [BitConverter]::ToUInt32($xbeBytes, $section + 4)
    $rawSize = [BitConverter]::ToUInt32($xbeBytes, $section + 16)
    if ($SignatureAddress -ge $va -and $SignatureAddress + 32 -le $va + $rawSize) {
        $rawOffset = [BitConverter]::ToUInt32($xbeBytes, $section + 12) + $SignatureAddress - $va
        $expected = [byte[]]$xbeBytes[$rawOffset..($rawOffset + 31)]
        break
    }
}
if (!$expected) { throw ('Signature address 0x{0:X8} is not in an XBE raw section.' -f $SignatureAddress) }

$found = [UInt64]0
$bytes = [GodzillaDammParityHostRam.Reader]::Capture(
    $XemuPid, $RamBase, $GuestAddress, $Length, $Cr3, $SignatureAddress, $expected, [ref]$found)
$file = [IO.File]::Open($output, [IO.FileMode]::CreateNew)
try { $file.Write($bytes, 0, $bytes.Length) } finally { $file.Dispose() }
[ordered]@{
    schema = 1; source = 'xemu-host-ram'; pid = $XemuPid
    ramBase = ('0x{0:X}' -f $found); cr3 = ('0x{0:X8}' -f $Cr3)
    signatureAddress = ('0x{0:X8}' -f $SignatureAddress)
    guestAddress = $GuestAddress; length = $Length
    capturedAt = [DateTime]::UtcNow.ToString('o'); output = $output
    xbeSha256 = (Get-FileHash -LiteralPath $xbePath -Algorithm SHA256).Hash
    consistency = 'Caller must pause after a GPU flush; the savevm-to-stop gap is not atomic.'
} | ConvertTo-Json | Tee-Object -FilePath "$output.json"
