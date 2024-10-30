#ifndef MATRIX_H
#define MATRIX_H

#include "math.h"
#include "stdlib.h"

int transpose(int input_m, int input_n, double *input, double *output);
int dot_product(double *A, int m_A, int n_A, double *B, int n_B, double *C);
int invert_matrix(double *matrix, double *inverse, int n);

#endif