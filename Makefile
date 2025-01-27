LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:

document_color: | build
	$(LATEXCMD) "\def\colormode{1} \input{content/kactl.tex}" && $(LATEXCMD) "\def\colormode{1} \input{content/kactl.tex}"
	cp build/kactl.pdf notas.pdf

document_bw: | build
	$(LATEXCMD) content/kactl.tex && $(LATEXCMD) content/kactl.tex
	cp build/kactl.pdf notas_bn.pdf

clean:
	$(RM) -r build/

.PHONY: document_color document_bw clean

build:
	mkdir -p build/
