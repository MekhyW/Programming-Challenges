#include <stdio.h>
#include "troca.h"

int particiona(int v[], int l, int r) {
    int p = l;

    for (int i = l; i < r; i++) {
        if (v[i] < v[r]) {
            if (p != i) {
                troca(v, p, i);
            }
            p++;
        }
        for (int i = 0; i <= r; i++) {
            printf("%d ", v[i]);
        }
        printf("\n");
    }

    if (p != r) {
        troca(v, p, r);
    }

    return p;
}

void quick_sort_r(int v[], int l, int r) {
    if (l >= r) {
        return;
    }
    int p = particiona(v, l, r);
    quick_sort_r(v, l, p - 1);
    quick_sort_r(v, p + 1, r);
}

void quick_sort(int v[], int n) {
    quick_sort_r(v, 0, n - 1);
}

int main() {
    int v[] = { 6, 8, 2, 3, 1, 4 };
    int n = 6;

    quick_sort(v, n);

    return 0;
}