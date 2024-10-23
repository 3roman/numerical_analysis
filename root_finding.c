#include "root_finding.h"

double bisection(double (*func)(double), double a, double b, double tol) {
    double fa = func(a);
    double fb = func(b);

    if (fa * fb >= 0) {
        return DBL_MAX;
    }

    double c, fc;
    while (fabs((a - b) / 2) >= tol) {
        c = (a + b) / 2;
        fc = func(c);

        if (fa * fc < 0) {
            b = c;
        } else if (fa * fc > 0) {
            a = c;
        } else {
            return c;
        }
    }

    return (a + b) / 2;
}
