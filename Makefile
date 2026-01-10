# Makefile for LaTeX report compilation
# Usage: make report

LATEX = pdflatex
BIBTEX = bibtex
TEX_FILE = report.tex
PDF_FILE = report.pdf

.PHONY: all clean report

all: report

report: $(PDF_FILE)

$(PDF_FILE): $(TEX_FILE)
	$(LATEX) $(TEX_FILE)
	$(LATEX) $(TEX_FILE)  # Second pass for references
	@echo "Report compiled successfully: $(PDF_FILE)"

clean:
	rm -f *.aux *.log *.out *.toc *.bbl *.blg *.synctex.gz
	@echo "Cleaned LaTeX auxiliary files"

cleanall: clean
	rm -f $(PDF_FILE)
	@echo "Removed PDF and all auxiliary files"
