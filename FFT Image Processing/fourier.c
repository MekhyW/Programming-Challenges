#include <math.h>

#include "fourier.h"

void normalize(complex s[MAX_SIZE], int n) {
    for (int k = 0; k < n; k++) {
        s[k].a /= n;
        s[k].b /= n;
    }
}

void nft(complex s[MAX_SIZE], complex t[MAX_SIZE], int n, int sign) {
    for (int k = 0; k < n; k++) {
        t[k].a = 0;
        t[k].b = 0;

        for (int j = 0; j < n; j++) {
            double x = sign * 2 * PI * k * j / n;

            double cosx = cos(x);
            double sinx = sin(x);

            t[k].a += s[j].a * cosx - s[j].b * sinx;
            t[k].b += s[j].a * sinx + s[j].b * cosx;
        }
    }
}

void nft_forward(complex s[MAX_SIZE], complex t[MAX_SIZE], int n) {
    nft(s, t, n, -1);
}

void nft_inverse(complex t[MAX_SIZE], complex s[MAX_SIZE], int n) {
    nft(t, s, n, 1);
    normalize(s, n);
}

void fft(complex s[MAX_SIZE], complex t[MAX_SIZE], int n, int sign) {
    /* base da recursão */
    if (n <= 1) {
        t[0] = s[0];
        return;
    }

    /* arrays auxiliares */
    complex s_par[n / 2];
    complex s_impar[n / 2];
    complex t_par[n / 2];
    complex t_impar[n / 2];

    /* construindo sinal par e sinal impar */
    for (int i = 0; i < n / 2; i++) {
        s_par[i] = s[2 * i];
        s_impar[i] = s[2 * i + 1];
    }

    /* chamada recursiva de fft para transformada par e impar */
    fft(s_par, t_par, n / 2, sign);
    fft(s_impar, t_impar, n / 2, sign);

    /* construindo o sinal da transformada */
    for (int k = 0; k < n / 2; k++) {
        double x = sign * 2 * PI * k / n;
        double cosx = cos(x);
        double sinx = sin(x);
        double real_produto = cosx * t_impar[k].a - sinx * t_impar[k].b;
        double imaginario_produto = cosx * t_impar[k].b + sinx * t_impar[k].a;
        t[k].a = t_par[k].a + real_produto;
        t[k].b = t_par[k].b + imaginario_produto;
        t[k + n / 2].a = t_par[k].a - real_produto;
        t[k + n / 2].b = t_par[k].b - imaginario_produto;
    }
}

void fft_forward(complex s[MAX_SIZE], complex t[MAX_SIZE], int n) {
    fft(s, t, n, -1);
}

void fft_inverse(complex t[MAX_SIZE], complex s[MAX_SIZE], int n) {
    fft(t, s, n, 1);
    normalize(s, n);
}

void fft_forward_2d(complex matrix[MAX_SIZE][MAX_SIZE], int width, int height) {
    for (int l = 0; l < height; l++) {
        fft_forward(matrix[l], matrix[l], width);
    }
    for (int c = 0; c < width; c++) {
        complex coluna[height];
        for (int l = 0; l < height; l++) {
            coluna[l] = matrix[l][c];
        }
        fft_forward(coluna, coluna, height);
        for (int l = 0; l < height; l++) {
            matrix[l][c] = coluna[l];
        }
    }
}

void fft_inverse_2d(complex matrix[MAX_SIZE][MAX_SIZE], int width, int height) {
    for (int l = 0; l < height; l++) {
        fft_inverse(matrix[l], matrix[l], width);
    }
    for (int c = 0; c < width; c++) {
        complex coluna[height];
        for (int l = 0; l < height; l++) {
            coluna[l] = matrix[l][c];
        }
        fft_inverse(coluna, coluna, height);
        for (int l = 0; l < height; l++) {
            matrix[l][c] = coluna[l];
        }
    }
}

void filter(complex input[MAX_SIZE][MAX_SIZE], complex output[MAX_SIZE][MAX_SIZE], int width, int height, int flip) {
    int center_x = width / 2;
    int center_y = height / 2;
    double variance = -2 * SIGMA * SIGMA;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int dx = center_x - (x + center_x) % width;
            int dy = center_y - (y + center_y) % height;
            double d = dx * dx + dy * dy;
            double g = exp(d / variance);
            if (flip) {
                g = 1 - g;
            }
            output[y][x].a = g * input[y][x].a;
            output[y][x].b = g * input[y][x].b;
        }
    }
}

void filter_lp(complex input[MAX_SIZE][MAX_SIZE], complex output[MAX_SIZE][MAX_SIZE], int width, int height) {
    filter(input, output, width, height, 0);
}

void filter_hp(complex input[MAX_SIZE][MAX_SIZE], complex output[MAX_SIZE][MAX_SIZE], int width, int height) {
    filter(input, output, width, height, 1);
}
