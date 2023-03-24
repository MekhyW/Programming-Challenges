#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fourier.h"

#define NUM_TESTS 90

int main() {
    static char path[33];
    static complex s[MAX_SIZE], nt[MAX_SIZE], ns[MAX_SIZE], ft[MAX_SIZE], fs[MAX_SIZE];

    srand(0);

    int num_passed = 0;

    for (int n = 1; n <= MAX_SIZE; n *= 2) {
        for (int t = 1; t <= NUM_TESTS; t++) {
            int j;

            for (j = 0; j < n; j++) {
                double level = (rand() / (double)RAND_MAX) * 256;
                if (level >= 256) {
                    s[j].a = 255;
                } else {
                    s[j].a = floor(level);
                }
                s[j].b = 0;
            }

            nft_forward(s, nt, n);
            nft_inverse(nt, ns, n);

            fft_forward(s, ft, n);
            fft_inverse(ft, fs, n);

            int passed = 1;

            for (j = 0; j < n; j++) {
                if ((int)round(ns[j].a) != (int)round(fs[j].a)) {
                    passed = 0;
                    break;
                }
            }

            sprintf(path, "unit_outputs/%03d-%02d.txt", n, t);

            FILE *file = fopen(path, "w");

            fprintf(file, "SINAL     NFT                         FFT                         NFT INVERSA     FFT INVERSA\n");
            fprintf(file, "-----     -----------------------     -----------------------     -----------     -----------\n");

            for (j = 0; j < n; j++) {
                fprintf(file, " %4.0f     %11.3f %11.3f     %11.3f %11.3f            %4.0f            %4.0f\n", round(s[j].a), nt[j].a, nt[j].b, ft[j].a, ft[j].b, round(ns[j].a), round(fs[j].a));
            }

            fclose(file);

            if (passed) {
                num_passed++;
            } else {
                printf("NÃO PASSOU NO TESTE %d-%d: examine o texto %s\n", n, t, path);
            }
        }
    }

    printf("passou em %d de %d testes\n", num_passed, ((int)log2(MAX_SIZE) + 1) * NUM_TESTS);

    return EXIT_SUCCESS;
}
