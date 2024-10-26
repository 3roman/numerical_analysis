#include "root_finding.h"

double bisection(double (*func)(double), double a, double b, double tol, int max_iter) {
    double fa = func(a), fb = func(b);
    if (fabs(fa) <= tol) return a;
    if (fabs(fb) <= tol) return b;
    if (fa * fb > 0) return NAN;

    double c = 0.0, fc = 0.0;
    int iter_cnt = 0;

    while (fabs(a - b) > tol) {
        if (iter_cnt > max_iter) return NAN;
        c = 0.5 * (a + b);
        fc = func(c);

        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
        }

        iter_cnt++;
    }

    return c;
}

double newton(double (*func)(double), double initial_guess, double tol, int max_iter) {
    // divergent example: f(x) = x * x * x - 2 * x + 2 with initial value of 0.6

    int iter_cnt = 0;
    double x1 = initial_guess, x2 = 0.0;
    double derivative = 0.0;

    // x2 = x1 - f(x1) / f'(x1)
    while (iter_cnt < max_iter) {
        derivative = central_finite_difference(func, x1, tol);
        // tangent is too flat to continue
        if (fabs(derivative) < tol) return NAN;
        x2 = x1 - func(x1) / derivative;
        if (fabs(func(x2)) <= tol) return x2;
        x1 = x2;
        iter_cnt++;
    }

    return NAN;
}

double secant(double (*func)(double), double a, double b, double tol, int max_iter) {
    int iter_cnt = 0;
    double fa = func(a), fb = func(b);
    double c = 0.0, fc = 0.0;

    while (iter_cnt < max_iter) {
        c = b - fb * ((b - a) / (fb - fa));
        fc = func(c);
        if (fabs(fc) <= tol) return c;
        a = b;
        fa = fb;
        b = c;
        fb = fc;

        iter_cnt++;
    }

    return NAN;
}

double brent(double (*func)(double), double lower, double upper, double tol, int max_iter) {
    double a = lower;
    double b = upper;
    double fa = func(a);  // calculated now to save function calls
    double fb = func(b);  // calculated now to save function calls
    double fs = 0.0;
    double temp;

    if (!(fa * fb < 0)) return NAN;

    // if magnitude of func(lower_bound) is less than magnitude of func(upper_bound)
    if (fabs(fa) < fabs(b)) {
        temp = a;
        a = b;
        b = temp;
        temp = fa;
        fa = fb;
        fb = temp;
    }

    double c = a;       // c now equals the largest magnitude of the lower and upper bounds
    double fc = fa;     // precompute function evalutation for point c by assigning it the same value as fa
    bool mflag = true;  // boolean flag used to evaluate if statement later on
    double s = 0.0;     // Our Root that will be returned
    double d = 0.0;     // Only used if mflag is unset (mflag == false)

    for (int iter = 0; iter < max_iter; iter++) {
        // stop if converged on root or error is less than tolerance
        if (fabs(b - a) < tol) return s;

        if (fa != fc && fb != fc) {
            // use inverse quadratic interopolation
            s = (a * fb * fc / ((fa - fb) * (fa - fc))) + (b * fa * fc / ((fb - fa) * (fb - fc))) + (c * fa * fb / ((fc - fa) * (fc - fb)));
        } else {
            // secant method
            s = b - fb * (b - a) / (fb - fa);
        }

        // checks to see whether we can use the faster converging quadratic && secant methods or if we need to use bisection
        if (((s < (3 * a + b) * 0.25) || (s > b)) ||
            (mflag && (fabs(s - b) >= (fabs(b - c) * 0.5))) ||
            (!mflag && (fabs(s - b) >= (fabs(c - d) * 0.5))) ||
            (mflag && (fabs(b - c) < tol)) ||
            (!mflag && (fabs(c - d) < tol))) {
            // bisection method
            s = (a + b) * 0.5;
            mflag = true;
        } else {
            mflag = false;
        }

        fs = func(s);  // calculate fs
        d = c;         // first time d is being used (wasnt used on first iteration because mflag was set)
        c = b;         // set c equal to upper bound
        fc = fb;       // set func(c) = func(b)

        if (fa * fs < 0)  // fa and fs have opposite signs
        {
            b = s;
            fb = fs;  // set func(b) = func(s)
        } else {
            a = s;
            fa = fs;  // set func(a) = func(s)
        }

        if (fabs(fa) < fabs(fb))  // if magnitude of fa is less than magnitude of fb
        {
            temp = a;
            a = b;
            b = temp;
            temp = fa;
            fa = fb;
            fb = temp;
        }
    }
}