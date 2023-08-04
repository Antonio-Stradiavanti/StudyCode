#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
    int i = 0;
    unsigned n;
    double sum = 0.0;

    printf("Enter a natural number n: ");
    scanf("%u", &n);

    double *cont = (double*)malloc(n * sizeof(double));

    for (i = 0; i < n; i++)
    {
        printf("Enter the value of the [ %d ] element: \n");
        scanf("%lf", &cont[i]);
    }

    printf("\n");

    for (i = 0; i < n; i++)
    {
        sum += pow(cont[i], 2);
        printf("%d : | %lf |\n", i+1, cont[i]);
    }

    printf("ans = %lf", sum);
}
