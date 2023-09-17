#include <stdio.h>

int main()
{
    int argPrice1, argPrice2;
    char argItem1, argItem2;
    printf("Enter a search query in the following order:\n[1 -> (char) item1; 2 -> (int) price1; 3 -> (char) item2; 4 -> (int) price2]\n");
    scanf_s("%c %d %c %d", &argItem1, &argPrice1, &argItem2, &argPrice2);
    printf("---Ok, I'll try to find it, please wait---");
    return 0;
}