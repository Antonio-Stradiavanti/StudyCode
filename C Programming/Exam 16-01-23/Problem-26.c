#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int i, j = 0;
// объявление ф-ции
int *remove_dublicates(int *arr, int n, int *new_len);

void main()
{
    int n = 0;
    printf("Enter the size of the array: "); 
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));

    // генерирую массив
    for (i = 0; i < n ; i++)
    {
        printf("Enter the %d element of the array: ", i);
        scanf("%d", &arr[i]);
    }

    // вывожу исхожный массив
    for (i = 0; i < n ; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    int new_len = 0;
    // создаю адрес для нового массива
    // длина в виде указателя нужна для удобного вывода нового массива
    int *clear_arr = remove_dublicates(arr, n, &new_len);

    for (i = 0; i < new_len; i++)
    {
        printf("clean_arr[%d] = %d\n", i, clear_arr[i]);
    }

    free(arr);
    free(clear_arr);
}

// определение ф-ции
int *remove_dublicates(int *arr, int n, int *new_len)
{
    int *new_arr = (int*)malloc(n*sizeof(int)); // храню новый массив, в котором нет дубликатов

    // realloc для изменения размера динамического массива

    int u_c = 0;
    for (i = 0; i < n; i++)
    {
        bool is_unique = true;
        // первая итерация скипнется
        for (j = 0; j < u_c; j++)
        {
            if (new_arr[j] == arr[i])
            {
                is_unique == false;
                break;
            }
        }
        if (is_unique)
        {
            new_arr[u_c] = arr[i];
            u_c++;  
        }
    }
    // новый размер нового массива
    if (u_c != n)
    {
        new_arr = realloc(new_arr, u_c * sizeof(int));
    }
    
    *new_len = u_c;

    free(new_arr);
    // возвращает указатель на новый массив, которого пока нет
    // я очищаю память из под него только в ф-ции main()
}