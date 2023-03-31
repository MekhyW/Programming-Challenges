#include <stdio.h>

int busca_simples(int v[], int n, int q) {
    for (int i = 0; i < n; i++) {
        if (v[i] == q) {
            return i;
        }
    }
    return -1;
}


int main() {
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 10;
    int q = 5;
    int pos = busca_simples(v, n, q);
    if (pos == -1) {
        printf("Não encontrado\n");
    } else {
        printf("Encontrado na posição %d\n", pos);
    }
    return 0;
}