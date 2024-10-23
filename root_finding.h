#ifndef ROOT_FINDING_H
#define ROOT_FINDING_H

#include <float.h>
#include <math.h>

double bisection(double (*func)(double), double a, double b, double tol, int max_iter);
double secant(double (*func)(double), double a, double b, double tol, int max_iter);

#endif