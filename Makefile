ALL= generador main
ALL:$(ALL)
PHONY:clean
CFLAGS= -g 
CPPFLAGS=-std=c++11
LDFLAGS=-lpthread

clean:
	\rm -fr $(ALL) *.dSYM
