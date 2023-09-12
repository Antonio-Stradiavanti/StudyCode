#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 2
#define ERROR1 "try again :("
#define ERROR2 "Struct not found!"
typedef struct Record
{
    char C1;
    char C2;
    int B[ARR_SIZE];
} Record;
void structPrint(Record* str)
{
    int i;
    printf("\n[\n");
    printf("\tkey char1: %c\n", str->C1);
    printf("\tarray:\n\t[\n");
    for (i = 0; i < ARR_SIZE; i++)
        printf("\t\t%d el: %d\n", i, str->B[i]);
    printf("\t]\n");
    printf("\tchar2: %c", str->C2);
    printf("\n]\n");
}
void searchTst(Record* DataStore, int N)
{
    int i, j, k, found = 0, criteriaNum = 0, criteriaOption = 0, intArg = 0, intMode, range = 1, matchCounter = 0;
    char charArg;
    printf("Enter search argument, enter number of criteria:\n[1 -> one, 2 -> two]\n"); 
    fflush(stdin);
    scanf("%d", &criteriaNum);
    // Это работает
    switch (criteriaNum)
    {
    case 1:
        printf("choose on of these options: [1 -> char, 2 -> int]\n");
        fflush(stdin);
        scanf("%d", &criteriaOption);
        switch (criteriaOption)
        {
        case 1:
            printf("Enter a char:\n");
            fflush(stdin);
            scanf("%c", &charArg);
            for (i = 0; i < N; i++)
            {
                if ((i != N-1) && (DataStore[i].C1 == charArg || DataStore[i].C2 == charArg))
                {
                    found = 1;
                    structPrint(DataStore+i);
                    break;
                }
            }
            if (!found) printf("Struct not found!");    
            break;
        case 2:
            printf("Enter an integer\n");
            fflush(stdin);
            scanf("%d", &intArg);
            for (i = 0; i < N; i++)
            {
                for (j = 0; i < ARR_SIZE; j++)
                {
                    if (DataStore[i].B[j] == intArg)
                    {
                        found = 1;
                        structPrint(DataStore+i);
                        break;
                    }       
                }
            }
            if (!found) printf("Struct not found!");
            break;    
        default:
            printf(ERROR1);
            break;
        }
        break;
    case 2:
        // Многоаспектный поиск
        // Реализовать ввод диапазона поиска
        printf("Enter a char\n");
        fflush(stdin);
        scanf("%c", &charArg);
        printf("\nenter an integer or more integers [1 -> 1 integer, 2 -> integer range]\n");
        fflush(stdin);
        scanf("%d", &intMode);
        if (intMode == 2)
        {
            printf("Enter number of integers to search, note: this number should not exceed %d\n", ARR_SIZE);
            scanf("%d", &range);
            int* rangeNums = (int*)malloc(range * sizeof(int));
            for (i = 0; i < range; i++)
            {
                printf("Enter %d integer: ", i); scanf("%d", &rangeNums[i]);
            }
            for (i = 0; i < N; i++)
            {
                if (DataStore[i].C1 == charArg || DataStore[i].C2 == charArg)
                {
                    for (j = 0; j < range; j++)
                    {
                        for (k = 0; k < ARR_SIZE; k++)
                        {
                            // Проверить на соответствие целому диапазону чисел
                            if (rangeNums[j] == rangeNums[k])
                            {
                                matchCounter++;
                            }
                        }
                    }
                    if (matchCounter == range)
                    {
                        found = 1;
                        printf("\nMatch counter: %d\n", matchCounter);
                        structPrint(DataStore+i);
                        break;
                    }    
                }
            }
            if (!found) 
            {
                printf(ERROR2);
            }
            free(rangeNums);
        }
        else
        {
            printf("Enter an integer:\n");
            fflush(stdin); scanf("%d", &intArg);
            for (i = 0; i < N; i++)
            {
                if (DataStore[i].C1 == charArg || DataStore[i].C2 == charArg)
                {
                    for (j = 0; j < ARR_SIZE; j++)
                    {
                        if (DataStore[i].B[j] == intArg)
                        {
                            found = 1;
                            structPrint(DataStore+i);
                            break;
                        }
                    }
                }
            }
            if (!found) printf(ERROR2);
        }
        
        break;
    default:
        printf(ERROR1);
        break;
    }
}
int main()
{
    char isexit;
    Record DataStore[3] = 
        {
            DataStore[0].C1 = 'A',
            DataStore[0].C2 = 'C',
            DataStore[0].B[0] = 44, DataStore[0].B[1] = 43,
            DataStore[1].C1 = 'B',
            DataStore[1].C2 = 'D',
            DataStore[1].B[0] = 42, DataStore[1].B[1] = 41,
            DataStore[2].C1 = 'B',
            DataStore[2].C2 = 'E',
            DataStore[2].B[0] = 34, DataStore[2].B[1] = 32,
        };
    do 
    {
        searchTst(DataStore, 3);
        printf("is exit? [78 -> N, 89 -> Y]\n");
        fflush(stdin);
        scanf("%c", &isexit);
    } while (isexit != 89);
    return 0;
}