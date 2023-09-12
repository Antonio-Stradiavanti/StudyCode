#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int i, j, k;

/*

- Алгоритм решения:
    - Разбить исходную последовательность на подпоследовательности размером sqrt(n)
    - Отсортировать эти подпоследовательности
    - Объединить их в один просматривая на каждом этапе первые элементы каждой из подпоследовательностей

*/

void printArray(int *A, int size);
void countingSort(int* M, int* N_M, int size);
void swap(int* A, int* B);
void bubbleSort(int* A, int size);

// объявим ф-ции
void balancedMergeSort(int *a, int n);
void balancedMergeSort_recursion(int *a, int l, int r);
void merge_sorted_arrays(int *a, int l, int m, int r);

void main()
{
    int a[] = {0, 93, 84, 7, 115, 6, 3, 1, 50};
    printArray(a, (int)sizeof(a)/4);

}
/*

Указатель - переменная, значение которой - адрес другой переменной  

* - в неоктором выражении обозначает операцию разыменовывания 

*/


void swap(int* A, int* B)
{   
    int tmp = *A;
    *A = *B;
    *B = tmp;
}

void printArray(int *A, int size)
{
    printf("\n");
    for (i = 0; i < size; i++)
    {
        printf("| %d |\n", A[i]);
    }
}

void bubbleSort(int *A, int n)
{
    int swapFlag;
    for (i = 0; i < n - 1; i++)
    {
        swapFlag = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
                swapFlag = 1;
            }
        }
        if (swapFlag = 0)
        {
            break;
        }
    }
}

void countingSort(int *M, int *N_M, int size)
{
    /* 
    Каждый из входных элементов - целое число из **интервала** от 0 до k.  
    */

    int count[k];
    for (i = 0; i < k; i++)
    {
        count[i] = 0;
        /* 
        числа из массива в порядке возрастания
        его походу придется тоже передавать в ф-цию
        */
    }

    for (i = 1; i < size; i++)
    {
        count[M[i]]++;
        /* 

        1. Массив-счетчик count содержит количество вхождений каждого из уникальных элементов в исходный последовательность M
            - (последовательность счетчик содержит максимальное количество элементов массива)
        
        Пример: пусть у меня в исходном массиве 4 повторяющихся элемента 1 тогда: count[1] == 4 

        */
    }

    for (i = 1 ; i < k; i++)
    {
        /*

        2. Путем накоптельного суммирования элементов массива count определяю сколько элементов могут стоять раньше или на том же месте что и рассматриваемый элемент исходного массива 

        */
        count[i] += count[i-1];
    }

    for (i = size-1; i >= 0; i--)
    {
        /*

        3. Выстраиваю элементы в новом массиве в правильном порядке

        Когда я расположил один экземпляр элемента в выходном массиве, я вычеркиваю одно его вхождение

        */
        N_M[count[M[i]]] = M[i];
        count[M[i]]--;
    }
}

void countingSort2(float* array, int n)
{
    // создается временный контейнер
    float* newArray = (float*)malloc(n * sizeof(float)); int count;
    
    for (i = 0; i < n; i++)
    {
        newArray[i] = FLT_MAX;
        // заполняю все элементы нового массива большими числами
    }

    for (i = 0; i < n; i++)
    {
        /*
        Сравнивает свякое число со всеми остальными элементами и определяет его позицию в отсортированном массиве
        */
        count = 0;
        for (j = 0; j < n; j++)
        {
            if (array[i] > array[j])
                count++;
        }
        newArray[count] = array[i];
    }

    for (i = 1; i < n; i++)
    {
        if (newArray[i] == FLT_MAX) newArray[i] = newArray[i - 1];
    }
    
    for (i = 0; i < n; i++)
    {
        // выставляю значения старого массива на правильные места.
        array[i] = newArray[i];
    }

    free(newArray);
}

void balancedMergeSort(int *a, int n)
{
    balancedMergeSort_recursion(a, 0, n - 1);    
}

void balancedMergeSort_recursion(int *a, int l, int r)
{

    /* 
    Разбиваю большой последовательность на мелкие
    
    второй и третий аргументы - границы рассматриваемой части исходного массива (изначально передаю исходный последовательность)
    */


    // если длина массива 1, то прекратить разбиение
    if (l < r)
    {
        // постоянно обновляю значение средней переменной
        int m = l + (r - 1) / 2;
        
        // рассматриваю все меньшую и меньшую левую часть исходного массива, которая левее m, m - включается.
        balancedMergeSort_recursion(a, l, m);
        
        // рассматриваю правую часть, она начинается с элемента, следующего после m
        balancedMergeSort_recursion(a, m + 1, r);

        // Объединяю и сортрую разбитые под-массивы
        merge_sorted_arrays(a, l, m, r);

    }

    // разбиваю полученный последовательность еще на 2 части (левую и правую)
}

void merge_sorted_arrays(int *a, int l, int m, int r)
{
    /* 
    Считаю размер каждого из временных массивов

    l, m -> крайние индексы левого массива => длина массива будет на 1 больше

    длина правого массива равна разности между r и m так как значение m берется изначально на 1 больше
    */
    int l_len = m - l + 1; 
    int r_len = r - m; 

    // временные подмассивы, в которые я буду копировать левую и правую части исходного массива. 
    int *temp_l = (int*)malloc(l_len * sizeof(int));
    int *temp_r = (int*)malloc(r_len * sizeof(int));

    // копирую соответствующие части исходного массива во временные массивы
    for (i = 0; i < l_len; i++)
    {
        temp_l[i] = a[l + i];
    }

    for (i = 0; i < r_len; i++)
    {
        temp_r[i] = a[m + 1 + i];
    }

    for ( i = 0, j = 0, k = l; k <= r; k++)
    {
        // k -> индекс сортируемого под-массива (а) мини сортировка ниже
        if ( ((i < l_len) && (j >= r_len)) || (temp_l[i] <= temp_r[j]) )
        {
           a[k] = temp_l[i]; i++; 
        }
        else
        {
            a[k] = temp_r[j]; j++;
        }
    }

    free(temp_l); free(temp_r);  
}