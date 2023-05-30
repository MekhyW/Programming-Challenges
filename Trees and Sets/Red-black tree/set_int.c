#include <stdlib.h>

#include "set_int.h"

#define RED 0
#define BLACK 1

struct _node {
    int value;
    int color;
    struct _node *parent;
    struct _node *left;
    struct _node *right;
};

typedef struct _node node;

struct _set_int {
    node *root;
};

set_int *set_int_new() {
    set_int *s = malloc(sizeof(set_int));
    s->root = NULL;
    return s;
}

void tree_delete(node *n) {
    if (n == NULL) {
        return;
    }
    tree_delete(n->right);
    tree_delete(n->left);
    free(n);
}

void set_int_delete(set_int **_s) {
    set_int *s = *_s;
    tree_delete(s->root);
    *_s = NULL;
}

int set_int_empty(set_int *s) {
    return s->root == NULL;
}

int set_int_has(set_int *s, int value) {
    node *n = s->root;

    while (n != NULL) {
        if (value == n->value) {
            return 1;
        }

        if (value < n->value) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    return 0;
}

void rotate_left(set_int *s, node *n) {
    node *p = n->parent;
    node *m = n->right;
    node *c = m->left;

    if (p != NULL) {
        if (n == p->left) {
            p->left = m;
        } else {
            p->right = m;
        }
    } else {
        s->root = m;
    }
    m->parent = p;

    n->right = c;
    if (c != NULL) {
        c->parent = n;
    }

    m->left = n;
    n->parent = m;
}

void rotate_right(set_int *s, node *m) {
    node *p = m->parent;
    node *n = m->left;
    node *c = n->right;

    if (p != NULL) {
        if (m == p->left) {
            p->left = n;
        } else {
            p->right = n;
        }
    } else {
        s->root = n;
    }
    n->parent = p;

    m->left = c;
    if (c != NULL) {
        c->parent = m;
    }

    n->right = m;
    m->parent = n;
}

int color(node *n) {
    if (n == NULL) {
        return BLACK;
    }
    return n->color;
}

void set_int_insert(set_int *s, int value) {
    node *p = NULL;
    node *n = s->root;

    while (n != NULL) {
        if (value == n->value) {
            return;
        }

        p = n;
        if (value < n->value) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    n = malloc(sizeof(node));
    n->value = value;
    n->color = RED;
    n->parent = p;
    n->left = NULL;
    n->right = NULL;

    if (p != NULL) {
        if (value < p->value) {
            p->left = n;
        } else {
            p->right = n;
        }
    } else {
        s->root = n;
    }

    while (p != NULL && p->color == RED) {
        node *g = p->parent;
        node *u;
        if (p == g->left) {
            u = g->right;
            if (color(u) == RED) {
                g->color = RED;
                p->color = BLACK;
                u->color = BLACK;
                n = g;
                p = n->parent;
            } else {
                if (n == p->right) {
                    rotate_left(s, p);
                    n = p;
                    p = n->parent;
                }
                g->color = RED;
                p->color = BLACK;
                rotate_right(s, g);
            }
        } else {
            u = g->left;
            if (color(u) == RED) {
                g->color = RED;
                p->color = BLACK;
                u->color = BLACK;
                n = g;
                p = n->parent;
            } else {
                if (n == p->left) {
                    rotate_right(s, p);
                    n = p;
                    p = n->parent;
                }
                g->color = RED;
                p->color = BLACK;
                rotate_left(s, g);
            }
        }
    }
    if (p == NULL) {
        n->color = BLACK;
    }
}

void node_delete(set_int *s, node *n, node *c) {
    int deleted = n->color;

    node *p = n->parent;
    if (p != NULL) {
        if (n == p->left) {
            p->left = c;
        } else {
            p->right = c;
        }
    } else {
        s->root = c;
    }
    if (c != NULL) {
        c->parent = p;
    }
    free(n);

    if (deleted == BLACK) {
        while (p != NULL && color(c) == BLACK) {
            node *d;
            if (c == p->left) {
                d = p->right;
                if (d->color == RED) {
                    p->color = RED;
                    d->color = BLACK;
                    rotate_left(s, p);
                    d = p->right;
                }
                if (color(d->left) == BLACK && color(d->right) == BLACK) {
                    d->color = RED;
                    c = p;
                    p = c->parent;
                } else {
                    if (color(d->right) == BLACK) {
                        d->color = RED;
                        d->left->color = BLACK;
                        rotate_right(s, d);
                        d = p->right;
                    }
                    d->color = p->color;
                    p->color = BLACK;
                    d->right->color = BLACK;
                    rotate_left(s, p);
                    return;
                }
            } else {
                d = p->left;
                if (d->color == RED) {
                    p->color = RED;
                    d->color = BLACK;
                    rotate_right(s, p);
                    d = p->left;
                }
                if (color(d->left) == BLACK && color(d->right) == BLACK) {
                    d->color = RED;
                    c = p;
                    p = c->parent;
                } else {
                    if (color(d->left) == BLACK) {
                        d->color = RED;
                        d->right->color = BLACK;
                        rotate_left(s, d);
                        d = p->left;
                    }
                    d->color = p->color;
                    p->color = BLACK;
                    d->left->color = BLACK;
                    rotate_right(s, p);
                    return;
                }
            }
        }
        if (color(c) == RED) {
            c->color = BLACK;
        }
    }
}

void set_int_remove(set_int *s, int value) {
    node *n = s->root;

    while (n != NULL) {
        if (value == n->value) {
            break;
        }

        if (value < n->value) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    if (n != NULL) {
        if (n->left == NULL) {
            node_delete(s, n, n->right);
        } else {
            if (n->right != NULL) {
                node *m = n;
                n = n->left;
                while (n->right != NULL) {
                    n = n->right;
                }
                m->value = n->value;
            }
            node_delete(s, n, n->left);
        }
    }
}

int tree_balanced(node *n, int *_h) {
    if (n == NULL) {
        *_h = 1;
        return 1;
    }
    int l, r;
    int b = tree_balanced(n->left, &l) && tree_balanced(n->right, &r);
    *_h = l > r ? l : r;
    if (n->color == BLACK) {
        *_h += 1;
    } else {
        if (color(n->left) == RED || color(n->right) == RED) {
            return 0;
        }
    }
    if (!b || l != r) {
        return 0;
    }
    return 1;
}

int is_balanced(set_int *s) {
    if (color(s->root) == RED) {
        return 0;
    }
    int h;
    return tree_balanced(s->root, &h);
}
