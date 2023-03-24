#include <stdio.h>
#include "troca.h"

void selection_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;

        for (int j = i + 1; j < n; j++) {
            if (v[m] > v[j]) {
                m = j;
            }
        }

        troca(v, m, i);
        
        for (int i = 0; i < n; i++) {
            printf("%d ", v[i]);
        }
        printf("\n");
    }
}

int main() {
    int v[] = { 5, 1, 9, 7, 3 };
    int n = 5;

    selection_sort(v, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    return 0;
}