#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CAP 100

void printArr(int* arr, int total)
{
    int i;
    printf("\n");
    for (i = 0; i < total; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int main()
{
    int i, total = 0; // Количество переменных, которые хранятся в массиве
    // Для вставки, Позиция, куда вставлять и значение, которое вставляем
    int insert_index = 0, insert_value = 0; 
    printf("Enter total number of values to store:\n");
    scanf("%d", &total);
    int* arr = (int*)malloc(total * sizeof(int));

    for (i = 0; i < total; i++)
    {
        printf("array[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    printArr(arr, total); 
    
    printf("Enter value to insert: "); scanf("%d", &insert_value);
    printf("Enter index to insert value at: "); scanf("%d", &insert_index);
    
    for (i = total; i > insert_index; i--)
    {
        arr[i] = arr[i-1];    
    }
    arr[insert_index] = insert_value;
    total++;
    arr = (int*)realloc(arr, total);

    printArr(arr, total);

    free(arr);
    return 0;
}
