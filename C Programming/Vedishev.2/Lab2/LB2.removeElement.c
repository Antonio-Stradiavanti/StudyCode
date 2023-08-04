#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArr(int* arr, int total)
{
    int i;
    printf("\narray = ");
    for (i = 0; i < total; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n\n");
}

int main()
{
    int i, total = 0;

    int delete_index = 0, delete_value = 0; 
    printf("Enter total number of values to store:\n");
    scanf("%d", &total);
    int* arr = (int*)malloc(total * sizeof(int));

    for (i = 0; i < total; i++)
    {
        printf("array[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    printArr(arr, total);

    printf("Enter value index to delete:\n");
    scanf("%d", &delete_index);
    printf("\n");
    for (i = delete_index; i < total; i++)
    {
        arr[i] = arr[i+1];
    }
    total--;
    arr = (int*)realloc(arr, total);
    
    printArr(arr, total);

    free(arr);
    return 0;
}