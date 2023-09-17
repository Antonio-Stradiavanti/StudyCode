#include <stdio.h>
#include <math.h>

void main()
{
    double a, SFA, V;
    printf("Enter a real number a: ");
    scanf("%lf", &a);

    SFA = 4*pow(a, 2); V = pow(a ,3);
    printf("cube value: %lf;\ncube SFA: %lf;", V, SFA);
}