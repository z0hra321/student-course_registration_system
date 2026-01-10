# PowerShell script to compile LaTeX report to PDF
# This script tries multiple methods to compile the LaTeX report

param(
    [string]$InputFile = "report.tex",
    [string]$OutputFile = "report.pdf"
)

Write-Host "=== LaTeX PDF Compilation Script ===" -ForegroundColor Cyan
Write-Host "Attempting to compile: $InputFile" -ForegroundColor Yellow

# Check if input file exists
if (-not (Test-Path $InputFile)) {
    Write-Host "Error: $InputFile not found!" -ForegroundColor Red
    exit 1
}

# Method 1: Try pdflatex if available
$pdflatexPaths = @(
    "pdflatex",
    "C:\Program Files\MiKTeX\miktex\bin\x64\pdflatex.exe",
    "$env:LOCALAPPDATA\Programs\MiKTeX\miktex\bin\x64\pdflatex.exe",
    "$env:USERPROFILE\AppData\Local\Programs\MiKTeX\miktex\bin\x64\pdflatex.exe"
)

$pdflatex = $null
foreach ($path in $pdflatexPaths) {
    if (Get-Command $path -ErrorAction SilentlyContinue) {
        $pdflatex = $path
        break
    } elseif (Test-Path $path) {
        $pdflatex = $path
        break
    }
}

if ($pdflatex) {
    Write-Host "Found pdflatex at: $pdflatex" -ForegroundColor Green
    Write-Host "Compiling LaTeX document..." -ForegroundColor Yellow
    
    try {
        & $pdflatex -interaction=nonstopmode $InputFile
        if ($LASTEXITCODE -eq 0) {
            Write-Host "First compilation pass completed" -ForegroundColor Green
            & $pdflatex -interaction=nonstopmode $InputFile
            if ($LASTEXITCODE -eq 0) {
                Write-Host "Second compilation pass completed" -ForegroundColor Green
                if (Test-Path $OutputFile) {
                    Write-Host "SUCCESS! PDF generated: $OutputFile" -ForegroundColor Green
                    Get-Item $OutputFile | Select-Object Name, Length, LastWriteTime
                    exit 0
                }
            }
        }
    } catch {
        Write-Host "Error during compilation: $_" -ForegroundColor Red
    }
} else {
    Write-Host "pdflatex not found locally" -ForegroundColor Yellow
}

# Method 2: Instructions for manual compilation
Write-Host "`n=== Alternative Methods ===" -ForegroundColor Cyan
Write-Host "1. Install MiKTeX:" -ForegroundColor Yellow
Write-Host "   winget install --id MiKTeX.MiKTeX" -ForegroundColor White
Write-Host "`n2. Use Overleaf (online):" -ForegroundColor Yellow
Write-Host "   https://www.overleaf.com/" -ForegroundColor White
Write-Host "   Upload $InputFile and download the PDF" -ForegroundColor White
Write-Host "`n3. Check GitHub Actions:" -ForegroundColor Yellow
Write-Host "   The PDF should be auto-generated via GitHub Actions" -ForegroundColor White
Write-Host "   Check: https://github.com/z0hra321/student-registration/actions" -ForegroundColor White

exit 1
