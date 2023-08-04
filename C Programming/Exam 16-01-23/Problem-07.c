#include <stdio.h>
#include <math.h>

// реализация факториала в си
unsigned long factorial(unsigned n)
{
    if (n == 1)
    {
        return 1;
    }
    return factorial(n - 1) * n; // по с-ву
}

int main()
{
    unsigned n, i = 1;
    printf("Enter a natural number n: ");
    scanf("%u", &n);

    double sum = 0.0, ans = 0.0;

    while (i != n+1) 
    {
        sum += sin((2*i - 1)*(M_PI/180));
        ans += 1.0/sum;
        i++;
        printf("sum = %lf, ans = %lf\n", sum, ans);
    }

    unsigned long fact = factorial(factorial(n));
    printf("\nsumma: | %lf |;\nfactorial: | %lu |;", ans, fact);
} 
