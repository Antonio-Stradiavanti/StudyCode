#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#define ARR_SIZE 10
#define ERROR1 "try again :("
#define ERROR2 "Struct not found!"
#define MAX2(a, b) (a > b) ? a : b
#define MAX3(a, b, c) MAX2(a, MAX2(b, c))
// Элемент информационного массива
typedef struct Record
{
    // С1 -> ключевое поле
    char C1;
	int B[10];
    char C2;
} Record;
// Статья для единого справочника
typedef struct Entry
{
    char key;
    int index;
} Entry; 
typedef struct EntryB
{
	int key;
	int index;
} EntryB;
// Структуры для инверсных массивов
typedef struct inv_C12
{
    char C12;
    int ind;
} inv_C12;
typedef struct inv_B
{
    int B[ARR_SIZE];
    int ind;
} inv_B;
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
            DataStore[i].B[j] = rand() % 1000;
        DataStore[i].C2 = rand()%26 + 65;
    }
    // Возвращаю адрес млажшего байта выделенной области памяти
    return DataStore;
}
// 0. version 1.0 -> correct ? 1
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
void inv_C1Print(inv_C12* str)
{
	int i;
	printf("\n[\n");
	printf("\tC1: %c, ind: %d\n", str->C12, str->ind);
	printf("]\n");
}
// 1. Ф-ции сортировки методом вставки
// 1. version - 1.0 -> correct ? 1
void insSortC1(inv_C12* inv_C1Store, int N)
{
    int i = 0, loc = 0;
    inv_C12 NE;
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

// 3. version - 1.0 -> correct ? подлежит проверке и отладке

// ---
// 2. Единый справочник
// 1. version - 1.0 -> correct ? 1, все работает идеально.
Entry* createEntriesC1(inv_C12* inv_C1Store, int N, int blockCount, int blockSize)
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
    Entry* EntriesC1 = (Entry*)malloc(blockCount * sizeof(Entry));
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
			(EntriesC1 + i)->key = (inv_C1Store + i*sizes[i] + sizes[i] - 1)->C12;
            // адрес нулевой записи i-го блока 
			(EntriesC1 + i)->index = i*sizes[i];
        }
        else
        {
            // Для последнего блока:
			(EntriesC1 + i)->key = (inv_C1Store + i*sizes[i - 1] + sizes[i] - 1)->C12;
			(EntriesC1 + i)->index = i*sizes[i - 1];
        }
    }
    // Очистка памяти
    free(sizes);
    // возвращаю адрес младшего байта созданного справочника для переданного информационного массива. 
	return EntriesC1;
}
// 2. version - 1.0 -> correct ? подлежит проверке и отладке

// 3. version - 1.0 -> correct ? подлежит проверке и отладке

/* 
    3. Одноаспектный поиск по совпадению
    correct? ?
    Интерфейс ф-ции: информационный массив, его размер, единый справочник, количество блоков
    Будет 3 поиска по совпадению для каждого инверсного массива
*/ 
// 1. version - 1.0 -> correct ? 0, проблема в этой ф-ции
int* MatchSearchC1(inv_C12* inv_C1Store, int N, Entry* EntriesC1, int blockCount, char argC1, int* cfound1)
{
    int i, j, found = -1;
    // Создаю массив адресов найденных элементов в инверсном массиве для полей C12, размер которого изменяется от количества найденных элементов
    int* res = (int*)calloc(N, sizeof(int));
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
                        res[found] = inv_C1Store[j].ind;
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
                        res[found] = inv_C1Store[j].ind;
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
        *cfound1 = found+1;
        // В моем случае - возвращает тот же адрес, освобождает ячейки, находящиеся за пределами found+1.
        res = (int*)realloc(res, sizeof(int)*(found+1));
        return res;
    }
}
// 2. version - 1.0 -> correct ? подлежит проверке и отладке

// 3. version - 1.0 -> correct ? подлежит проверке и отладке

// 3. Инверсные массивы
// 1. version - 1.0 -> correct ? подлежит проверке и отладке

// 4. Пересечение результатов поиска
// 1. version - 1.0 -> correct ? подлежит проверке и отладке
int* Intersection(int* res1, int cfound1, int* res2, int cfound2, int* res3, int cfound3, int* ctfound)
{
	int i, j, k, found = -1;
	if (res1 != NULL && res2 != NULL && res3 != NULL)
	{
		int max = MAX3(cfound1, cfound2, cfound3);
		int* tres = (int*)malloc(max * sizeof(int));
		for (i = 0; i < cfound1; i++)
		{
			for (j = 0; j < cfound2; j++)
			{
				for (k = 0; k < cfound3; k++)
				{
					if (res1[i] == res2[j] && res2[j] == res3[k])
					{
						found += 1;
						tres[found] = ctfound[i];
					}
				}
			}
		}
		*ctfound = found + 1;
		return (int*)realloc(tres, sizeof(int)*(found + 1));
	}
	else
	{
		return NULL;
	}
}
void printEntries(Entry* EntriesCi, int blockCount, int num)
{
	int i;
	printf("\nEntriesC%d:\n", num);
	for (i = 0; i < blockCount; i++)
	{
		printf("Entry %d: last entry key value: %c, first entry index: %d\n", i, EntriesCi[i].key, EntriesCi[i].index);
	}
}
void printRes(Record* DataStore, int* resi, int cfoundi, int num)
{
	int i;
	printf("\n\nMatch search: %d \n\n", num);
	printf("cfound%d = %d\n", cfoundi, num);
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
int main()
{
    int i, j, N = 3, argB, cfound1 = 0, cfound2 = 0, cfound3 = 0, ctfound = -1, blockCount, blockSize;
	char isexit;
	char argC1, argC2;
	//do
	//{
		//printf("Enter the size of Origin Array:\n"); fflush(stdin);
		//scanf_s("%d", &N);
		// Размер блока - целая часть квадратного кореня из количетва записей
		blockSize = sqrt(N);
		// Количество блоков - округленное в большую сторону частное от количества элементов в информационном массиве на размер каждого блока. 
		blockCount = ceil((double)N / blockSize);

		// Генерируем информационный массив correct ? 1
		Record* DataStore = GenDataStore(N);
        // Создадим один инверсный массив и выведем его:

        inv_C12* inv_C1Store = (inv_C12*)malloc(N * sizeof(inv_C12));
		inv_C12* inv_C2Store = (inv_C12*)malloc(N * sizeof(inv_C12));


		// Выводим ифнформационный массив
		printf("Let's print Data Store:\n");
		for (i = 0; i < N; i++)
		{
        	structPrint(DataStore+i);
		}

		// Создаю первый инверсный массив в тестовом режиме: -> correct!
		for (i = 0; i < N; i++)
		{
			inv_C1Store[i].C12 = DataStore[i].C1;
			inv_C1Store[i].ind = i;

			inv_C2Store[i].C12 = DataStore[i].C2;
			inv_C2Store[i].ind = i;

		}

		// Сортирую инверсный массив: -> correct!
		insSortC1(inv_C1Store, N);
		insSortC1(inv_C2Store, N);

		// Вывод инверсного массива -> correct!
		printf("\ninv_C1Store:\n");
		for (i = 0; i < N; i++)
		{
        	inv_C1Print(inv_C1Store+i);
		}
		printf("\ninv_C2Store:\n");
		for (i = 0; i < N; i++)
		{
			inv_C1Print(inv_C2Store+i);
		}
		
		// Создание единого справочника для отсортированного инверсного массива
		Entry* EntriesC1 = createEntriesC1(inv_C1Store, N, blockCount, blockSize);
		Entry* EntriesC2 = createEntriesC1(inv_C2Store, N, blockCount, blockSize);

		// Вывожу Единый справочник для инверсного массива correct ? 1
		printEntries(EntriesC1, blockCount, 1);
		printEntries(EntriesC2, blockCount, 2);

		// Одноаспектный поиск символов в инверсном массиве: correct ? 1
		int* res1 = MatchSearchC1(inv_C1Store, N, EntriesC1, blockCount, 'G', &cfound1);
		int* res2 = MatchSearchC1(inv_C2Store, N, EntriesC2, blockCount, 'W', &cfound2);
		
		// Одноаспектный поиск целых чисел в массиве целых чисел

		// Вывожу результат одноаспектного поиска в инверсном массиве и значени по индексам из ифнормационного массива, все работает. correct ? 1

		printRes(DataStore, res1, cfound1, 1);
		printRes(DataStore, res2, cfound2, 2);

		// Выполним операцию пересесение над результатами одноаспектных поисков:

        // С символами все работаем, теперь массив целых
        int max1 = MAX2(cfound1, cfound2); 
        int* tres = (int*)malloc(max1 * sizeof(int));
		for (i = 0; i < cfound1; i++)
        {
            for (j = 0; j < cfound2; j++)
            {
                if (res1[i] == res2[j])
                {
                    ctfound+=1;
                    tres[ctfound] = res1[i];
                }
            }
        }

        int* tres1 = (int*)realloc(tres, ctfound+1);
        printRes(DataStore, tres1, ctfound+1, 3);

		//inv_C2* inv_C2Store = (inv_C2*)malloc(N * sizeof(inv_C2));
        //inv_B* inv_BStore = (inv_B*)malloc(N * sizeof(inv_B));
        // Создадим один инверсный массив и выведем его:
		
		// Очистка памяти
		free(res1); free(res2); //free(res3);
		free(EntriesC1); free(EntriesC2); //free(EntriesB);
		free(DataStore);
        free(inv_C1Store); free(inv_C2Store); //free(inv_BStore);
		free(tres1);
        //printf("is exit? [78 -> N, 89 -> Y]\n"); 
		//fflush(stdin);
		//scanf_s("%c", &isexit);
	//} while (isexit != 89);

}
