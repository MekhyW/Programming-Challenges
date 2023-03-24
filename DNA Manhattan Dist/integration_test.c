#include <stdio.h>
#include <stdlib.h>

#include "dna.h"

#define NUM_TESTS 900

int random_int(int max) {
    int r = (rand() / (double)RAND_MAX) * (max + 1);

    if (r == max + 1) {
        r--;
    }

    return r;
}

void random_string(char s[], int size) {
    for (int i = 0; i < size; i++) {
        switch (random_int(3)) {
        case 0:
            s[i] = 'A';
            break;
        case 1:
            s[i] = 'C';
            break;
        case 2:
            s[i] = 'G';
            break;
        case 3:
            s[i] = 'T';
            break;
        }
    }

    s[size] = '\0';
}

int main() {
    char a[MAX_SIZE + 1], b[MAX_SIZE + 1];

    srand(0);

    int num_passed = 0;

    for (int t = 1; t <= NUM_TESTS; t++) {
        int n = random_int(MAX_SIZE);
        random_string(a, n);

        int m = random_int(MAX_SIZE);
        random_string(b, m);

        int gold = mlev(a, n, b, m);

        int result = dlev(a, n, b, m);

        if (result == gold) {
            num_passed++;
        } else {
            printf("NÃO PASSOU NO TESTE %d: para %s e %s deveria ser %d mas devolveu %d\n", t, a, b, gold, result);
        }
    }

    printf("passou em %d de %d testes\n", num_passed, NUM_TESTS);

    return EXIT_SUCCESS;
}
