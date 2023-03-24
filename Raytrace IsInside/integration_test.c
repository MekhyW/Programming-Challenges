#include <stdio.h>
#include <stdlib.h>

#include "drawing.h"

#define NUM_TESTS 162

int main() {
    char path[36];
    int n, gold;
    point p;

    int num_passed = 0;

    for (int t = 1; t <= NUM_TESTS; t++) {
        sprintf(path, "integration_inputs/%03d.txt", t);

        FILE *file = fopen(path, "r");

        if (fscanf(file, "%d %d", &p.x, &p.y) < 2) {
            fprintf(stderr, "erro ao ler p do arquivo %s\n", path);
        }
        if (fscanf(file, "%d", &n) < 1) {
            fprintf(stderr, "erro ao ler n do arquivo %s\n", path);
        }

        point poly[n];

        for (int i = 0; i < n; i++) {
            if (fscanf(file, "%d %d", &poly[i].x, &poly[i].y) < 2) {
                fprintf(stderr, "erro ao ler poly do arquivo %s\n", path);
            }
        }
        if (fscanf(file, "%d", &gold) < 1) {
            fprintf(stderr, "erro ao ler gabarito do arquivo %s\n", path);
        }

        fclose(file);

        int result = inside(p, poly, n);

        sprintf(path, "integration_outputs/%03d.svg", t);

        draw_integration(p, poly, n, result, path);

        if (result == gold) {
            num_passed++;
        } else {
            printf("NÃO PASSOU NO TESTE %d: examine a imagem %s\n", t, path);
        }
    }

    printf("passou em %d de %d testes\n", num_passed, NUM_TESTS);

    return EXIT_SUCCESS;
}
