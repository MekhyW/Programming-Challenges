#ifndef PQUEUE_INT_H
#define PQUEUE_INT_H

struct _pqueue_int;

typedef struct _pqueue_int pqueue_int;

pqueue_int *pqueue_int_new(int capacity);
void pqueue_int_delete(pqueue_int **_q);
int pqueue_int_empty(pqueue_int *q);
int pqueue_int_full(pqueue_int *q);
void pqueue_int_insert(pqueue_int *q, int value);
int pqueue_int_remove(pqueue_int *q);

#endif
