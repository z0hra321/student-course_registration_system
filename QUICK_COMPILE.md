# Quick Guide: Compile LaTeX Report to PDF

## ⚡ Fastest Method: Use Overleaf (2 minutes)

### Step-by-Step Instructions:

1. **Go to Overleaf**: https://www.overleaf.com/

2. **Create Account** (if needed):
   - Click "Register" 
   - Use email or Google/GitHub sign-in (free)

3. **Create New Project**:
   - Click "New Project"
   - Select "Upload Project"

4. **Upload report.tex**:
   - Click "Select a .zip file or folder" OR
   - Drag and drop `report.tex` file from your computer
   - File: `C:\Users\csvde\OneDrive\Desktop\student-registration\student-registration\report.tex`

5. **Compile**:
   - Overleaf automatically compiles when you upload
   - Wait for "PDF successfully generated" message (green checkmark)

6. **Download PDF**:
   - Click the "Download" button (top left, next to Recompile)
   - Save the file as `report.pdf`

7. **Add to GitHub**:
   ```powershell
   cd "C:\Users\csvde\OneDrive\Desktop\student-registration\student-registration"
   # Copy the downloaded PDF to this directory
   git add report.pdf
   git commit -m "Add compiled LaTeX report PDF"
   git push origin main
   ```

**Time Required**: 2-3 minutes (no installation needed!)

---

## 🔧 Alternative: Install MiKTeX Locally

If you want to compile locally in the future:

### Windows Installation:

1. **Install MiKTeX**:
   ```powershell
   winget install --id MiKTeX.MiKTeX --accept-package-agreements --accept-source-agreements
   ```

2. **Wait for Installation** (5-10 minutes for full installation)

3. **Restart Terminal/PowerShell**

4. **Compile**:
   ```powershell
   cd "C:\Users\csvde\OneDrive\Desktop\student-registration\student-registration"
   pdflatex report.tex
   pdflatex report.tex
   ```

5. **The PDF will be generated as `report.pdf`**

---

## 🤖 Automatic: GitHub Actions

The repository is configured with GitHub Actions to automatically compile the PDF.

**To trigger manually:**
1. Go to: https://github.com/z0hra321/student-registration
2. Click "Actions" tab
3. Select "Build LaTeX Report PDF" workflow
4. Click "Run workflow" button
5. Wait 3-5 minutes
6. The PDF will be automatically added to the repository

---

## 📋 What You Need

For **Overleaf** (recommended):
- ✅ Internet connection
- ✅ Web browser
- ✅ 2-3 minutes

For **Local Compilation**:
- ✅ MiKTeX installed (~500MB)
- ✅ 10-15 minutes setup time
- ✅ Admin privileges (may be required)

---

## ✅ Verification

After compilation, verify the PDF exists:
```powershell
Test-Path report.pdf  # Should return True
Get-Item report.pdf   # Shows file details
```

---

## 🆘 Troubleshooting

**Overleaf Issues:**
- If compilation fails, check for missing packages
- All required packages should auto-install on Overleaf

**Local Issues:**
- If `pdflatex` not found, restart terminal after installation
- Check PATH: `$env:Path` should include MiKTeX bin directory
- Install missing packages: Use MiKTeX Console

**GitHub Actions Issues:**
- Check Actions tab for error messages
- PDF should appear in repository after successful run

---

## 📝 Quick Command Summary

```powershell
# Navigate to project
cd "C:\Users\csvde\OneDrive\Desktop\student-registration\student-registration"

# After getting PDF (from Overleaf or local compilation):
git add report.pdf
git commit -m "Add compiled LaTeX report PDF"
git push origin main
```

**Recommended**: Use **Overleaf** for the fastest, easiest compilation! 🚀
