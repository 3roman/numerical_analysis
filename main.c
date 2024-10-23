#include <stdio.h>
#include <math.h>
#include "root_finding.h"

double example_function(double x);

int main()
{
    printf("%f\n", bisection(example_function, 1.5, 2, 1e-6));

    return 0;
}

double example_function(double x)
{
    return pow(x, 3) - pow(x, 2) - x - 1;
}
