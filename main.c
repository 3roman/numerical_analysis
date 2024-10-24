#include <stdio.h>

#include "root_finding.h"

const double EPSILON = 1e-6;
const double MAX_ITER = 1e3;

double example_function(double x) {
    return pow(x, 5) - pow(x, 4) - pow(x, 3) - pow(x, 2) - x - 4;
}

int main() {
    printf("%-20s%f\n", "bisection ->", bisection(example_function, 3, 2, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "secant ->", secant(example_function, 3, 2, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "newton ->", newton(example_function, 2, EPSILON, MAX_ITER));
    printf("%-20s%f\n", "brent ->", brent(example_function, 3, 2, EPSILON, MAX_ITER));

    return 0;
}