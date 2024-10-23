#include <stdio.h>

#include "root_finding.h"

const double EPSILON = 1e-6;
const double MAX_ITER = 1e3;

double example_function(double x) {
    return pow(x, 3) - pow(x, 2) - x - 1;
}

int main() {
    printf("bisection ->\t\t\t%f\n", bisection(example_function, 1, 2.5, EPSILON, MAX_ITER));
    printf("secant ->\t\t\t%f\n", secant(example_function, 1, 2.5, EPSILON, MAX_ITER));

    return 0;
}