#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 2
#define BLOCK_SIZE 2

typedef struct Data 
{
    char C1_key;
    int A[ARR_SIZE];
    char C2;
} Data;

typedef struct BlockNode
{
    int elCnt;
    Data LocalDataStore[BLOCK_SIZE];
} BlockNode;

void PrintElem(Data Elem)
{
	int j;
	printf("\n\t[\n\t\tC1_key: %c,\n\t\tC2: %c,\n\t\tA: [ ", Elem.C1_key, Elem.C2);
    for (j = 0; j < ARR_SIZE-1; j++)
    {
        printf("%d, ", Elem.A[j]);
    }
    printf("%d ]\n\t]", Elem.A[j]);
}

void PrintNode(BlockNode* BB)
{
    int i;
    printf("\nBlock node No %d (elements: %d):\n[", 1, BB->elCnt);
    for (i = 0; i < BB->elCnt-1; i++)
    {
        PrintElem(BB->LocalDataStore[i]); printf(",");
    }
    PrintElem(BB->LocalDataStore[i]); printf("\n]\n");
}
void find(BlockNode* BB, Data sArg)
{
    int fflag = 0, i, j, eqC = 0;
    for (i = 0; i < BB->elCnt; i++)
    {
        if (sArg.C1_key == BB->LocalDataStore[i].C1_key && sArg.C2 == BB->LocalDataStore[i].C2)
        {
            for (j = 0; j < ARR_SIZE; j++)
            {
                if (sArg.A[j] == BB->LocalDataStore[i].A[j]) eqC++;
            }
            printf("eqC = %d\n", eqC);
            if (eqC == ARR_SIZE) 
            {
                PrintElem(BB->LocalDataStore[i]);
            }
            fflag = 1;
        }
    }
	if (!fflag) printf("Element not found :(\n");
}

int main()
{
    int i;
    BlockNode BB;
    BB.LocalDataStore[0].C1_key = 'A',
    BB.LocalDataStore[0].C2 = 'B';
    BB.LocalDataStore[0].A[0] = 12;
    BB.LocalDataStore[0].A[1] = 13;
    
    BB.LocalDataStore[1].C1_key = 'B';
    BB.LocalDataStore[1].C2 = 'C';
    BB.LocalDataStore[1].A[0] = 14;
    BB.LocalDataStore[1].A[1] = 15;
    
    BB.elCnt = 2;

    Data sArg;
    sArg.C1_key = 'A'; sArg.C2 = 'B';
    sArg.A[0] = 12; sArg.A[1] = 13;

    PrintNode(&BB);
    printf("\nfind:\n");
    find(&BB, sArg);
    return 0;
}