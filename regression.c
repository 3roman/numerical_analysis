#include "regression.h"

int polynomial_fit(double* xvalues, double* yvalues, int pointer_number, int degree, double* coeffs) {
    int m = degree + 1, n = pointer_number;
    double X[m][n], Xt[n][m], XXt[m][m], XXt_inverse[m][m];
    double XXt_inverse_X[m][n];

    // generate vandermonde row matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            X[i][j] = pow(xvalues[j], i);
        }
    }

    transpose(m, n, (double*)X, (double*)Xt);
    dot_product((double*)X, m, n, (double*)Xt, m, (double*)XXt);
    invert_matrix((double*)XXt, (double*)XXt_inverse, m);
    dot_product((double*)XXt_inverse, m, m, (double*)X, n, (double*)XXt_inverse_X);

    for (int i = 0; i < m; i++) {
        coeffs[i] = 0;
        for (int j = 0; j < n; j++) {
            coeffs[i] = coeffs[i] + XXt_inverse_X[i][j] * yvalues[j];
        }
    }

    return 0;
}
