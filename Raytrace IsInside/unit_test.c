#include <stdio.h>
#include <stdlib.h>

#include "drawing.h"

#define NUM_TESTS 625

int main() {
    char path[29];
    int gold;
    point p, a, b;

    int num_passed = 0;

    for (int t = 1; t <= NUM_TESTS; t++) {
        sprintf(path, "unit_inputs/%03d.txt", t);

        FILE *file = fopen(path, "r");

        if (fscanf(file, "%d %d", &p.x, &p.y) < 2) {
            fprintf(stderr, "erro ao ler p do arquivo %s\n", path);
        }
        if (fscanf(file, "%d %d", &a.x, &a.y) < 2) {
            fprintf(stderr, "erro ao ler a do arquivo %s\n", path);
        }
        if (fscanf(file, "%d %d", &b.x, &b.y) < 2) {
            fprintf(stderr, "erro ao ler b do arquivo %s\n", path);
        }
        if (fscanf(file, "%d", &gold) < 1) {
            fprintf(stderr, "erro ao ler gabarito do arquivo %s\n", path);
        }

        fclose(file);

        int result = verify(p, a, b);

        sprintf(path, "unit_outputs/%03d.svg", t);

        draw_unit(p, a, b, result, path);

        if (result == gold) {
            num_passed++;
        } else {
            printf("NÃO PASSOU NO TESTE %d: examine a imagem %s\n", t, path);
        }
    }

    printf("passou em %d de %d testes\n", num_passed, NUM_TESTS);

    return EXIT_SUCCESS;
}
