#include "matrix.h"

int transpose(int input_m, int input_n, double *input, double *output) {
    for (int i = 0; i < input_m; i++) {
        for (int j = 0; j < input_n; j++) {
            *(output + j * input_m + i) = *(input + i * input_n + j);
        }
    }

    return 0;
}

int dot_product(double *A, int m_A, int n_A, double *B, int n_B, double *C) {
    for (int i = 0; i < m_A; i++) {
        for (int j = 0; j < n_B; j++) {
            C[i * n_B + j] = 0;
            for (int k = 0; k < n_A; k++) {
                C[i * n_B + j] += A[i * n_A + k] * B[k * n_B + j];
            }
        }
    }

    return 0;
}

int invert_matrix(double *matrix, double *inverse, int n) {
    // Create an augmented matrix with the input matrix and the identity matrix
    double *augmented = (double *)malloc(n * 2 * n * sizeof(double));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i * 2 * n + j] = matrix[i * n + j];         // Copy matrix
            augmented[i * 2 * n + j + n] = (i == j) ? 1.0 : 0.0;  // Identity matrix
        }
    }

    // Perform Gauss-Jordan elimination
    for (int i = 0; i < n; i++) {
        // Check for singularity by ensuring pivot element is non-zero
        if (fabs(augmented[i * 2 * n + i]) < 1e-10) {
            free(augmented);
            return -1;
        }

        // Normalize the pivot row
        double pivot = augmented[i * 2 * n + i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i * 2 * n + j] /= pivot;
        }

        // Eliminate all other entries in the current column
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented[k * 2 * n + i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k * 2 * n + j] -= factor * augmented[i * 2 * n + j];
                }
            }
        }
    }

    // Extract the inverse matrix from the augmented matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i * n + j] = augmented[i * 2 * n + j + n];
        }
    }

    free(augmented);

    return 0;
}
