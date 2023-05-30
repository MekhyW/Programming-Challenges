#include <stdlib.h>

#include "set_int.h"

struct _node {
    int value;
    int height;
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

int height(node *n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

void update_height(node *n) {
    int l = height(n->left);
    int r = height(n->right);
    n->height = (l > r ? l : r) + 1;
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

    update_height(n);
    update_height(m);
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

    update_height(m);
    update_height(n);
}

int balance(node *n) {
    return height(n->right) - height(n->left);
}

void fix_balance(set_int *s, node *p) {
    while (p != NULL) {
        int h = p->height;

        switch (balance(p)) {
        case -2:
            if (balance(p->left) == 1) {
                rotate_left(s, p->left);
            }
            rotate_right(s, p);
            p = p->parent;
            break;
        case 2:
            if (balance(p->right) == -1) {
                rotate_right(s, p->right);
            }
            rotate_left(s, p);
            p = p->parent;
            break;
        default:
            update_height(p);
        }

        if (p->height != h) {
            p = p->parent;
        } else {
            break;
        }
    }
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
    n->height = 1;
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

    fix_balance(s, p);
}

void node_delete(set_int *s, node *n, node *c) {
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
    fix_balance(s, p);
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
        *_h = 0;
        return 1;
    }
    int l, r;
    int b = tree_balanced(n->left, &l) && tree_balanced(n->right, &r);
    *_h = (l > r ? l : r) + 1;
    if (!b) {
        return 0;
    }
    b = r - l;
    if (b < -1 || b > 1) {
        return 0;
    }
    return 1;
}

int is_balanced(set_int *s) {
    int h;
    return tree_balanced(s->root, &h);
}
