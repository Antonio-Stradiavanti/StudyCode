#include <stdio.h>
#include <stdlib.h>

int i, j, k;

void AllocVector(float** pV, int n, int m)
{
    *pV = (float*)malloc((n * m) * sizeof(float));
}

void InitVector(float *pV, int n, int m)
{
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
           *(pV + i * m + j) = (float) 1.0*(i*m + j + 1);
        }
    }
}

void PrintVector(float *pV, int n, int m)
{
    printf("\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++) printf("%.3f\t", *(pV + i*m + j));
        printf("\n");
    }
}

float* VectorsAdd(float* V1, float* V2, int n1, int m1, int n2, int m2)
{
    // Размер складываемых матриц должен совпадать!
    if (n1 == n2 && m1 == m2)
    {
        float* VE; AllocVector(&VE, n1, m1);
        for (i = 0; i < n1; i++)
        {
            for (j = 0; j < m1; j++)
            {
                *(VE + i*m1 + j) = *(V1 + i*m1 + j) + *(V2 + i*m1 + j);
            }
        }   
        return VE;
    }
    else return NULL;
}


void Test(float* V1)
{
    int n1, m1; 
    printf("Enter the dimension of vector V1:\n"); scanf("%d %d", &n1, &m1);
    AllocVector(&V1, n1, m1);
    InitVector(V1, n1, m1);
    PrintVector(V1, n1, m1);
    free(V1);
}

void main()
{
    //int m1 = 1, m2 = 1; 
    float* V1;
    Test(V1);
    //float* V2; AllocVector(&V2, n2, m2);
    //InitVector(V2, n2, m2); 
    
    //PrintVector(V2, n2, m2);
    
    //VectorNumDiv(V1, n1, m1, 2.0);
    //PrintVector(V1, n1, m1); 
    //float* G = VectorMult(V1, V2, n1, m1, n2, m2); 
    //if (G != NULL) PrintVector(G, n1, m2);
    //else printf("\nIt is not possible :(");
    
    //free(V2); free(G);
}