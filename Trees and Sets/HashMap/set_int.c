#include <stdlib.h>

#include "set_int.h"

struct _node {
    int value;
    struct _node *next;
};

typedef struct _node node;

struct _set_int {
    int capacity;
    int size;
    double factor;
    node **table;
};

void initialize(set_int *s) {
    s->table = malloc(s->capacity * sizeof(node *));
    for (int i = 0; i < s->capacity; i++) {
        s->table[i] = NULL;
    }
}

set_int *set_int_new(int capacity, double factor) {
    set_int *s = malloc(sizeof(set_int));
    s->capacity = capacity;
    s->size = 0;
    s->factor = factor;
    initialize(s);
    return s;
}

void set_int_delete(set_int **_s) {
    set_int *s = *_s;
    for (int i = 0; i < s->capacity; i++) {
        node *n = s->table[i];
        while (n != NULL) {
            node *next = n->next;
            free(n);
            n = next;
        }
    }
    free(s->table);
    free(s);
    *_s = NULL;
}

int hash(set_int *s, int value) {
    return value % s->capacity;
}

int set_int_has(set_int *s, int value) {
    int i = hash(s, value);
    for (node *n = s->table[i]; n != NULL; n = n->next) {
        if (value == n->value) {
            return 1;
        }
    }
    return 0;
}

void set_int_insert(set_int *s, int value) {
    int i;
    node *n;

    i = hash(s, value);
    for (n = s->table[i]; n != NULL; n = n->next) {
        if (value == n->value) {
            return;
        }
    }

    s->size++;
    if (s->size > s->factor * s->capacity) {
        int capacity = s->capacity;
        node **table = s->table;
        s->capacity *= 2;
        initialize(s);
        for (int j = 0; j < capacity; j++) {
            n = table[j];
            while (n != NULL) {
                node *next = n->next;
                i = hash(s, n->value);
                n->next = s->table[i];
                s->table[i] = n;
                n = next;
            }
        }
        free(table);
        i = hash(s, value);
    }

    n = malloc(sizeof(node));
    n->value = value;
    n->next = s->table[i];
    s->table[i] = n;
}

void set_int_remove(set_int *s, int value) {
    int i = hash(s, value);
    node *p = NULL;
    node *n = s->table[i];
    while (n != NULL) {
        if (value == n->value) {
            break;
        }
        p = n;
        n = n->next;
    }
    if (n == NULL) {
        return;
    }
    if (p != NULL) {
        p->next = n->next;
    } else {
        s->table[i] = n->next;
    }
    free(n);
    s->size--;
}
