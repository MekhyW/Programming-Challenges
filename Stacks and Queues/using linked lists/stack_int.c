#include <stdlib.h>

#include "stack_int.h"

struct _node {
    int value;
    struct _node *next;
};

typedef struct _node node;

struct _stack_int {
    node *top;
};

stack_int *stack_int_new() {
    stack_int *s = malloc(sizeof(stack_int));
    s->top = NULL;
    return s;
}

void stack_int_delete(stack_int **_s) {
    stack_int *s = *_s;
    node *n = s->top;
    while (n != NULL) {
        node *next = n->next;
        free(n);
        n = next;
    }
    free(s);
    *_s = NULL;
}

int stack_int_empty(stack_int *s) {
    return s->top == NULL;
}

void stack_int_push(stack_int *s, int value) {
    node *n = malloc(sizeof(node));
    n->value = value;
    n->next = s->top;
    s->top = n;
}

void stack_int_genpush(stack_int *s, int value, int index) {
    node *p = NULL;
    node *n = s->top;
    //walk until index
    for (int i = 0; i < index; i++) {
        p = n;
        n = n->next;
    }
    //push
    n = malloc(sizeof(node));
    n->value = value;
    //connect with previous and next
    if (p != NULL) {
        n->next = p->next;
        p->next = n;
    } else {
        n->next = s->top;
        s->top = n;
    }
}

int stack_int_pop(stack_int *s) {
    node *n = s->top;
    s->top = n->next;
    int value = n->value;
    free(n);
    return value;
}

int stack_int_genpop(stack_int *s, int index) {
    node *n;
    //determine current size
    int size = 0;
    for (n = s->top; n != NULL; n = n->next) {
        size++;
    }
    //walk size-index-1 times with p (previous) and n (current)
    node *p = NULL;
    node *n = s->top;
    for (int i = 0; i < size - index - 1; i++) {
        p = n;
        n = n->next;
    }
    //connect previous with next
    if(index > 0) {
        p->next = n->next;
    } else {
        s->top = n->next;
    }
    //value to return
    int value = n->value;
    free(n);
    return value;
}