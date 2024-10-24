#include <stdio.h>

#include "root_finding.h"

const double EPSILON = 1e-6;
const double MAX_ITER = 1e3;

double example_function(double x) {
    return pow(x, 3) - pow(x, 2) - x - 1;
}

int main() {
    printf("%-20s%f\n", "bisection ->", bisection(example_function, 2.1, 1, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "secant ->", secant(example_function, 2.1, 1, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "regula_falsi ->", regula_falsi(example_function, 2.1, 1, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "newton ->", newton(example_function, 2, EPSILON, MAX_ITER));

    return 0;
}