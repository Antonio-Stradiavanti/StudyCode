#include <stdio.h>
#include <stdlib.h>
#define frand() ((float) rand() / RAND_MAX+1.0)

int i, j;

// ранд не обновляет свои значения
void AllocMatrix(float*** pA, int n, int m)
{
    *pA = (float **)malloc (n*sizeof(float *));
	for (i = 0; i < n; i++)
    {
		(*pA)[i] = (float *)malloc(m*sizeof(float));
    }
}
void InitMatrix(float **a, int n, int m)
{
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++) *(*(a + i) + j) = (float) 1.0*(i*m + j + 1);
    }
}
void PrintMatrix(float **pM, int n, int m)
{
    printf("\n");
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j) 
        {
            printf("%.3f\t", *(*(pM + i) + j));
        }
        printf("\n");
    }
}
float** MatrixTranspose(float** pM, int n, int m)
{
    float** MC;
    AllocMatrix(&MC, m, n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            *(*(MC+j)+i) = *(*(pM+i) + j);
        }
    }
    // возвращаю адрес, младшего байта выделенной и заполненной области массива указателей, его нужно хранить в указателе на указатель. 
    return MC;
}
void FreeMatrix(float **a, int n)
{
    for (i=0; i < n; i++)
    {
        free(*(a+i));
    }
    free(a);
}
// это работает и проще
// распределение памяти под большое количество массивов
void main()
{
    float** M; int nM = 2, mM = 3;  
    AllocMatrix(&M, nM, mM);
    InitMatrix(M, nM, mM);
    PrintMatrix(M, nM, mM);
    float** MC = MatrixTranspose(M, nM, mM);
    PrintMatrix(MC, mM, nM);
    FreeMatrix(MC, nM);
    FreeMatrix(M, nM);  
     
}
