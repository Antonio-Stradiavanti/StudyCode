#include<stdio.h>
int Add(int a, int b)
{
    return a+b;
}
int main()
{
    // Указатель на ф-цию
    int (*p)(int, int);
    p = Add;

    int c = p(2, 3); // -> указатель на ф-цию.
    // int *p(int, int); -> объявление ф-ции, которая возвращает указатель на целое число
    printf("%d\n", c);
    return 0;
}