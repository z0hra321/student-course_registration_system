# How to Generate PDF from LaTeX Report

This document provides multiple methods to compile the LaTeX report (`report.tex`) into a PDF.

## Method 1: Automatic via GitHub Actions (Recommended)

The repository includes a GitHub Actions workflow that automatically compiles the PDF whenever `report.tex` is updated.

### How it works:
1. Push changes to `report.tex` or the workflow file
2. GitHub Actions automatically compiles the LaTeX document
3. The generated `report.pdf` is committed back to the repository
4. Download the PDF from the repository

### Manual Trigger:
1. Go to the **Actions** tab in your GitHub repository
2. Select **Build LaTeX Report PDF** workflow
3. Click **Run workflow** button
4. Wait for compilation to complete (usually 2-5 minutes)
5. Download the PDF from the artifacts or find it in the repository

## Method 2: Local Compilation with MiKTeX (Windows)

### Step 1: Install MiKTeX

**Option A: Using winget (Recommended)**
```powershell
winget install --id MiKTeX.MiKTeX --accept-package-agreements --accept-source-agreements
```

**Option B: Manual Installation**
1. Download MiKTeX from https://miktex.org/download
2. Run the installer
3. Choose "Install packages on-the-fly: Yes" (recommended)
4. Complete the installation

### Step 2: Add MiKTeX to PATH
After installation, restart your terminal or add MiKTeX to PATH manually:
```powershell
$env:Path += ";C:\Users\$env:USERNAME\AppData\Local\Programs\MiKTeX\miktex\bin\x64"
```

### Step 3: Compile the Report
```powershell
cd "C:\Users\csvde\OneDrive\Desktop\student-registration\student-registration"
pdflatex report.tex
pdflatex report.tex  # Second pass for references
```

The PDF will be generated as `report.pdf` in the same directory.

## Method 3: Using Overleaf (Online - No Installation)

1. Go to https://www.overleaf.com/
2. Create a free account (if needed)
3. Click **New Project** > **Upload Project**
4. Upload `report.tex` file
5. Overleaf will automatically compile the PDF
6. Download the compiled PDF

### Note for Overleaf:
- You may need to upload additional files if the document references them
- All required LaTeX packages are usually pre-installed

## Method 4: Using Docker (Advanced)

If you have Docker installed:

```bash
docker run --rm -v "$PWD":/workspace -w /workspace texlive/texlive:latest pdflatex report.tex
docker run --rm -v "$PWD":/workspace -w /workspace texlive/texlive:latest pdflatex report.tex
```

## Method 5: Using WSL (Windows Subsystem for Linux)

If you have WSL installed:

```bash
# Install TeX Live in WSL
sudo apt update
sudo apt install texlive-full

# Compile
cd /mnt/c/Users/csvde/OneDrive/Desktop/student-registration/student-registration
pdflatex report.tex
pdflatex report.tex
```

## Troubleshooting

### Missing Packages Error

If you get errors about missing packages:

**MiKTeX (Windows):**
- Packages will be installed automatically when you compile
- Or use MiKTeX Console to install packages manually

**TeX Live (Linux):**
```bash
sudo tlmgr install <package-name>
```

### Common Missing Packages

If compilation fails, you might need:
- `algorithms` package
- `algorithmicx` package (for `algpseudocode`)
- `pgf` package (for TikZ)
- `listings` package

### Checking Installation

Verify LaTeX is installed:
```bash
pdflatex --version
```

### Viewing the PDF

After compilation:
- Windows: Double-click `report.pdf`
- Or use: `start report.pdf`
- Or use any PDF viewer

## Quick Summary

**Fastest Method:** Use GitHub Actions (Method 1) - no installation needed, automatic compilation.

**Best for Editing:** Install MiKTeX locally (Method 2) - compile instantly while editing.

**Best for Testing:** Use Overleaf (Method 3) - instant online compilation.

## Current Status

✅ GitHub Actions workflow is configured and active
✅ PDF will be auto-generated on each push to `report.tex`
✅ Check the **Actions** tab in GitHub to see compilation status
