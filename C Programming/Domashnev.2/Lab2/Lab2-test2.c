#include <stdio.h>
#include <stdlib.h>
#define MAX2(a, b) (a > b) ? a : b
int* inter(int* A, int sizeA, int* B, int sizeB, int* cfound)
{
    int i, j, found = -1;
    int maxSize = MAX2(sizeA, sizeB);
    int* res = (int*)malloc(maxSize * sizeof(int));
    for (i = 0; i < sizeA; i++)
    {
        for (j = 0; j < sizeB; j++)
        {
            if (A[i] == B[j])
            {
                found+=1;
                res[found] = A[i];
            }
        }
    }
    if (found == -1)
    {
        return NULL;
    }
    else
    {
        *cfound = found+1;
        res = (int*)realloc(res, found+1);
        return res;
    }
}
int* inter4(int* A, int sizeA, int* B, int sizeB, int* C, int sizeC, int* D, int sizeD, int* tcfound)
{
    int cfound1, cfound2;
    int* tempres1 = inter(A, sizeA, B, sizeB, &cfound1);
    int* tempres2 = inter(C, sizeC, D, sizeD, &cfound2);
    if (tempres1 == NULL || tempres2 == NULL)
    {
        free (tempres1); free(tempres2);
        printf("\nEmpty array\n");
        return NULL;
    }
    else
    {
        int* res = inter(tempres1, cfound1, tempres2, cfound2, tcfound);
        if (res == NULL)
        {
            printf("\nEmpty array\n");
            free (tempres1); free(tempres2); free(res);
            return NULL;
        }
        else
        {
            free (tempres1); free(tempres2);
            return res;
        }
    }
}

int main()
{
    int i, tcfound;
    // протестируем сортировочку
    int A[6] = {1, 45, 4, 5, 0, -1};
    int B[6] = {1, 45, 5, 6, 88, 9};
    int C[6] = {1, 5, 77, 8, 23, 34};
    int D[6] = {5, 6, 23, 45, 90, 55};
    
    // Выполним финальную операцию пересечение
    int* res = inter4(A, 6, B, 6, C, 6, D, 6, &tcfound);
    printf("\n");
    for (i = 0; i < tcfound; i++)
    {
        printf("res[%d] = %d\n", i, res[i]);
    }
    // Сбор мусора
    free(res);
    return 0;
}