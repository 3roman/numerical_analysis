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
    while (fabs(a - b) >= tol) {
        c = (a + b) / 2;
        fc = func(c);
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
        }

        if (iter_cnt >= max_iter) {
            return NAN;
        } else {
            iter_cnt++;
        }
    }

    return (a + b) / 2;
}
