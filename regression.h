#ifndef REGRESSION_H
#define REGRESSION_H

#include <float.h>
#include <math.h>
#include <stdbool.h>

double* polynomial_fit(double* xvalues, double* yvalues, int size, int degree);

#endif