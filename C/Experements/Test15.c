#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 10
typedef struct Record
{
    // С1 -> ключевое поле
    char C1;
    int B[ARR_SIZE];
    char C2;
} Record;
void insSort(Record* str, int N)
{
    int i = 0, loc = 0;
    Record NE;
    // один элемент уже составляет отсортированную последовательность
    for (i = 1; i < N; i++)
    {
        loc = i - 1;
        NE = *(str + i);
        // loc идет от крайнего элемнта отсортированной последовательности к нулевому (если потребуется)
        // Сравниваю элементы по значению ключа
        while ((loc >= 0) && ((str+loc)->C1 > NE.C1))
        {
            // пока элемент стоит не на своем месте, я его переставляю переставляю на позицию впрааво в отсортированной последовательности
            *(str+loc+1) = *(str+loc);
            loc--;  
        }
        // Ставлю больший элемент на позицию меньшего
        *(str+loc+1) = NE;
    }
}
void structPrint(Record* str)
{
    int i;
    printf("\n[\n");
    printf("\tkey char1: %c\n", str->C1);
    printf("\tarray:\n\t[\n");
    for (i = 0; i < ARR_SIZE; i++)
        printf("\t%d el: %d\n", i, str->B[i]);
    printf("\t]\n");
    printf("\tchar2: %c", str->C2);
    printf("\n]\n");
}
Record* DataStore(int N)
{
    int i, j;
    Record* DataStore = (Record*)malloc(N * sizeof(Record));
    for (i = 0; i < N; i++)
    {
        //В таблице ASCII заглавные буквы латинского алфавита имеют порядковые номера от 65 до 90, это диапазон чисел от 0 до 25, так как остаток от деления никогда не превышает делителя получим:
        DataStore[i].C1 = rand()%26 + 65;
        for (j = 0; j < ARR_SIZE; j++)
            DataStore[i].B[j] = rand() % 1000;
        DataStore[i].C2 = rand()%26 + 65;
    }
    // Возвращаю адрес млажшего байта выделенной области памяти
    return DataStore;
}
int main()
{
    int i;
    Record* A = DataStore(2);
    printf("\nOrigin:\n");
    for (i = 0; i < 2; i++)
        structPrint(A+i);
    insSort(A, 2);
    printf("\nSorted:\n");
    for (i = 0; i < 2; i++)
        structPrint(A+i);
    free(A);
    return 0;
}