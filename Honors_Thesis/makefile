TEX = $(wildcard sections/*.tex)
IMG = $(wildcard img/*.png)


thesis.pdf: thesis.tex $(TEX) $(IMG)
	pdflatex -shell-escape thesis.tex

clean:
	rm *lot *toc *aux *out *log *lof

