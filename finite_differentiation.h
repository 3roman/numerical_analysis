#ifndef NUMERICAL_DIFFERENTIATION_H
#define NUMERICAL_DIFFERENTIATION_H

#include <float.h>
#include <math.h>

double central_difference(double (*func)(double), double x, double h);

#endif