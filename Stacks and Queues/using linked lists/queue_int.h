#ifndef QUEUE_INT_H
#define QUEUE_INT_H

struct _queue_int;

typedef struct _queue_int queue_int;

queue_int *queue_int_new();
void queue_int_delete(queue_int **_q);
int queue_int_empty(queue_int *q);
void queue_int_put(queue_int *q, int value);
void queue_int_genput(queue_int *q, int value, int index);
int queue_int_get(queue_int *q);
int queue_int_genget(queue_int *q, int index);

#endif
