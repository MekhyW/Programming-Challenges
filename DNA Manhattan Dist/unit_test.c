#include <stdio.h>
#include <stdlib.h>

#include "dna.h"

int main() {
    char a[MAX_SIZE + 1], b[MAX_SIZE + 1];
    int num_tests, n, m, gold;

    FILE *file = fopen("unit_inputs.txt", "r");

    if (fscanf(file, "%d", &num_tests) != 1) {
        fprintf(stderr, "erro ao ler numero de testes\n");
    }

    int num_passed = 0;

    for (int t = 1; t <= num_tests; t++) {
        load_string(file, &n, a, t);
        load_string(file, &m, b, t);

        if (fscanf(file, "%d", &gold) != 1) {
            fprintf(stderr, "erro ao ler gabarito do teste %d\n", t);
        }

        int result = mlev(a, n, b, m);

        if (result == gold) {
            num_passed++;
        } else {
            printf("NÃO PASSOU NO TESTE %d: para %s e %s deveria ser %d mas devolveu %d\n", t, a, b, gold, result);
        }
    }

    printf("passou em %d de %d testes\n", num_passed, num_tests);

    return EXIT_SUCCESS;
}
