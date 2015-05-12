ALL= generador main
ALL:$(ALL)
PHONY: clean
CFLAGS= -g
LDFLAGS=-lpthread

clean:
	\rm -fr $(ALL) *.dSYM
