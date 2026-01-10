# LaTeX Report Compilation Guide

This directory contains the LaTeX source files for the comprehensive project report.

## Files

- `report.tex` - Main LaTeX document containing the complete project report
- `Makefile` - Build automation for compiling the report
- `REPORT_README.md` - This file

## Prerequisites

To compile the LaTeX report, you need:

1. **LaTeX Distribution**:
   - **Linux**: `texlive-full` or `texlive-base` + required packages
   - **macOS**: MacTeX distribution
   - **Windows**: MiKTeX or TeX Live

2. **Required Packages**:
   - `geometry`
   - `graphicx`
   - `amsmath`
   - `listings`
   - `xcolor`
   - `hyperref`
   - `booktabs`
   - `algorithm`
   - `algorithmicx` (for `algpseudocode`)
   - `tikz`
   - `fancyhdr`
   - `enumitem`
   - `titlesec`

## Installation

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install texlive-full
# OR minimal installation:
sudo apt install texlive-base texlive-latex-extra texlive-latex-recommended
```

### Linux (Fedora)
```bash
sudo dnf install texlive-scheme-full
# OR minimal installation:
sudo dnf install texlive-latex texlive-latex-extras
```

### macOS
```bash
# Install MacTeX (full distribution recommended)
brew install --cask mactex
# OR minimal installation:
brew install --cask basictex
sudo tlmgr update --self
sudo tlmgr install collection-fontsrecommended collection-latexextra
```

### Windows
1. Download and install **MiKTeX** from https://miktex.org/
2. Packages will be installed automatically on first compilation
3. Or install **TeX Live** from https://www.tug.org/texlive/

## Compilation

### Method 1: Using Makefile (Recommended)

```bash
# Compile the report
make report

# Clean auxiliary files
make clean

# Clean everything including PDF
make cleanall
```

### Method 2: Direct pdflatex

```bash
# First pass
pdflatex report.tex

# Second pass (for references and table of contents)
pdflatex report.tex

# The PDF will be generated as report.pdf
```

### Method 3: Using latexmk (if available)

```bash
latexmk -pdf report.tex
```

## Output

After successful compilation, you will find:
- `report.pdf` - The compiled PDF document
- Auxiliary files: `.aux`, `.log`, `.out`, `.toc`, etc. (can be removed)

## Report Contents

The LaTeX report includes:

1. **Introduction** - Project overview and objectives
2. **System Architecture** - High-level design and components
3. **Algorithm Design** - Detailed algorithms with pseudocode
4. **Time Complexity Analysis** - Comprehensive complexity tables
5. **Implementation Details** - Code structure and features
6. **Build System** - CMake configuration
7. **Testing and Validation** - Test methodology
8. **Usage Examples** - CLI and GUI usage
9. **Performance Analysis** - Benchmark results
10. **Conclusion** - Summary and future work

## Troubleshooting

### Missing Packages

If compilation fails due to missing packages:

**MiKTeX (Windows):**
- Packages will be installed automatically
- Or use Package Manager GUI

**TeX Live (Linux/macOS):**
```bash
sudo tlmgr install <package-name>
```

**Ubuntu/Debian:**
```bash
sudo apt install texlive-latex-extra  # Most common packages
```

### Common Errors

**Error: File `algorithm.sty' not found**
```bash
# Install algorithmic packages
sudo apt install texlive-science  # Linux
# OR
sudo tlmgr install algorithms algorithmicx  # TeX Live
```

**Error: File `tikz.sty' not found**
```bash
# Install TikZ
sudo apt install texlive-pictures  # Linux
# OR
sudo tlmgr install pgf  # TeX Live
```

### Overfull/Underfull Hbox Warnings

These are formatting warnings and won't prevent compilation. The PDF will still be generated correctly.

## Viewing the PDF

After compilation, open `report.pdf` with any PDF viewer:
- Linux: `xdg-open report.pdf`
- macOS: `open report.pdf`
- Windows: Double-click `report.pdf`

## Customization

To customize the report:
1. Edit `report.tex` to modify content
2. Adjust formatting by modifying the preamble (before `\begin{document}`)
3. Add figures by placing image files and using `\includegraphics{filename}`

## Notes

- The report requires two compilation passes to resolve references and generate the table of contents
- Code listings use the `listings` package for syntax highlighting
- Algorithms are typeset using the `algorithm` and `algorithmicx` packages
- The document uses A4 paper size with 1-inch margins

## License

The report is part of the Student Registration System project. See the main repository for license information.
