#include <stdio.h>
#include "troca.h"

void insertion_sort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int temp = v[i];

        int j = i;
        while (j > 0 && v[j - 1] > temp) {
            v[j] = v[j - 1];
            j--;
        }

        v[j] = temp;
        
        for (int i = 0; i < n; i++) {
            printf("%d ", v[i]);
        }
        printf("\n");
    }
}

int main() {
    int v[] = { 5, 1, 9, 7, 3 };
    int n = 5;

    insertion_sort(v, n);

    return 0;
}