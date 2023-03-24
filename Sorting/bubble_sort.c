#include <stdio.h>
#include "troca.h"

void bubble_sort(int v[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int trocou = 0;

        for (int j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                troca(v, j, j + 1);
                trocou = 1;
            }
        }
        
        for (int i = 0; i < n; i++) {
            printf("%d ", v[i]);
        }
        printf("\n");

        if (!trocou) {
            break;
        }
    }
}

int main() {
    int v[] = { 5, 1, 9, 7, 3 };
    int n = 5;

    bubble_sort(v, n);

    return 0;
}