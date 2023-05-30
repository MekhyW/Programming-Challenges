#include <stdlib.h>

#include "pqueue_int.h"

struct _pqueue_int {
    int capacity;
    int *data;
    int size;
};

int parent(int i) {
    return (i - 1) / 2;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

void swap(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void ascend(int v[], int i) {
    while (i > 0) {
        int p = parent(i);
        if (v[p] > v[i]) {
            swap(v, i, p);
            i = p;
        } else {
            break;
        }
    }
}

void descend(int v[], int n, int i) {
    while (1) {
        int l = left(i);
        int r = right(i);
        int m = i;
        if (l < n && v[l] < v[m]) {
            m = l;
        }
        if (r < n && v[r] < v[m]) {
            m = r;
        }
        if (m != i) {
            swap(v, i, m);
            i = m;
        } else {
            break;
        }
    }
}

pqueue_int *pqueue_int_new(int capacity) {
    pqueue_int *q = malloc(sizeof(pqueue_int));
    q->capacity = capacity;
    q->data = malloc(capacity * sizeof(int));
    q->size = 0;
    return q;
}

void pqueue_int_delete(pqueue_int **_q) {
    pqueue_int *q = *_q;
    free(q->data);
    free(q);
    *_q = NULL;
}

int pqueue_int_empty(pqueue_int *q) {
    return q->size == 0;
}

int pqueue_int_full(pqueue_int *q) {
    return q->size == q->capacity;
}

void pqueue_int_insert(pqueue_int *q, int value) {
    q->data[q->size] = value;
    ascend(q->data, q->size);
    q->size++;
}

int pqueue_int_remove(pqueue_int *q) {
    q->size--;
    int value = q->data[0];
    q->data[0] = q->data[q->size];
    descend(q->data, q->size, 0);
    return value;
}
