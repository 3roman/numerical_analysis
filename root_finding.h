#ifndef ROOT_FINDING_H
#define ROOT_FINDING_H

#include <math.h>
#include <float.h>

double bisection(double (*func)(double), double a, double b, double tol);

#endif