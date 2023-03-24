#ifndef IMAGE_H
#define IMAGE_H

#define MIN(x, y) x < y ? x : y
#define MAX(x, y) x > y ? x : y

#include "fourier.h"

typedef struct {
    int width;
    int height;
    int levels[MAX_SIZE][MAX_SIZE];
} image;

void load_image(char path[], image *img);
void save_image(image *img, char path[]);

void convert_image(complex matrix[MAX_SIZE][MAX_SIZE], image *img);

#endif
