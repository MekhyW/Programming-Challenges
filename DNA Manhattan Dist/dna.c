#include <stdio.h>

#include "dna.h"

void load_string(FILE *file, int *p, char *s, int t) {
    if (fscanf(file, "%d", p) != 1) {
        fprintf(stderr, "erro ao ler string do teste %d\n", t);
    }

    char c;
    do {
        c = getc(file);
    } while (c != '\n');

    fgets(s, *p + 1, file);
}

int mlev_w(char a[], int n, char b[], int m, int cache[MAX_SIZE + 1][MAX_SIZE + 1]) {
    if (cache[n][m] != -1) {
        return cache[n][m];
    }
    /* base da recursão */
    if (n == 0) {
        cache[n][m] = m;
        return cache[n][m];
    }
    if (m == 0) {
        cache[n][m] = n;
        return cache[n][m];
    }
    if (a[n - 1] == b[m - 1]) {
        cache[n][m] = mlev_w(a, n - 1, b, m - 1, cache);
        return cache[n][m];
    }
    /* calcular o minimo entre 3 chamadas */
    int menor = mlev_w(a, n - 1, b, m - 1, cache);
    int valor_2 = mlev_w(a, n - 1, b, m, cache);
    int valor_3 = mlev_w(a, n, b, m - 1, cache);
    if (valor_2 < menor) {
        menor = valor_2;
    }
    if (valor_3 < menor) {
        menor = valor_3;
    }
    cache[n][m] = 1 + menor;
    return cache[n][m];
}

int mlev(char a[], int n, char b[], int m) {
    int cache[MAX_SIZE + 1][MAX_SIZE + 1];
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            cache[i][j] = -1;
        }
    }
    return mlev_w(a, n, b, m, cache);
}

int dlev(char a[], int n, char b[], int m) {
    int cache[MAX_SIZE + 1][MAX_SIZE + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                cache[i][j] = j;
            }
            if (j == 0) {
                cache[i][j] = i;
            } else {
                if (a[i - 1] == b[j - 1]) {
                    cache[i][j] = cache[i - 1][j - 1];
                } else {
                    int menor = cache[i - 1][j - 1];
                    int valor_2 = cache[i - 1][j];
                    int valor_3 = cache[i][j - 1];
                    if (valor_2 < menor) {
                        menor = valor_2;
                    }
                    if (valor_3 < menor) {
                        menor = valor_3;
                    }
                    cache[i][j] = 1 + menor;
                }
            }
        }
    }
    return cache[n][m];
}
