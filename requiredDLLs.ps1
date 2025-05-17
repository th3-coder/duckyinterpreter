# install-dlls.ps1

$exePath = Split-Path -Parent $MyInvocation.MyCommand.Definition
$dllList = @(
    "api-ms-win-core-synch-l1-2-0.dll",
    "clbcatq.dll",
    "combase.dll",
    "comctl32.dll",
    "comdlg32.dll",
    "gdi32.dll",
    "gdi32full.dll",
    "imm32.dll",
    "kernel.appcore.dll",
    "kernel32.dll",
    "libgcc_s_dw2-1.dll",
    "libstdc++-6.dll",
    "libwinpthread-1.dll",
    "msvcrt.dll",
    "ole32.dll",
    "oleaut32.dll",
    "rpcrt4.dll",
    "sechost.dll",
    "shell32.dll",
    "shlwapi.dll",
    "sspicli.dll",
    "user32.dll",
    "ucrtbase.dll",
    "win32u.dll",
    "windows.storage.dll",
    "winmm.dll",
    "wldcore.dll",
    "wldlog.dll"
)

Write-Host "Checking for required DLLs in: $exePath"

$missing = @()

foreach ($dll in $dllList) {
    $dllPath = Join-Path $exePath $dll
    if (-not (Test-Path $dllPath)) {
        $missing += $dll
    }
}

if ($missing.Count -eq 0) {
    Write-Host "✅ All required DLLs are present."
} else {
    Write-Host "❌ Missing DLLs:"
    $missing | ForEach-Object { Write-Host " - $_" }
}
