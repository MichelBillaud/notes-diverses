HTMLDIR = ../HTML-PUBLIC
PDFDIR  = ../PDF-PRIVE

include ../lib/common.mk

publish: all
	rsync -av --delete  $(HTMLDIR)/* ~/sites/labri/notes
