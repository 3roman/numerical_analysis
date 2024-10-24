#include "root_finding.h"

double bisection(double (*func)(double), double a, double b, double tol, int max_iter) {
    double fa = func(a), fb = func(b);
    if (fabs(fa) <= tol) {
        return a;
    }
    if (fabs(fb) <= tol) {
        return b;
    }
    if (fa * fb > 0) {
        return NAN;
    }

    double c = 0.0, fc = 0.0;
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
    double c = 0.0;
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

double newton(double (*func)(double), double initial_guess, double tol, int max_iter) {
    int iter_cnt = 0;
    double x1 = initial_guess, x2 = 0.0;

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

double brent(double (*func)(double), double a, double b, double tol, int max_iter) {
    double m = 0.0, p = 0.0, q = 0.0, r = 0.0, s = 0.0;

    double a1 = a;
    double b1 = b;
    double fa = func(a1);
    double fb = func(b1);

    double c = a1;
    double fc = fa;      // Function value at c (same as fa initially)
    double e = b1 - a1;  // Interval size
    double d = e;

    int iter_cnt = 0;
    while (iter_cnt < max_iter) {
        // Ensure that |fb| is always the smallest, if not, swap variables
        if (fabs(fc) < fabs(fb)) {
            a1 = b1;
            b1 = c;
            c = a1;
            fa = fb;
            fb = fc;
            fc = fa;
        }

        // Compute the midpoint
        m = (c - b1) / 2;

        // Check for convergence: if m is within tolerance or root found
        if ((fabs(m) <= tol) || (fb == 0.0)) {
            break;
        }

        // If previous step was small or |fa| <= |fb|, use bisection
        if ((fabs(e) < tol) || (fabs(fa) <= fabs(fb))) {
            e = m;
            d = e;  // Bisection step
        } else {
            // Inverse quadratic interpolation
            s = fb / fa;

            if (a1 == c) {
                p = 2.0 * m * s;  // Linear interpolation
                q = 1.0 - s;
            } else {
                q = fa / fc;
                r = fb / fc;
                // Parabolic interpolation
                p = s * (2.0 * m * q * (q - r) - (b1 - a1) * (r - 1.0));
                q = (q - 1.0) * (r - 1.0) * (s - 1.0);
            }

            // Make sure p is in the correct direction
            if (p > 0.0) {
                q = -q;
            } else {
                p = -p;
            }

            // Adjust step size
            s = e;
            e = d;

            // Accept interpolation only if it provides a reasonable step
            if ((2.0 * p < 3.0 * m * q - fabs(tol * q)) && (p < fabs(0.5 * s * q))) {
                d = p / q;
            } else {
                // Use bisection if interpolation fails
                e = m;
                d = e;
            }
        }

        // Update a1, fa, b1
        a1 = b1;
        fa = fb;

        // Update b1 using the step size
        if (tol < fabs(d)) {
            b1 += d;
        } else if (0.0 < m) {
            b1 += tol;
        } else {
            b1 -= tol;
        }

        // Update function value at b1
        fb = func(b1);

        // If fb and fc have the same sign, update c
        if ((0.0 < fb && 0.0 < fc) || (fb <= 0.0 && fc <= 0.0)) {
            c = a1;
            fc = fa;
            e = b1 - a1;
            d = e;
        }

        iter_cnt++;
    }

    // Return the best estimate of the root
    return b1;
}
