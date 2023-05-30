CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O0 -g
LFLAGS=
OBJCMD=$(CC) $(CFLAGS) $< -c
EXECMD=$(CC) $^ -o $@ $(LFLAGS)
OBJS=set_int.o set_int_test.o
EXEC=set_int_test

all: $(EXEC)

set_int.o: set_int.c set_int.h
	$(OBJCMD)

set_int_test.o: set_int_test.c set_int.h
	$(OBJCMD)

set_int_test: set_int_test.o set_int.o
	$(EXECMD)

clean:
	rm -f $(OBJS)

destroy: clean
	rm -f $(EXEC) set_int_test.txt
