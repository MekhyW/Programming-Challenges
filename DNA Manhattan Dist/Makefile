CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O0 -g
LFLAGS=
OBJCMD=$(CC) $(CFLAGS) $< -c
EXECMD=$(CC) $^ -o $@ $(LFLAGS)
OBJS=dna.o unit_test.o integration_test.o
EXEC=unit_test integration_test

all: $(EXEC)

dna.o: dna.c dna.h
	$(OBJCMD)

unit_test.o: unit_test.c dna.h
	$(OBJCMD)

integration_test.o: integration_test.c dna.h
	$(OBJCMD)

unit_test: unit_test.o dna.o
	$(EXECMD)

integration_test: integration_test.o dna.o
	$(EXECMD)

clean:
	rm -f $(OBJS)

destroy: clean
	rm -f $(EXEC)
