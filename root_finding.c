#include "root_finding.h"

double bisection(double (*func)(double), double a, double b, double tol, int max_iter) {
    double fa = func(a);
    double fb = func(b);
    if (fabs(fa) <= tol) {
        return a;
    }
    if (fabs(fb) <= tol) {
        return b;
    }
    if (fa * fb > 0) {
        return NAN;
    }

    double c, fc;
    int iter_cnt = 0;
    while (fabs(a - b) > tol) {
        c = (a + b) / 2;
        fc = func(c);
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
        }

        if (iter_cnt > max_iter) {
            return NAN;
        } else {
            iter_cnt++;
        }
    }

    return (a + b) / 2;
}

double secant(double (*func)(double), double a, double b, double tol, int max_iter) {
    int iter_cnt = 0;
    double c;
    while (fabs(a - b) > tol) {
        c = b - func(b) * (b - a) / (func(b) - func(a));
        a = b;
        b = c;

        if (iter_cnt > max_iter) {
            return NAN;
        } else {
            iter_cnt++;
        }
    }

    return (a + b) / 2;
}
