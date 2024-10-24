#include "numerical_differentiation.h"

double central_finite_difference(double (*func)(double), double x, double h) {
    return (func(x + h) - func(x - h)) / (2 * h);
}
