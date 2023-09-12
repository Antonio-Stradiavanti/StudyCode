#include <stdio.h>
#include <math.h>

void main()
{
    double a, b, x, y, z;
    printf("Enter the values:\n");
    scanf("%lf %lf %lf", &x, &y, &z);

    a = (2 * cos(x - M_PI/7)) / ((1/3) + pow(sin(y), 2));
    b = 1 + (pow(z, 2) / (3 + (pow(z, 2)/4)));

    printf("Answer: a = | %lf |, b = | %lf |", a, b);
}