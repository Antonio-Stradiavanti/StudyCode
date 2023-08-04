#include<stdio.h>
#include<stdbool.h>
//extern int a;

int main()
{
    int x, y, z, c = 10;
    x = y = z = ++c;
    printf("x = %d, y = %d, z = %d\n", x, y, z);
    return 0;
}