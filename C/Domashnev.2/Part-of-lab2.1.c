#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Entry
{
    char key;
    int index;
} Entry; 

typedef struct inv_C1
{
    char C1;
    int ind;
} inv_C1;

Entry* createEntries(inv_C1* inv_C1Store, int N, int blockCount, int blockSize)
{
    // В справочнике всего корень из N элементов
    int i;
    // Информационный массив разбивается на блоки размером blockSize, так как округление параметра количество блоков производится в большую сторону последнем блоке будет некоторое количетсво "пустых" ячеек
    // Разбиение на блоки не выполяется буквально!
    int garbage = blockCount * blockSize - N;
    int* sizes = (int*)malloc(blockCount * sizeof(int));
    for (i = 0; i < blockCount; i++)
    {
        // размер всех блоков кроме последнего равен blockSize
        if (i != blockCount - 1)
            sizes[i] = blockSize;
        else 
            sizes[i] = blockSize - garbage;
    }
    // Для каждого блока создается статься, следовательно формируем массив статей для каждого блока. Статья содержит: в поле ключа → значение ключа последней записи блока, в поле указателя → указатель на адрес первой записи в блоке.
    Entry* Entries = (Entry*)malloc(blockCount * sizeof(Entry));
    for (i = 0; i < blockCount; i++)
    {
        if (i != blockCount - 1)
        {
            /*
            *(inv_C1Store + i*sizes[i] + sizes[i] - 1)

            нулевое слагаемое → относительный адрес, начиная с которого размещаются структуры информационного массива
            
            первое слагаемое → сдвигает адрес на нулевой элемент каждого блока, 
            
            второе слагаемое → сдвигает адрес на нулевой элемент следующего за i-м блоком
            
            третье слагаемое → откатывает ардес на последний элемент i-го блока 
            */
            (Entries + i)->key = (inv_C1Store + i*sizes[i] + sizes[i] - 1)->C1;
            // адрес нулевой записи i-го блока 
            (Entries + i)->index = i*sizes[i];
        }
        else
        {
            // Для последнего блока:
            (Entries + i)->key = (inv_C1Store + i*sizes[i-1] + sizes[i] - 1)->C1;
            (Entries + i)->index = i*sizes[i-1];
        }
    }
    // Очистка памяти
    free(sizes);
    // возвращаю адрес младшего байта созданного справочника для переданного информационного массива. 
    return Entries;
}
/* 
    Одноаспектный поиск по совпадению
    correct? ?
    Интерфейс ф-ции: информационный массив, его размер, единый справочник, количество блоков
    Будет 3 поиска по совпадению для каждого инверсного массива
*/ 
int* MatchSearchC1(inv_C1* inv_C1Store, int N, Entry* EntriesC1, int blockCount, char argC1, int* foundc)
{
    int i, j, found = -1;
    // Создаю массив адресов найденных элементов в инверсном массиве для полей C1, размер которого изменяется от количества найденных элементов
    int* res = (int*)calloc(N, sizeof(int));
    // Аргумент поиска я передаю
    // Прохожу по справочнику
    for (i = 0; i < blockCount; i++)
    {
        // Находится статья, значение ключа которой больше чем аргумент аргумент поиска
        if (EntriesC1[i].key >= argC1)
        {
            // Перед каждой процедурой считывания записи осуществляется проверка достижения конца массива.
            if (i != blockCount-1)
            {
                // Затем в **информационном массиве** проводится **последовательный поиск** начиная с адреса первой записи найденного блока и до адреса первой записи следующего блока.
                for (j = EntriesC1[i].index; j < EntriesC1[i+1].index; j++)
                {
                    // Записи информационного массива в рамках текущего блока последовательно считываются и по каждой из них принимается решение о выдаче в качестве результата в соответствии с аргументом поиска.
                    if (inv_C1Store[j].C1 == argC1)
                    {
                        // Добавляю адрес найденного элемента в инверсном массиве в массив результатов            
                        found+=1;
                        res[found] = inv_C1Store[j].ind;
                    }
                }
            }
            else
            {
                for (j = EntriesC1[i].index; j < N; j++)
                {
                    if (inv_C1Store[j].C1 == argC1)
                    {
                        found+=1;
                        res[found] = inv_C1Store[j].ind;
                    }
                }
            }
        }
    } 
    if (found == 0)
    {
        printf("Element not found\n");
        return NULL;
    }
    else 
    {
        *foundc = found+1;
        return realloc(res, found+1);
    }
}

int main()
{
    int foundc = 0;
    inv_C1 inv_C1Store[3] = 
        {
            inv_C1Store[0].C1 = 'A',
            inv_C1Store[0].ind = 0,
            inv_C1Store[1].C1 = 'A',
            inv_C1Store[1].ind = 1,
            inv_C1Store[2].C1 = 'B',
            inv_C1Store[2].ind = 2
        };
    Entry* Entries = createEntries(inv_C1Store, 3, 1, 3);
    int* res = MatchSearchC1(inv_C1Store, 3, Entries, 1, 'A', &foundc);
    printf("%d\n\n", foundc);
    for (int i = 0; i < foundc; i++)
    {
        printf("%d\n", res[i]);
    }
    free(Entries); free(res);
    return 0;
}