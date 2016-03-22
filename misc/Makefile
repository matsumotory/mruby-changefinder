#   the default target
all: ar

#   compile binary
ar:
	gcc -lm ar.c -o ar

test: ar
	./ar 10000 0.6 0.5 2000 5 1 0.0 1.0 > ar.tsv

.PHONY: ar
