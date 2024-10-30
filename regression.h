// reference: https://stats.blue/Stats_Suite/polynomial_regression_calculator.html

#ifndef REGRESSION_H
#define REGRESSION_H

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "matrix.h"

int polynomial_fit(double* xvalues, double* yvalues, int pointer_number, int degree, double* coeffs);

#endif