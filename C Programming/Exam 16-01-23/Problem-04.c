#include <stdio.h>
#include <math.h>

double op(double x, double y, double z);

void main()
{
    double x, y, z;
    printf("Enter the real numbers:\n");
    scanf("%lf %lf %lf", &x, &y, &z);

    printf("answer = | %lf |", op(x, y, z));
}

double op(double x, double y, double z)
{
    if ((x + y/2 + z/4) < x*y*z)
    {
        return pow((x + y/2 + z/4), 2) + 1;
    }
    else
    {
        return pow((x*y*z), 2) + 1;
    }
}