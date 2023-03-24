#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fourier.h"
#include "image.h"

#define NUM_TESTS 9

int main() {
    static char path[39];
    static complex input[MAX_SIZE][MAX_SIZE], output[MAX_SIZE][MAX_SIZE];
    static image img;

    for (int t = 1; t <= NUM_TESTS; t++) {
        int x, y;

        sprintf(path, "integration_inputs/%d.pgm", t);
        load_image(path, &img);

        int width = pow(2, ceil(log2(img.width)));
        int height = pow(2, ceil(log2(img.height)));

        for (y = 0; y < img.height; y++) {
            for (x = 0; x < img.width; x++) {
                input[y][x].a = img.levels[y][x];
                input[y][x].b = 0;
            }
            while (x < width) {
                input[y][x].a = 0;
                input[y][x].b = 0;
                x++;
            }
        }
        while (y < height) {
            for (x = 0; x < width; x++) {
                input[y][x].a = 0;
                input[y][x].b = 0;
            }
            y++;
        }

        fft_forward_2d(input, width, height);

        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                output[y][x] = input[y][x];
            }
        }

        fft_inverse_2d(output, width, height);
        convert_image(output, &img);
        sprintf(path, "integration_outputs/%d.pgm", t);
        save_image(&img, path);

        filter_lp(input, output, width, height);
        fft_inverse_2d(output, width, height);
        convert_image(output, &img);
        sprintf(path, "integration_outputs/%d-lp.pgm", t);
        save_image(&img, path);

        filter_hp(input, output, width, height);
        fft_inverse_2d(output, width, height);
        convert_image(output, &img);
        sprintf(path, "integration_outputs/%d-hp.pgm", t);
        save_image(&img, path);
    }

    printf("tudo pronto para rodar integration_test.py\n");

    return EXIT_SUCCESS;
}
