#include <stdio.h>
#include <stdlib.h>

void main()
{
    int n, i, j, summ_even = 0, summ_odd = 0;
    printf("Enter the size of the array: "); scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        printf("Enter the [ %d ] array element: ", i); scanf("%d", &arr[i]);
        printf("| %d |\n", arr[i]);
    }

    for (i = 0; i < n; i++)
    {
        if ( i % 2 == 0 )
        {
            summ_even += arr[i];
        }
        else
        {
            summ_odd += arr[i];
        }
    }

    printf("sum of elements with even indeces: | %d |\nsum of elements with odd indeces: | %d |\n", summ_even, summ_odd);
    free(arr);
}
