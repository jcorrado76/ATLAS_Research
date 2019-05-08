TEX = $(wildcard sections/*.tex)


thesis.pdf: thesis.tex $(TEX)
	pdflatex -shell-escape thesis.tex

clean:
	rm *lot *toc *aux *out *log *lof

