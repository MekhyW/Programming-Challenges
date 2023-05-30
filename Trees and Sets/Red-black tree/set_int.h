#ifndef SET_INT_H
#define SET_INT_H

struct _set_int;

typedef struct _set_int set_int;

set_int *set_int_new();
void set_int_delete(set_int **_s);
int set_int_empty(set_int *s);
int set_int_has(set_int *s, int value);
void set_int_insert(set_int *s, int value);
void set_int_remove(set_int *s, int value);
int is_balanced(set_int *s);

#endif
