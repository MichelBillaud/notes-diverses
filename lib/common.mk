
CSS = ../lib/s1.css

SRC = $(wildcard *.md)

HTML = $(addprefix $(HTMLDIR)/,$(addsuffix .html,$(basename $(SRC))))
TWOCOLPDF = $(addprefix $(PDFDIR)/,$(addsuffix .2col.pdf,$(basename $(SRC))))
PDF = $(addprefix $(PDFDIR)/,$(addsuffix .pdf,$(basename $(SRC))))

all: $(HTML) $(PDF)

$(HTMLDIR)/%.html: %.md $(CSS)
	pandoc  -N --toc -t html5  -c $(CSS) --self-contained  $<  -o $@

$(PDFDIR)/%.2col.pdf: %.md
	pandoc -t latex --pdf-engine=xelatex -N --toc --self-contained -V lang=fr -V papersize:a4 -V documentclass:extarticle -V classoption:twocolumn -o $@ $^

$(PDFDIR)/%.pdf: %.md
	pandoc -t latex --pdf-engine=xelatex -N --toc --self-contained -V lang=fr -V papersize:a4 -V documentclass:extarticle -o $@ $^

clean:
	$(RM) *~


