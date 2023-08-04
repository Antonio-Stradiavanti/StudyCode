#include<stdio.h>
#define BLOCK_SIZE 7

int main()
{
    int i, LDS[BLOCK_SIZE] = {1, 2, 3, 4, 5, 6, 7}, newData[BLOCK_SIZE], p = 3, elCnt1 = 7, elCnt2 = 0; 

    printf("LDS : ");
    for (i = 0; i < BLOCK_SIZE; i++)
    {
        printf("%d ", LDS[i]);
    }
    printf("\n");

    for (i = p; p < elCnt1; i++)
    {
        newData[++elCnt2-1] = LDS[i];
        elCnt1--;
    }
    LDS[p] = 777; elCnt1++;

    printf("LDS : ");
    for (i = 0; i < elCnt1; i++)
    {
        printf("%d ", LDS[i]);
    }
    printf("\n");

    printf("newData : ");
    for (i = 0; i < elCnt2; i++)
    {
        printf("%d ", newData[i]);
    }
    printf("\n");

}