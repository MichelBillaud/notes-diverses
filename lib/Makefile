HTMLDIR = ../HTML-PUBLIC
PDFDIR  = ../PDF-PUBLIC

include ../lib/common.mk

publish: all
	rsync -av --delete  $(HTMLDIR)/* ~/sites/labri/notes
