# Script to get the compiled PDF from GitHub Actions or compile locally

param(
    [string]$RepoOwner = "z0hra321",
    [string]$RepoName = "student-registration",
    [string]$Branch = "main"
)

Write-Host "=== Getting LaTeX PDF Report ===" -ForegroundColor Cyan

# Check if PDF already exists locally
if (Test-Path "report.pdf") {
    Write-Host "PDF already exists locally!" -ForegroundColor Green
    Get-Item "report.pdf" | Select-Object Name, Length, LastWriteTime
    exit 0
}

# Try to get from GitHub Actions artifact
Write-Host "`nChecking GitHub Actions for compiled PDF..." -ForegroundColor Yellow

try {
    $headers = @{
        "Accept" = "application/vnd.github.v3+json"
    }
    
    # Get latest workflow run
    $runsUrl = "https://api.github.com/repos/$RepoOwner/$RepoName/actions/runs?per_page=1"
    $response = Invoke-RestMethod -Uri $runsUrl -Headers $headers -Method Get
    
    if ($response.workflow_runs -and $response.workflow_runs.Count -gt 0) {
        $run = $response.workflow_runs[0]
        Write-Host "Found workflow run: $($run.status) - $($run.conclusion)" -ForegroundColor Cyan
        
        if ($run.status -eq "completed" -and $run.conclusion -eq "success") {
            Write-Host "Workflow completed successfully! PDF should be in repository." -ForegroundColor Green
            Write-Host "`nTry: git pull origin $Branch" -ForegroundColor Yellow
            Write-Host "The PDF should be auto-committed by GitHub Actions." -ForegroundColor Yellow
        } else {
            Write-Host "Workflow status: $($run.status)" -ForegroundColor Yellow
            Write-Host "Check: https://github.com/$RepoOwner/$RepoName/actions" -ForegroundColor Cyan
        }
    }
} catch {
    Write-Host "Could not check GitHub Actions: $_" -ForegroundColor Yellow
}

Write-Host "`n=== Manual Compilation Options ===" -ForegroundColor Cyan
Write-Host "1. Wait for GitHub Actions (automatic)" -ForegroundColor White
Write-Host "   The PDF will be auto-generated and committed" -ForegroundColor Gray

Write-Host "`n2. Use Overleaf (fastest, no installation):" -ForegroundColor White
Write-Host "   a. Go to: https://www.overleaf.com/" -ForegroundColor Cyan
Write-Host "   b. Sign up (free)" -ForegroundColor Gray
Write-Host "   c. New Project > Upload Project" -ForegroundColor Gray
Write-Host "   d. Upload report.tex" -ForegroundColor Gray
Write-Host "   e. Download the compiled PDF" -ForegroundColor Gray
Write-Host "   f. Save as report.pdf in this directory" -ForegroundColor Gray

Write-Host "`n3. Install MiKTeX locally:" -ForegroundColor White
Write-Host "   winget install --id MiKTeX.MiKTeX" -ForegroundColor Cyan
Write-Host "   Then run: pdflatex report.tex (twice)" -ForegroundColor Gray

Write-Host "`n4. Check if PDF was already committed:" -ForegroundColor White
Write-Host "   git pull origin $Branch" -ForegroundColor Cyan
