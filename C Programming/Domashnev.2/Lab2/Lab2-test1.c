#include <stdio.h>
#include <stdlib.h>
#define MAX2(a, b) (a > b) ? a : b
#define MAX3(a, b, c) MAX2(a, MAX2(b, c))

int main()
{
    int a = 5, b = 4, c = 89;
    int res1 = MAX2(b, c); int res2 = MAX2(a, res1);
    printf("max2: %d", res2);
}