#ifndef FOURIER_H
#define FOURIER_H

#define MAX_SIZE 512

#define PI 3.141592

#define SIGMA 16

typedef struct {
    double a;
    double b;
} complex;

void nft_forward(complex s[MAX_SIZE], complex t[MAX_SIZE], int n);
void nft_inverse(complex t[MAX_SIZE], complex s[MAX_SIZE], int n);

void fft_forward(complex s[MAX_SIZE], complex t[MAX_SIZE], int n);
void fft_inverse(complex t[MAX_SIZE], complex s[MAX_SIZE], int n);

void fft_forward_2d(complex matrix[MAX_SIZE][MAX_SIZE], int width, int height);
void fft_inverse_2d(complex matrix[MAX_SIZE][MAX_SIZE], int width, int height);

void filter_lp(complex input[MAX_SIZE][MAX_SIZE], complex output[MAX_SIZE][MAX_SIZE], int width, int height);
void filter_hp(complex input[MAX_SIZE][MAX_SIZE], complex output[MAX_SIZE][MAX_SIZE], int width, int height);

#endif
