#include <stdio.h>
#include "root_finding.h"

const  double EPSILON  = 1e-6;

double example_function(double x);

int main()
{
    printf("%f\n", bisection(example_function, 1.5, 2, EPSILON));

    return 0;
}

double example_function(double x)
{
    return pow(x, 3) - pow(x, 2) - x - 1;
}
