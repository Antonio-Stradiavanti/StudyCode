#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ARR_SIZE 2
#define ERROR1 "try again :("
#define ERROR2 "Struct not found!"
#define MAX2(a, b) (a > b) ? a : b
// Элемент информационного массива
typedef struct Record
{
    // С1 -> ключевое поле
    char C1;
	int Prices[ARR_SIZE];
    char C2;
} Record;
// Статья для единого справочника
typedef struct Entry
{
    char key;
    int index;
} Entry; 
typedef struct EntryPrices
{
    int key;
    int index;
} EntryPrices; 
// Элементы инверсных массивов
typedef struct inv_item
{
    char C12;
    int ind;
} inv_item;
typedef struct inv_Prices
{
    int Prices[ARR_SIZE];
    int ind;
} inv_Prices;
//---
// 0. Подготовка: генерация информационного массива, вывод структуры, сортировка
// 1. version 1.0 correct ? 1
Record* GenDataStore(int N)
{
    int i, j;
    Record* DataStore = (Record*)malloc(N * sizeof(Record));
    for (i = 0; i < N; i++)
    {
        //В таблице ASCII заглавные буквы латинского алфавита имеют порядковые номера от 65 до 90, это диапазон чисел от 0 до 25, так как остаток от деления никогда не превышает делителя получим:
        DataStore[i].C1 = rand()%26 + 65;
        for (j = 0; j < ARR_SIZE; j++)
            DataStore[i].Prices[j] = rand() % 1000;
        DataStore[i].C2 = rand()%26 + 65;
    }
    // Возвращаю адрес млажшего байта выделенной области памяти
    return DataStore;
}
// 0. version 1.0 -> correct ? 1
void structPrint(Record* nStore)
{
    int i;
    printf("\n[\n");
    printf("\titem: %c; price: %d;\n", nStore->C1, nStore->Prices[0]);
    printf("\titem: %c; price: %d;\n", nStore->C2, nStore->Prices[1]);
    printf("]\n");
}
void printPrices(inv_Prices* PricesStore, int num)
{
	int i;
	printf("\nN%d\nPrices[2]:\n", num);
    for (i = 0; i < ARR_SIZE; i++)
    {
        printf("%d ", PricesStore->Prices[i]);
    }
    printf("\nind: %d\n", PricesStore->ind);
}
void printItem(inv_item* ItemStore)
{
	printf("\nItem: %c; ind: %d;\n", ItemStore->C12, ItemStore->ind);
}
// 1. Ф-ции сортировки методом вставки
void ItemInsSort(inv_item* inv_C1Store, int N)
{
    int i = 0, loc = 0;
    inv_item NE;
    // один элемент уже составляет отсортированную последовательность
    for (i = 1; i < N; i++)
    {
        loc = i - 1;
        NE = *(inv_C1Store + i);
        // loc идет от крайнего элемента отсортированной последовательности к нулевому (если потребуется)
        // Сравниваю элементы по значению ключа
		while ((loc >= 0) && ((inv_C1Store + loc)->C12 > NE.C12))
        {
            // пока элемент стоит не на своем месте, я его переставляю переставляю на позицию впрааво в отсортированной последовательности
			*(inv_C1Store + loc + 1) = *(inv_C1Store + loc);
            loc--;  
        }
        // Ставлю больший элемент на позицию меньшего
		*(inv_C1Store + loc + 1) = NE;
    }
}
// 2. version - 1.0 -> correct ? подлежит проверке и отладке
void PricesInsSort(inv_Prices* PricesStore, int N)
{
    int i = 0, loc = 0;
    inv_Prices NE;
    // один элемент уже составляет отсортированную последовательность
    for (i = 1; i < N; i++)
    {
        loc = i - 1;
        NE = *(PricesStore + i);
        // loc идет от крайнего элемента отсортированной последовательности к нулевому (если потребуется)
        // Сравниваю элементы по значению ключа
		while ((loc >= 0) && ((PricesStore + loc)->Prices[0] > NE.Prices[0]))
        {
            // пока элемент стоит не на своем месте, я его переставляю переставляю на позицию впрааво в отсортированной последовательности
			*(PricesStore + loc + 1) = *(PricesStore + loc);
            loc--;  
        }
        // Ставлю больший элемент на позицию меньшего
		*(PricesStore + loc + 1) = NE;
    }
}
// ---
// 2. Единый справочник
// 1. version - 1.0 -> correct ? 1, все работает идеально.
Entry* createItemEntries(inv_item* inv_C1Store, int N, int blockCount, int blockSize)
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
    Entry* ItemEntries = (Entry*)malloc(blockCount * sizeof(Entry));
    for (i = 0; i < blockCount; i++)
    {
        if (i != blockCount - 1)
        {
            /*
            *(DataStore + i*sizes[i] + sizes[i] - 1)

            нулевое слагаемое → относительный адрес, начиная с которого размещаются структуры информационного массива
            
            первое слагаемое → сдвигает адрес на нулевой элемент каждого блока, 
            
            второе слагаемое → сдвигает адрес на нулевой элемент следующего за i-м блоком
            
            третье слагаемое → откатывает ардес на последний элемент i-го блока 
            */
			(ItemEntries + i)->key = (inv_C1Store + i*sizes[i] + sizes[i] - 1)->C12;
            // адрес нулевой записи i-го блока 
			(ItemEntries + i)->index = i*sizes[i];
        }
        else
        {
            // Для последнего блока:
			(ItemEntries + i)->key = (inv_C1Store + i*sizes[i - 1] + sizes[i] - 1)->C12;
			(ItemEntries + i)->index = i*sizes[i - 1];
        }
    }
    // Очистка памяти
    free(sizes);
    // возвращаю адрес младшего байта созданного справочника для переданного информационного массива. 
	return ItemEntries;
}
EntryPrices* createPricesEntries(inv_Prices* PricesStore, int N, int blockCount, int blockSize, int mode)
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
    EntryPrices* EntriesPrices = (EntryPrices*)malloc(blockCount * sizeof(EntryPrices));
    for (i = 0; i < blockCount; i++)
    {
        if (i != blockCount - 1)
        {
            /*
            Добавляю ключевое поле полностью.

            *(DataStore + i*sizes[i] + sizes[i] - 1)

            нулевое слагаемое → относительный адрес, начиная с которого размещаются структуры информационного массива
            
            первое слагаемое → сдвигает адрес на нулевой элемент каждого блока, 
            
            второе слагаемое → сдвигает адрес на нулевой элемент следующего за i-м блоком
            
            третье слагаемое → откатывает ардес на последний элемент i-го блока 
            */
           
            (EntriesPrices + i)->key = (PricesStore + i*sizes[i] + sizes[i] - 1)->Prices[mode];
            // адрес нулевой записи i-го блока 
            (EntriesPrices + i)->index = i*sizes[i];
        }
        else
        {
            // Для последнего блока:
            (EntriesPrices + i)->key = (PricesStore + i*sizes[i - 1] + sizes[i] - 1)->Prices[mode];
            (EntriesPrices + i)->index = i*sizes[i - 1];
        }
    }
    // Очистка памяти
    free(sizes);
    // возвращаю адрес младшего байта созданного справочника для переданного информационного массива. 
	return EntriesPrices;
}
/* 
    3. Одноаспектный поиск по совпадению
    correct? ?
    Интерфейс ф-ции: информационный массив, его размер, единый справочник, количество блоков
    Будет 2 поиска по совпадению для каждого инверсного массива
*/ 
int* ItemMatchSearch(inv_item* inv_C1Store, int N, Entry* EntriesC1, int blockCount, char argC1, int* cfoundi)
{
    int i, j, found = -1;
    // Создаю массив адресов найденных элементов в инверсном массиве для полей C12, размер которого изменяется от количества найденных элементов
    int* resi = (int*)calloc(N, sizeof(int));
    // Аргумент поиска я передаю, прохожу по справочнику
    for (i = 0; i < blockCount; i++)
    {
        // Находится статья, значение ключа которой больше чем аргумент аргумент поиска 1
        if (EntriesC1[i].key >= argC1)
        {
            // Перед каждой процедурой считывания записи осуществляется проверка достижения конца массива. 1
            if (i != blockCount-1)
            {
                // Затем в **информационном массиве** проводится **последовательный поиск** начиная с адреса первой записи найденного блока и до адреса первой записи следующего блока.
                for (j = EntriesC1[i].index; j < EntriesC1[i+1].index; j++)
                {
                    // Записи информационного массива в рамках текущего блока последовательно считываются и по каждой из них принимается решение о выдаче в качестве результата в соответствии с аргументом поиска.
                    if (inv_C1Store[j].C12 == argC1)
                    {
                        // Добавляю адрес найденного элемента в инверсном массиве в массив результатов            
                        found+=1;
                        resi[found] = inv_C1Store[j].ind;
                    }
                }
            }
            else
            {
                for (j = EntriesC1[i].index; j < N; j++)
                {
                    if (inv_C1Store[j].C12 == argC1)
                    {
                        found+=1;
                        resi[found] = inv_C1Store[j].ind;
                    }
                }
            }
        }
    } 
    if (found == -1)
    {
        return NULL;
    }
    else 
    { 
        *cfoundi = found+1;
        // В моем случае - возвращает тот же адрес, освобождает ячейки, находящиеся за пределами found+1.
        resi = (int*)realloc(resi, sizeof(int)*(found+1));
        return resi;
    }
}
int* PricesMatchSearch(inv_Prices* PricesStore, int N, EntryPrices* EntriesPrices, int blockCount, int argPrice, int* cfoundi, int mode)
{
    int i = 0, j = 0, k = 0, l, found = -1, matchCounter = 0;
    // 1
    int* resi = (int*)calloc(N, sizeof(int));
    for (i = 0; i < blockCount; i++)
    {
        if (EntriesPrices[i].key >= argPrice)
        {
            // Перед каждой процедурой считывания записи осуществляется проверка достижения конца массива. 1
            if (i != blockCount-1)
            {
                // Затем в **информационном массиве** проводится **последовательный поиск** начиная с адреса первой записи найденного блока и до адреса первой записи следующего блока.
                for (j = EntriesPrices[i].index; j < EntriesPrices[i+1].index; j++)
                {
                    // Записи информационного массива в рамках текущего блока последовательно считываются и по каждой из них принимается решение о выдаче в качестве результата в соответствии с аргументом поиска.
                    if (PricesStore[j].Prices[mode] == argPrice)
                    {
                        // Добавляю адрес найденного элемента в инверсном массиве в массив результатов            
                        found+=1;
                        resi[found] = PricesStore[j].ind;
                    }
                }
            }
            else
            {
                for (j = EntriesPrices[i].index; j < N; j++)
                {
                    if (PricesStore[j].Prices[mode] == argPrice)
                    {
                        found+=1;
                        resi[found] = PricesStore[j].ind;
                    }
                }
            }
        }
    }
    if (found == -1)
    {
        return NULL;
        printf("ERROR!");
    }
    else
    {
        *cfoundi = found + 1;
        resi = (int*)realloc(resi, sizeof(int)*(found + 1));
        return resi;
    }
}
// Пересечение
int* inter(int* A, int sizeA, int* B, int sizeB, int* cfound)
{
    int i, j, found = -1;
    int maxSize = MAX2(sizeA, sizeB);
    int* res = (int*)malloc(maxSize * sizeof(int));
    for (i = 0; i < sizeA; i++)
    {
        for (j = 0; j < sizeB; j++)
        {
            if (A[i] == B[j])
            {
                found+=1;
                res[found] = A[i];
            }
        }
    }
    if (found == -1)
    {
        return NULL;
    }
    else
    {
        *cfound = found+1;
        res = (int*)realloc(res, found+1);
        return res;
    }
}
int* inter4(int* A, int sizeA, int* B, int sizeB, int* C, int sizeC, int* D, int sizeD, int* tcfound)
{
    int cfound1, cfound2;
    int* tempres1 = inter(A, sizeA, B, sizeB, &cfound1);
    int* tempres2 = inter(C, sizeC, D, sizeD, &cfound2);
    if (tempres1 == NULL || tempres2 == NULL)
    {
        free (tempres1); free(tempres2);
        printf("\nEmpty array\n");
        return NULL;
    }
    else
    {
        int* res = inter(tempres1, cfound1, tempres2, cfound2, tcfound);
        if (res == NULL)
        {
            printf("\nEmpty array\n");
            free (tempres1); free(tempres2); free(res);
            return NULL;
        }
        else
        {
            free (tempres1); free(tempres2);
            return res;
        }
    }
}
// Вывод
void printItemEntries(Entry* EntriesCi, int blockCount, int num)
{
	int i;
	printf("\nItem Entries%d:\n", num);
	for (i = 0; i < blockCount; i++)
	{
		printf("Entry %d: last entry key value: %c, first entry index: %d\n", i, EntriesCi[i].key, EntriesCi[i].index);
	}
}
void printPricesEntries(EntryPrices* EntriesBi, int blockCount, int num)
{
	int i, j;
	printf("\nPrices Entries%d:\n", num);
	for (i = 0; i < blockCount; i++)
	{
        printf("\nEntry%d:\nlast entry key value: %d\n", i, EntriesBi[i].key);
        printf("first entry index: %d\n", EntriesBi[i].index);
	}
}
void printRes(Record* DataStore, int* resi, int cfoundi, int num)
{
	int i;
	printf("\nMatch search: %d \n", num);
	printf("cfound%d = %d\n", num, cfoundi);
	if (resi != NULL)
	{
		for (i = 0; i < cfoundi; i++)
		{
			// Вывожу результат из информационного массива, а не из инверсного
			printf("\tindex: %d\n", resi[i]);
			structPrint(DataStore+resi[i]);
		}
		printf("\n");
	}
	else
	{
		printf("\nElement not found\n");
	}
}
// Главная ф-ция
// Оставим теперь только ф-ции, отвечающие за целые
int main()
{
    srand(time(NULL));
    int i, j, N = 3, cfound1 = 0, cfound2 = 0, cfound3 = 0, cfound4 = 0, tcfound, blockCount, blockSize;
	char isexit;
    // Поисковой запрос
    int argPrice1 = 0, argPrice2 = 0;
	char argItem1 = 0, argItem2 = 0;
	do
	{
        printf("Enter the size of Origin Array:\n"); 
        fflush(stdin);
		scanf("%d", &N);
		// Размер блока - целая часть квадратного кореня из количетва записей
		blockSize = sqrt(N);
		// Количество блоков - округленное в большую сторону частное от количества элементов в информационном массиве на размер каждого блока. 
		blockCount = ceil((double)N / blockSize);

		// Генерируем информационный массив correct ? 1
		Record* DataStore = GenDataStore(N);

        // Создадим инверсные массивы и выведем их:
        inv_Prices* PricesStore = (inv_Prices*)malloc(N * sizeof(inv_Prices));
		inv_item* ItemStore1 = (inv_item*)malloc(N * sizeof(inv_item));
		inv_item* ItemStore2 = (inv_item*)malloc(N * sizeof(inv_item));
        
		// Выводим ифнформационный массив; correct ? 1
		printf("Let's print Data Store:\n");
		for (i = 0; i < N; i++)
		{
        	structPrint(DataStore+i);
		}

		// Заполним инверсные массивы;
        for (i = 0; i < N; i++)
		{
            ItemStore1[i].C12 = DataStore[i].C1;
			ItemStore1[i].ind = i;

			ItemStore2[i].C12 = DataStore[i].C2;
			ItemStore2[i].ind = i;
            for (j = 0; j < ARR_SIZE; j++)
            {
                PricesStore[i].Prices[j] = DataStore[i].Prices[j];
            }
            PricesStore[i].ind = i;
		}
		// Сортирую инверсный массив: сначала внутренние массивы каждой из структур, потом сам инверсный массив; correct 1
		ItemInsSort(ItemStore1,N);
        ItemInsSort(ItemStore2,N);
        PricesInsSort(PricesStore, N);

		// Вывод инверсных массивов; correct ? 1
        /* printf("\nLet's print ItemStore1:\n");
        for (i = 0; i < N; i++)
        {
            printItem(ItemStore1+i);
        }
        printf("\nLet's print ItemStore2:\n");
        for (i = 0; i < N; i++)
        {
            printItem(ItemStore2+i);
        }
        printf("\nLet's print PricesStore:\n");
		for (i = 0; i < N; i++)
        {
            printPrices(PricesStore+i, i);
        } */
		
		// Создание единых справочникоы для отсортированных инверсных массивов; correct ? 1
		EntryPrices* PricesEntries1 = createPricesEntries(PricesStore, N, blockCount, blockSize, 0);
        EntryPrices* PricesEntries2 = createPricesEntries(PricesStore, N, blockCount, blockSize, 1);
        Entry* ItemEntries1 = createItemEntries(ItemStore1, N, blockCount, blockSize);
        Entry* ItemEntries2 = createItemEntries(ItemStore2, N, blockCount, blockSize);

		// Вывожу Единый справочник для инверсных массивов correct ? 0
        //printPricesEntries(PricesEntries1, blockCount, 0);
        //printPricesEntries(PricesEntries2, blockCount, 1);
        //printItemEntries(ItemEntries1, blockCount, 0);
        //printItemEntries(ItemEntries2, blockCount, 1);

		// Одноаспектный поиск целых в инверсном массиве: correct ? 0
        printf("\n--- SEARCH QUERY ---\nEnter a search query in the following order:\n[1 -> (char) item1; 2 -> (int) price1; 3 -> (char) item2; 4 -> (int) price2]\n");
        fflush(stdin);
        scanf(" %c", &argItem1); 
        fflush(stdin);
        scanf("%d", &argPrice1); 
        fflush(stdin);
        scanf(" %c", &argItem2); 
        fflush(stdin);
        scanf("%d", &argPrice2); 
        printf("---Ok, I'll try to find it, please wait---");
        int* resItem1 = ItemMatchSearch(ItemStore1, N, ItemEntries1, blockCount, argItem1, &cfound1);
        int* resPrices1 = PricesMatchSearch(PricesStore, N, PricesEntries1, blockCount, argPrice1, &cfound2, 0);
        int* resItem2 = ItemMatchSearch(ItemStore2, N, ItemEntries2, blockCount, argItem2, &cfound3);
        int* resPrices2 = PricesMatchSearch(PricesStore, N, PricesEntries2, blockCount, argPrice2, &cfound4, 1);

		// Вывожу результат одноаспектного поиска в инверсном массиве и значение по индексам из ифнормационного массива, все работает. correct ? 1
        printRes(DataStore, resItem1, cfound1, 1);
        printRes(DataStore, resPrices1, cfound3, 2);
		printRes(DataStore, resItem2, cfound2, 3);
        printRes(DataStore, resPrices2, cfound4, 4);

        // Найдем пересечение:
        int* tres = inter4(resItem1, cfound1, resItem2, cfound2, resPrices1, cfound3, resPrices2, cfound4, &tcfound);
        if (tres == NULL)
        {
            printf("Not found :(");
        }
        else
        {
            printf("--- Result of the intersection ---\n");
            printRes(DataStore, tres, tcfound, 5);
        }
		
        // Очистка памяти
        free(ItemStore1); free(ItemStore2); free(PricesStore); free(DataStore); free(PricesEntries1); free(PricesEntries2); free(ItemEntries1); free(ItemEntries2);
        free(resPrices1); free(resPrices2); free(resItem1); free(resItem2);
        free(tres);
        printf("is exit? [78 -> N, 89 -> Y]\n"); 
		fflush(stdin);
		scanf(" %c", &isexit);
	} while (isexit != 89);
    return 0;
}
