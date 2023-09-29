# aggiorna questo nome con il nome del file .tex che contiene la tua tesi
finalname = esempioTesi

# lista qui di seguito tutti i file aggiuntivi .tex (se ci sono) che compongono 
# la tua tesi (tipicamente sono quelli importati con il comando \input{miofile} dentro
# il file principale .tex
included_latex_sources = \
	ringraziamenti.tex \
	introduzione.tex \
	capitolo_1.tex \
	capitolo_2.tex \
	capitolo_3.tex \
	conclusioni.tex

# lista qui le figure che ti servono 
psfiles = \
	figure/uniroma3-logo.eps \
	figure/esempio-figura-1.eps \
	figure/esempio-figura-2.eps 

$(finalname): $(included_latex_sources) $(psfiles) $(finalname).tex
	latex $(finalname).tex

%.bbl: %.aux
	bibtex $<

%.ps: %.fig
	fig2dev -Leps $< $@

%.eps: %.fig
	fig2dev -Leps $< $@

%.ps: %.gif
	convert $< $@

%.ps: %.jpg
	convert $< $@

clean:
	rm -f $(finalname).ps
	rm -f $(finalname).log
	rm -f $(finalname).out
	rm -f $(finalname).toc
	rm -f $(finalname).lof
	rm -f *~
	rm -f *.bak
	rm -f figure/*.bak
	rm -f *.toc
	rm -f *.aux
	rm -f *.blg
	rm -f *.dvi
	rm -f *.log
	rm -f temp.tex
	rm -f *.idx
	rm -f *.ilg
	rm -f *.ind


index: 
	latex $(finalname).tex
	makeindex $(finalname)
	latex $(finalname).tex
	latex $(finalname).tex

bib:
	latex $(finalname).tex
	bibtex $(finalname)
	latex $(finalname).tex
	latex $(finalname).tex

ps: $(finalname)
	dvips -t letter $(finalname).dvi -o

pdf: $(finalname)
	dvips -Ppdf $(finalname).dvi -o $(finalname).ps
	ps2pdf $(finalname).ps $(finalname).pdf
