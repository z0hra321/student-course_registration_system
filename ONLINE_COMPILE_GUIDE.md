# Online LaTeX Compilation Services

## 🌐 Best Websites to Compile LaTeX Files

### 1. **Overleaf** (Most Popular) ⭐
**Website**: https://www.overleaf.com/

**Features**:
- ✅ Free account available
- ✅ Real-time collaboration
- ✅ Auto-compilation
- ✅ Large template library
- ✅ Version history
- ✅ Export to PDF, ZIP, or source

**How to Use**:
1. Go to https://www.overleaf.com/
2. Click "Register" (free) or sign in with Google/GitHub
3. Click "New Project" → "Upload Project"
4. Upload your `report.tex` file
5. Wait for automatic compilation (10-30 seconds)
6. Click "Download" → "PDF" to get your compiled PDF

**Best For**: Most users, collaboration, professional documents

---

### 2. **LaTeX Base**
**Website**: https://latexbase.com/

**Features**:
- ✅ No sign-up required
- ✅ Simple interface
- ✅ Quick compilation
- ✅ Share via URL

**How to Use**:
1. Go to https://latexbase.com/
2. Paste your LaTeX code or upload file
3. Click "Compile"
4. Download the PDF

**Best For**: Quick compilation without account

---

### 3. **Papeeria**
**Website**: https://www.papeeria.com/

**Features**:
- ✅ Free online editor
- ✅ Collaboration features
- ✅ Git integration
- ✅ Multiple LaTeX distributions

**How to Use**:
1. Go to https://www.papeeria.com/
2. Sign up (free)
3. Create new project
4. Upload `report.tex`
5. Compile and download

**Best For**: Git integration, advanced features

---

### 4. **CoCalc**
**Website**: https://cocalc.com/

**Features**:
- ✅ LaTeX support
- ✅ Jupyter notebooks
- ✅ Free tier available
- ✅ Collaborative editing

**How to Use**:
1. Go to https://cocalc.com/
2. Sign up for free account
3. Create new LaTeX file
4. Upload and compile

**Best For**: Academic work, research papers

---

### 5. **LaTeX.Online** (API Service)
**Website**: https://latexonline.cc/

**Features**:
- ✅ API-based compilation
- ✅ Command-line tool
- ✅ Good for automation
- ✅ No sign-up needed

**How to Use**:
```bash
# Via command line
curl --data-urlencode "compiler=pdflatex" \
     --data-urlencode "text=@report.tex" \
     https://latexonline.cc/compile > report.pdf
```

**Best For**: Automation, CI/CD pipelines

---

## 📋 Quick Comparison

| Service | Free | Sign-up | Collaboration | Best For |
|---------|------|---------|---------------|----------|
| **Overleaf** | ✅ | Required | ✅ | Most users |
| **LaTeX Base** | ✅ | No | ❌ | Quick compile |
| **Papeeria** | ✅ | Required | ✅ | Git users |
| **CoCalc** | ✅ | Required | ✅ | Academic |
| **LaTeX.Online** | ✅ | No | ❌ | Automation |

---

## 🚀 Recommended: Overleaf (Step-by-Step)

### Step 1: Create Account
1. Visit: https://www.overleaf.com/
2. Click "Register" (top right)
3. Use email or Google/GitHub sign-in
4. Verify email if needed

### Step 2: Upload Your File
1. Click "New Project" (green button)
2. Select "Upload Project"
3. Choose your `report.tex` file
   - Location: `C:\Users\csvde\OneDrive\Desktop\student-registration\student-registration\report.tex`
4. Click "Upload"

### Step 3: Add Images (if needed)
If your report includes PNG images:
1. Click "Files" in left sidebar
2. Click "Upload" (or drag & drop)
3. Upload all PNG files:
   - `studentstab.png`
   - `coursetab.png`
   - `Registerationtab.png`
   - `mycoursestab.png`
   - `Waitlisttab.png`

### Step 4: Compile
- Overleaf compiles automatically
- Look for green checkmark (✓) = Success
- Red X (✗) = Error (check log)

### Step 5: Download PDF
1. Click "Download" button (top menu)
2. Select "PDF"
3. Save as `report.pdf`

### Step 6: Add to GitHub
```powershell
cd "C:\Users\csvde\OneDrive\Desktop\student-registration\student-registration"
git add report.pdf
git commit -m "Add compiled LaTeX report PDF"
git push origin main
```

---

## ⚠️ Important Notes

### For Your Project:
- Your `report.tex` includes images (`studentstab.png`, etc.)
- Make sure to upload **all PNG files** along with `report.tex` to Overleaf
- Images must be in the same directory as the `.tex` file

### Common Issues:
1. **Missing Images**: Upload all PNG files to Overleaf
2. **Package Errors**: Overleaf usually installs packages automatically
3. **Compilation Errors**: Check the "Logs and output files" tab

---

## 🔗 Direct Links

- **Overleaf**: https://www.overleaf.com/
- **LaTeX Base**: https://latexbase.com/
- **Papeeria**: https://www.papeeria.com/
- **CoCalc**: https://cocalc.com/
- **LaTeX.Online**: https://latexonline.cc/

---

## 💡 Pro Tip

**For your project**, use **Overleaf** because:
- ✅ Handles all required packages automatically
- ✅ Supports images easily
- ✅ Professional output
- ✅ Free and reliable
- ✅ Can share with team members

**Time Required**: 2-3 minutes total!
