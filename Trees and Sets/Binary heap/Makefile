CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O0 -g
LFLAGS=
OBJCMD=$(CC) $(CFLAGS) $< -c
EXECMD=$(CC) $^ -o $@ $(LFLAGS)
OBJS=pqueue_int.o pqueue_int_test.o
EXEC=pqueue_int_test

all: $(EXEC)

pqueue_int.o: pqueue_int.c pqueue_int.h
	$(OBJCMD)

pqueue_int_test.o: pqueue_int_test.c pqueue_int.h
	$(OBJCMD)

pqueue_int_test: pqueue_int_test.o pqueue_int.o
	$(EXECMD)

clean:
	rm -f $(OBJS)

destroy: clean
	rm -f $(EXEC) pqueue_int_test.txt
