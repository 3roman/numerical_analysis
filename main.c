#include <stdio.h>
#include <stdlib.h>

#include "regression.h"
#include "root_finding.h"

const double EPSILON = 1e-6;
const double MAX_ITER = 1e3;

double example_function(double x) {
    return pow(x, 8) - pow(x, 4) - pow(x, 3) - pow(x, 2) - x - 4;
}

int main() {
    printf("%-20s%f\n", "bisection ->", bisection(example_function, 1, 3, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "newton ->", newton(example_function, 1, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "secant ->", secant(example_function, 1, 3, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "brent ->", brent(example_function, 1, 3, EPSILON, MAX_ITER));

    double xvalues[] = {1, 2, 3, 4, 5, 6, 7};
    double yvalues[] = {0.102, 0.095, 0.087, 0.079, 0.072, 0.065, 0.059};
    int size = 7;
    int degree = 3;

    polynomial_fit(xvalues, yvalues, size, degree);

    return 0;
}
