#include "regression.h"

double* polynomial_fit(double* xvalues, double* yvalues, int point_number, int degree) {
    // generate vandermonde row matrix
    double van_row_matrix[degree + 1][point_number];
    for (int m = 0; m < (degree + 1); m++) {
        for (int n = 0; n < point_number; n++) {
            van_row_matrix[m][n] = pow(xvalues[n], m);
        }
    }

    return 0;
}
