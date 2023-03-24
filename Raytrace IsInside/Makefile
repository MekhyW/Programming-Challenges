CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O0 -g
LFLAGS=-lm
OBJCMD=$(CC) $(CFLAGS) $< -c
EXECMD=$(CC) $^ -o $@ $(LFLAGS)
OBJS=geometry.o drawing.o unit_test.o integration_test.o
EXEC=unit_test integration_test

all: $(EXEC)

geometry.o: geometry.c geometry.h
	$(OBJCMD)

drawing.o: drawing.c drawing.h geometry.h
	$(OBJCMD)

unit_test.o: unit_test.c geometry.h drawing.h
	$(OBJCMD)

integration_test.o: integration_test.c geometry.h drawing.h
	$(OBJCMD)

unit_test: unit_test.o geometry.o drawing.o
	$(EXECMD)

integration_test: integration_test.o geometry.o drawing.o
	$(EXECMD)

clean:
	rm -f $(OBJS)

destroy: clean
	rm -f $(EXEC) unit_outputs/*.svg integration_outputs/*.svg
