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

// regula_falsi is the variant of bisection
double regula_falsi(double (*func)(double), double a, double b, double tol, int max_iter) {
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
        // The only difference here from the bisection method is that
        // the intersection of the secant with the x-axis is used instead of the midpoint
        c = b - func(b) * (b - a) / (func(b) - func(a));
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

double newton(double (*func)(double), double initial_guess, double tol, int max_iter) {
    int iter_cnt = 0;
    double x1 = initial_guess, x2;

    // x2 = x1 - f(x1)/f'(x1)
    while (iter_cnt <= max_iter) {
        x2 = x1 - func(x1) / central_finite_difference(func, x1, tol);
        if (fabs(x1 - x2) < tol) {
            return (x1 + x2) / 2;
        }
        x1 = x2;
        iter_cnt++;
    }

    return NAN;
}
