#include <math.h>
#include <stdio.h>

#include "image.h"

void load_image(char path[], image *img) {
    FILE *file = fopen(path, "r");

    getc(file);
    getc(file);

    if (fscanf(file, "%d", &img->width) != 1) {
        fprintf(stderr, "erro ao ler largura da imagem %s\n", path);
    }
    if (fscanf(file, "%d", &img->height) != 1) {
        fprintf(stderr, "erro ao ler altura da imagem %s\n", path);
    }
    if (fscanf(file, "%*d") != 0) {
        fprintf(stderr, "erro ao ler 255 da imagem %s\n", path);
    }

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            if (fscanf(file, "%d", &img->levels[y][x]) != 1) {
                fprintf(stderr, "erro ao ler nivel da imagem %s\n", path);
            }
        }
    }

    fclose(file);
}

void save_image(image *img, char path[]) {
    FILE *file = fopen(path, "w");

    fprintf(file, "P2\n%d %d\n255\n", img->width, img->height);

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            fprintf(file, "%d\n", img->levels[y][x]);
        }
    }

    fclose(file);
}

void convert_image(complex matrix[MAX_SIZE][MAX_SIZE], image *img) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            img->levels[y][x] = MIN(MAX(0, round(matrix[y][x].a)), 255);
        }
    }
}
