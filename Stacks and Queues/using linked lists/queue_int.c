#include <stdlib.h>

#include "queue_int.h"

struct _node {
    int value;
    struct _node *next;
};

typedef struct _node node;

struct _queue_int {
    node *first;
    node *last;
};

queue_int *queue_int_new() {
    queue_int *q = malloc(sizeof(queue_int));
    q->first = NULL;
    q->last = NULL;
    return q;
}

void queue_int_delete(queue_int **_q) {
    queue_int *q = *_q;
    node *n = q->first;
    while (n != NULL) {
        node *next = n->next;
        free(n);
        n = next;
    }
    free(q);
    *_q = NULL;
}

int queue_int_empty(queue_int *q) {
    return q->last == NULL;
}

void queue_int_put(queue_int *q, int value) {
    node *n = malloc(sizeof(node));
    n->value = value;
    n->next = NULL;
    if (q->last != NULL) {
        q->last->next = n;
    } else {
        q->first = n;
    }
    q->last = n;
}

void queue_int_genput(queue_int *q, int value, int index) {
    node *p;
    node *n;
    //get size of queue
    int size = 0;
    for (n = q->first; n != NULL; n = n->next) {
        size++;
    }
    //set p (previous) and n (current)
    p = NULL;
    n = q->first;
    for (int i = 0; i < size - index; i++) {
        p = n;
        n = n->next;
    }
    //put
    n = malloc(sizeof(node));
    n->value = value;
    //connect with previous and next
    if (p != NULL) {
        n->next = p->next;
        p->next = n;
    } else {
        n->next = q->first;
        q->first = n;
    }
    if (index == 0) {
      q->last = n;
    }
}

int queue_int_get(queue_int *q) {
    node *n = q->first;
    q->first = n->next;
    if (q->first == NULL) {
        q->last = NULL;
    }
    int value = n->value;
    free(n);
    return value;
}

int queue_int_genget(queue_int *q, int index) {
    node *p;
    node *n;
    //get size of queue
    int size = 0;
    for (n = q->first; n != NULL; n = n->next) {
        size++;
    }
    //set p (previous) and n (current)
    p = NULL;
    n = q->first;
    for (int i = 0; i < size - index; i++) {
        p = n;
        n = n->next;
    }
    //connect with previous and next
    if (p != NULL) {
        p->next = n->next;
    } else {
        q->first = n->next;
    }
    if (index == 0) {
      q->last = p;
    }
    //get value
    int value = n->value;
    free(n);
    return value;
}
