SRC=$(wildcard *.c)
EXE=$(SRC:.c=)
CFLAGS=-std=c99
LDLIBS=-lfftw3 -limago -lpng -ljpeg  -lm

ALL: $(EXE)

clean:
	rm $(EXE)

