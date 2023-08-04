#include <stdio.h>
#include <stdlib.h>

void swap(double *x, double *y)
{
    int temp = *x; // перезаписываем в темп значение из x
    *x = *y; // в х записываю значение у
    *y = temp; // в у значение х, просто по другому работать не будет, так как я на 8 строке утерял значение x
}
void bubble_sort(double *array, int n, int mode)
{
    int i, j;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (mode == 0)
            {
                if ( array[j] > array[j+1] )
                {
                    swap(&array[j], &array[j+1]);
                }
            }
            else
            {
               if ( array[j] < array[j+1] )
                {
                    swap(&array[j], &array[j+1]);
                } 
            }   
        }
    }
}

void matrix_print(double **matrix, int order, float code, int mode)
{
    int i, j;
    printf("\nThe printed matrix %.1f elements are: \n\n", code);
    for (i=0; i < order; i++)
    {
        for (j=0; j < order; j++)
        {
            if (mode == 0)
            {
                printf("%.1lf ", matrix[j][i]);
            }
            else
            {
                printf("%.1lf ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}
void matrix_gen(double **matrix, int order, float code)
{
    int i, j;  // i -> строки, j -> столбцы
    for(i=0; i < order; i++)
    {
        for (j = 0; j < order; j++)
        {
            printf("Enter the %.f matrix {%d %d} element: ", code, i+1, j+1);
            scanf("%lf", &matrix[j][i]);

        }
    }
    matrix_print(matrix, order, code, 0);
}
void matrix_sort(double **matrix, int order, float code)
{
    int i, j, k;
    for (k = 0; k < order; k++)
    {
        if (k%2==1)
        {
        bubble_sort(matrix[k], order, 0);
        }
        else
        {
        bubble_sort(matrix[k], order, 1);
        }
    }
    matrix_print(matrix, order, code, 0);
}
void matrix_square(double **fst, double **snd, double **res, int order, float code)
{
    int i, j, k;
    double tot = 0;
    for (i = 0; i < order; i++)
    {
        for (j = 0; j < order; j++)
        {
            for (k = 0; k < order; k++)
            {
                tot = tot + fst[i][k] * snd[k][j];
            }
            res[i][j] = tot;
            tot = 0;
        }
    }
    matrix_print(res, order, code, 0);

}
void matrix_copy(double **sourse, double **dest, int order)
{
    int i, j;
    for (i=0; i<order; i++)
    {
        for (j=0; j<order; j++)
        {
            dest[i][j] = sourse[i][j];
        }
    }
}
void matrix_free(double **matrix, int order)
{
    int i;
    for (i=0; i<order; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void main() 
{
    int n, i, j, k;
    
    printf("Enter matrix order: ");
    scanf("%d", &n);
    printf("\n");

    double **A = (double **)malloc( n * sizeof(int) );
    for (i = 0; i < n; i++)
    {
        A[i] = (double *)malloc(n * sizeof(int));
    }
    double **A_copy = (double **)malloc( n * sizeof(int) );
    for (i = 0; i < n; i++)
    {
        A_copy[i] = (double *)malloc(n * sizeof(int));
    }
    double **A_square = (double **)malloc( n * sizeof(int) );
    for (i = 0; i < n; i++)
    {
        A_square[i] = (double *)malloc(n * sizeof(int));
    }
    double **B = (double **)malloc( n * sizeof(int) );
    for (i = 0; i < n; i++)
    {
        B[i] = (double *)malloc(n * sizeof(int));
    }
    double **B_copy = (double **)malloc( n * sizeof(int) );
    for (i = 0; i < n; i++)
    {
        B_copy[i] = (double *)malloc(n * sizeof(int));
    }
    double **B_square = (double **)malloc( n * sizeof(int) );
    for (i = 0; i < n; i++)
    {
        B_square[i] = (double *)malloc(n * sizeof(int));
    }

    // malloc - возвращает указатель на распределенную память или нуль если не получилось

    matrix_gen(A, n, 1);
    matrix_sort(A, n, 1.1);
    matrix_copy(A, A_copy, n);
    matrix_square(A, A_copy, A_square, n, 1.2);

    printf("\n");

    matrix_gen(B, n, 2);
    matrix_sort(B, n, 2.1);
    matrix_copy(B, B_copy, n);
    matrix_square(B, B_copy, B_square, n, 2.2);

//----------------------------------------------------------------

    matrix_free(A, n);
    matrix_free(A_copy, n);
    matrix_free(A_square, n);

    matrix_free(B, n);
    matrix_free(B_copy, n);
    matrix_free(B_square, n);
}
