TEX = $(wildcard sections/*.tex)


thesis.pdf: $(TEX)
	pdflatex -shell-escape thesis.tex

clean:
	rm *lot *toc *aux *out *log *lof

