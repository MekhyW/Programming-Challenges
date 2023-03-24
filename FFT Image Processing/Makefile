CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O0 -g
LFLAGS=-lm
OBJCMD=$(CC) $(CFLAGS) $< -c
EXECMD=$(CC) $^ -o $@ $(LFLAGS)
OBJS=fourier.o image.o unit_test.o integration_test.o
EXEC=unit_test integration_test

all: $(EXEC)

fourier.o: fourier.c fourier.h
	$(OBJCMD)

image.o: image.c image.h fourier.h
	$(OBJCMD)

unit_test.o: unit_test.c fourier.h
	$(OBJCMD)

integration_test.o: integration_test.c fourier.h image.h
	$(OBJCMD)

unit_test: unit_test.o fourier.o
	$(EXECMD)

integration_test: integration_test.o fourier.o image.o
	$(EXECMD)

clean:
	rm -f $(OBJS)

destroy: clean
	rm -f $(EXEC) unit_outputs/*.txt integration_outputs/*.pgm
