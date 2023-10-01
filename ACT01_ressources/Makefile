SRC=$(wildcard *.c)
EXE=$(SRC:.c=)
CFLAGS=-std=c99 -I ${HOME}/local/include -L ${HOME}/local/lib
LDLIBS=-limago -lpng -ljpeg -lm

ALL: $(EXE)

clean:
	rm $(EXE)

