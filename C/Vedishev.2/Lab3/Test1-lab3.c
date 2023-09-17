#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define STR_LEN 128

#define STR_LEN 128

typedef struct Data 
{
   char C1_key;
   char CA[STR_LEN]; 
} Data;

typedef struct DListNode
{
    Data El;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

typedef struct DList
{
    int size;
    DListNode* t;
    DListNode* h;
} DList;
// --- Основыные ф-ции работы со списком ---
void DeclareDList(DList* List)
{
    List->size = 0;
    List->t = NULL;
    List->h = NULL;
}
void InitList(DList* List, Data newData)
{
	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	
	newNode->prev = NULL;
	newNode->next = NULL;
	newNode->El = newData;

    // И голова и хвост - один и тот же элемент
	List->t = newNode;
	List->h = newNode;
	List->size = 1;

    printf("\n--- The list has been successfully initialized and is now contains one node ---\n");
}
void DestroyList(DList* List)
{
    DListNode* curNode = List->t;
    while (curNode->next != NULL)
    {
        curNode = curNode->next;
        free(curNode->prev);
    }
    free(curNode);

    List->t = NULL;
    List->h = NULL;

    printf("\n--- The list has been successfully destroyed and is now empty ---\n");
}
int isEmpty(DList* List)
{
    if (List->size == 0) return 1;
    return 0;
}
// --- Оптимальный поиск адреса узла списка ---
// correct
DListNode* findNode(DList* List, int p)
{
	DListNode* curNode; int c;
    if (p >= List->size || p < 0)
    {
        return NULL;
    }
    // В двусвязных списках есть всего 2 точки входа
	if (p >= List->size / 2)
	{
		curNode = List->h;
		c = List->size-1;
		while (c != p)
        {
            curNode = curNode->prev;
            c--;
        }
	}
	else
	{
		curNode = List->t;
		c = 0;
        while (c != p)
		{
			curNode = curNode->next;
            c++;
		}
	}
    return curNode;
}
//--- Добавление элементов ---
// correct
// 1. В хвост списка
void insToBg(DList* List, Data newData)
{
    if (List->t == NULL)
	{
		InitList(List, newData);
		printf("List was empty, list successefully initialized.\n");
        return;
	}
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    if (newNode == NULL)
    {
        printf("malloc return NULL. Error => exiting\n");
        // Завершаю выполнение всей программы
        exit(1);
    }
    newNode->El = newData;
    newNode->prev = NULL;

    newNode->next = List->t;
    List->t->prev = newNode;

    List->t = newNode;
    List->size++;
}
// 2. В голову списка
void insToEnd(DList* List, Data newData)
{
    // Список пустой => я его инициализирую
    if (List->h == NULL)
	{
		InitList(List, newData);
		printf("List was empty, list successefully initialized.\n");
        return;
	}
    // При использовании malloc всегда проверяй возвращаемое ф-цией значение
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    if (newNode == NULL)
    {
        printf("malloc return NULL. Error => exiting\n");
        // Завершаю выполнение всей программы
        exit(1);
    }
    newNode->next = NULL;
    newNode->El = newData;

    newNode->prev = List->h;
    List->h->next = newNode;

    List->h = newNode; 
    List->size++;
}
// 3. На любую позицию
void insToPos(DList* List, Data newData, int p)
{
    int c = List->size-1;
    if (p == 0)
    {
        printf("\n--- newData will be inserted in the t of the list ---\n");
        insToBg(List, newData);
    }
    else if (p >= c)
    {
        printf("\n--- newData will be inserted in the h of the list ---\n");
        insToEnd(List, newData);
    }
    else
    {
        DListNode *curNode, *newNode = (DListNode*)malloc(sizeof(DListNode));
        if (newNode == NULL)
        {
            printf("malloc return NULL. Error => exiting\n");
            // Завершаю выполнение всей программы
            exit(1);
        }
        curNode = findNode(List, p);
        if (curNode != NULL)
        {
            newNode->El = newData;

            newNode->prev = curNode->prev;
            curNode->prev->next = newNode;
            curNode->prev = newNode;
            newNode->next = curNode;

            List->size++;
            printf("--- New data succesefully incerted ---\n");
        }
        else
        {
            printf("Index = %d, List size = %d\n=>ERROR: List index out of range, operation canceled.\n", p, List->size);
            free(curNode);
        }
    }
}
// --- Удаление элемента по заданной позиции ---
// correct
void rmFromPos(DList* List, int p)
{
	int i; DListNode* curNode;
	// Если список пустой:
	if (List->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    // Если p указывает на голову
	if (p == 0)
	{
        // correct
        curNode = List->t;
        curNode->next->prev = NULL;
        List->t = curNode->next;
	}
    // Если p указывает на хвост
    // Если p > чем количество элементов в списке, удалить хвост
    else if (p >= List->size-1)
    {
        // correct
        curNode = List->h;
        curNode->prev->next = NULL;
        List->h = curNode->prev;
    }
	// Если p указывает ни на хвост, ни на голову
	else
	{
		curNode = findNode(List, p);
        if (curNode != NULL)
        {
            curNode->prev->next = curNode->next;
            curNode->next->prev = curNode->prev; 
        }
        else
        {
            printf("Index = %d, List size = %d\n=>ERROR: List index out of range, operation canceled.\n", p, List->size);
            return;
        }
	}
    free(curNode);
	List->size--;
}
// --- Формирую список ---
void GenList(DList* List, int N)
{
    FILE* f = fopen("streets.txt", "r");
    if (f == NULL)
    {
        printf("It's not possible to generate list, the streets file does not exist :(");
        return;
    }
    int c = 0, sC = 0, comma = 1, i;
    // Считаем количество улиц в файле
    while (!feof(f) && !ferror(f))
    {
        c = fgetc(f); // <- возвращает коды символов
        // Каждая из улиц в файле ограничена запятыми
        if (comma && !ispunct(c)) 
        {
            sC++; comma = 0;
        }
        else if (!comma && ispunct(c)) comma = 1;
    }
    fclose(f);
    // Количество улиц есть, теперь считаем их в массив:
    char** streets = (char**)malloc(sC*sizeof(char*));
    for (i = 0; i < sC; i++)
        streets[i] = (char*)malloc(STR_LEN*sizeof(char));
	f = fopen("streets.txt", "r");
    for (i = 0; i < sC; i++)
    {
        fscanf(f, "%[^,]", streets[i]);
        // Сдвигаю курсор на единичку от текущей позиции
        fseek(f, 1, SEEK_CUR);
    }
    fclose(f);
    // Сформируем случайным образом каждый из узлов списка
    Data newData;
	for (int i = 0; i < N; i++)
	{
		// Последовательно добавляю в хвост списка новые элементы
		newData.C1_key = rand() % 26 + 65;
		strcpy(newData.CA, streets[rand() % sC]);
		// Последовательно добавляю элементы в хвост списка
		insToEnd(List, newData);
	}
    // Сбор мусора
    for (i = 0; i < sC; i++)
    {
        free(streets[i]);
    }
    free(streets);
}
Data GenNewData()
{
	Data newData;
	printf("Enter C1_key (1st character) : ");
	fflush(stdin);
	scanf(" %c", &newData.C1_key);
	printf("\nEnter CA (sting) : ");
	fflush(stdin);
    // Считывай отдельные символы, пока не достигнешь пробельного символа переход на новую строку, * - один и больше символов. Пробел в начале нужен для того чтобы не считывался символ enter 
	scanf(" %[^\n]%*c", newData.CA);
	return newData;
}
// --- Вывод информации в стандартный поток вывода ---
void PrintEl(Data El)
{
	printf("\n\t[\n\t\tC1_key: %c,\n\t\tCA: %s\n\t]", El.C1_key, El.CA);
}
void PrintFromPos(DList* List, int p)
{
    DListNode* curNode = findNode(List, p);
    if (curNode != NULL) PrintEl(curNode->El);
    else printf("Index = %d, List size = %d\n=>ERROR: List index out of range, operation canceled.\n", p, List->size);
}
void PrintDList(DList* List)
{
    int i, eflag = isEmpty(List);
    if (eflag)
    {
        printf("\nList is empty :(\n"); return;
    }
    printf("--- DOUBLE LINKED LIST ---\nThe number of elements in the list: %d\n[", List->size);
    for (DListNode* curNode = List->t; curNode->next != NULL; curNode = curNode->next)
    {
        PrintEl(curNode->El); printf(",");
    }
    PrintEl(List->h->El);
    printf("\n]\n--- THE END ---\n");
}
// --- Замена элемента ---
// 1. Замена «старого» значения элемента на заданное новое
void chEl1(DList* List, Data sArg)
{
    printf("--- First let's find the right element ---\n");
    DListNode *tmpNode = List->t; Data newData;
    int fflag = 0, i;
    while (tmpNode != NULL)
    {
        if (sArg.C1_key == tmpNode->El.C1_key && strcmp(sArg.CA, tmpNode->El.CA) == 0)
        {
            fflag = 1;
            printf("The element is found! Let's enter new values\n");
            newData = GenNewData();
            tmpNode->El = newData;
            return;
        }
        tmpNode = tmpNode->next;
    }
    if (!fflag) printf("Element not found :(\n");

}
// 2. Установка значения элемента по заданному индексу
// соrrect
void chEl2(DList* List, int p)
{
    if (p > List->size-1)
    {
        printf("Number of elements in list is %d. You cannot change an element with index greater than %d\n", List->size, List->size-1);
        return;
    }
    DListNode* curNode = findNode(List, p);
    if (curNode != NULL)
    {
        Data newData = GenNewData();
        curNode->El = newData;
        printf("The element has been successfully changed.\n");
    }
    else printf("Index = %d, List size = %d\n=>ERROR: List index out of range, operation canceled.\n", p, List->size);  
}
// Что нужно выгружать в файл ? сам узел или только полезные данные ?
int WriteNode(char* FullFilename, DList* List)
{
    DListNode* curNode = List->t; int p = 0;
    if (curNode == NULL)
    {
        printf("--- [WriteData] Error: List is empty. ---\n");
        return 1;
    }
    // Открываю файл для записи
    FILE* f;
    f = fopen(FullFilename, "wb");
    if (f == NULL)
    {
        printf("--- [WriteData] Error: unable to create binary file. ---\n");
        return 1;
    }
    // Записываю в двоичный файл количество элементов в списке на данный момент
    int size = List->size;
    if (fwrite(&size, sizeof(int), 1, f) != 1)
    { 
        printf("--- [WriteData] Error writing size to binary file! ---\n");
        return 1;
    }
    for (curNode = List->t; curNode != NULL; curNode = curNode->next)
    {
        // Записываю в двоичный файл узлы
        if (fwrite(curNode, sizeof(DListNode), 1, f) != 1)
        {
            printf("--- [WriteData] Node [ %d ] writing error. ---\n", p);
            return 1;
        }
        p++;
    }
    if (fclose(f) == EOF) return 1;
    return 0;
}
int WriteData(char* FullFilename, DList* List)
{
    DListNode* curNode = List->t; int p = 0;
    if (curNode == NULL)
    {
        printf("--- [WriteData] Error: List is empty. ---\n");
        return 1;
    }
    // Открываю файл для записи
    FILE* f;
    f = fopen(FullFilename, "wb");
    if (f == NULL)
    {
        printf("--- [WriteData] Error: unable to create binary file. ---\n");
        return 1;
    }
    // Записываю в двоичный файл количество элементов в списке на данный момент
    int size = List->size;
    if (fwrite(&size, sizeof(int), 1, f) != 1)
    { 
        printf("--- [WriteData] Error writing size to binary file! ---\n");
        return 1;
    }
    for (curNode = List->t; curNode != NULL; curNode = curNode->next)
    {
        // Записываю в двоичный файл полезные данные
        if (fwrite(&curNode->El, sizeof(Data), 1, f) != 1)
        {
            printf("--- [WriteData] Node [ %d ] writing error. ---\n", p);
            return 1;
        }
        p++;
    }
    if (fclose(f) == EOF) return 1;
    return 0;
}
int ReadNode(char* FullFilename, DList* List)
{
    // - [ ] Записать ф-цию в общем виде для чтения всех файлов, а потом эксперементировать и читать только строго определенные.
    FILE* f; int t = List->size, p = 0;
    DListNode* tmpNode = (DListNode*)malloc(sizeof(DListNode));
    f = fopen(FullFilename, "rb");
    if (f == NULL) return 1;

    // Считаем количество элементов в списке:
    if (fread(&t, sizeof(int), 1, f) != 1) return 1;
    // Считываю каждый из узлов и добавляю их в список
    while (p < t)
    {
        if (fread(tmpNode, sizeof(DListNode), 1, f) != 1)
        {
            printf("Error reading from the file of the [ %d ] node\n", p);
            return 1;
        }
        insToEnd(List, tmpNode->El);
        p++;
    }
    if (fclose(f) == EOF) 
    {
        printf("Error closing file\n");
        free(tmpNode);
        return 1;
    }
    free(tmpNode); return 0;
}
int ReadData(char* FullFilename, DList* List)
{
    // - [ ] Записать ф-цию в общем виде для чтения всех файлов, а потом эксперементировать и читать только строго определенные.
    FILE* f; int t = List->size, p = 0;
    Data* tmpData = (Data*)malloc(sizeof(Data));
    f = fopen(FullFilename, "rb");
    if (f == NULL) return 1;

    // Считаем количество элементов в списке:
    if (fread(&t, sizeof(int), 1, f) != 1) return 1;
    // Считываю каждый из узлов и добавляю их в список
    while (p < t)
    {
        if (fread(tmpData, sizeof(Data), 1, f) != 1)
        {
            printf("Error reading from the file of the [ %d ] node\n", p);
            return 1;
        }
        insToEnd(List, *tmpData);
        p++;
    }
    if (fclose(f) == EOF) 
    {
        printf("Error closing file\n");
        free(tmpData);
        return 1;
    }
    free(tmpData); return 0;
}
// Будем читать и добавлять только строго определенное количество узлов, в ф-цию передаю массив идексов и их количество, каждый из них проверяю на допустимость
// Добавлять данные по их индексу в исходном списке из двоичного файла по определенному индексу в новый список
int ReadSpecData(char* FullFilename, DList* List, int rpN, int* rpA, int* ipA)
{
    FILE* f; int i, t = 0;
    Data* tmpData = (Data*)malloc(sizeof(Data));
    f = fopen(FullFilename, "rb");
    if (f == NULL) 
    {
        printf("[ReadSpecData] Error: can't open the file.\n"); 
        return 1;
    }
    //fseek(f, sizeof(int), SEEK_SET);
    // Считал, указатель передвинул
    if (fread(&t, sizeof(int), 1, f) != 1) return 1;
    if (rpN > t)
    {
        printf("[ReadSpecData] Error: number of desired nodes [ %d ] >= [ %d ] number of nodes in the file.\n", rpN, t);
        exit(1);
    }
    for (i = 0; i < rpN; i++)
    {
        if (rpA[i] >= t)
        {
            printf("[ReadSpecData] Error: (current node index) rpA[i] -> [%d] >= [%d] t -> (nodes in file), exiting\n", rpA[i], t);
            // Замени на return
            exit(1);
        }
        else
        {
            fseek(f, sizeof(Data)*(rpA[i]) + sizeof(int), SEEK_SET);
        }
        if (fread(tmpData, sizeof(Data), 1, f) != 1)
        {
            printf("[ReadSpecData] Error reading from the file of the [ %d ] node\n", rpA[i]);
            return 1;
        }
        insToPos(List, *tmpData, ipA[i]);
    }
    if (fclose(f) == EOF) 
    {
        printf("Error closing file\n");
        free(tmpData);
        return 1;
    }
    free(tmpData); return 0;
}
// *** *** *** *** ***
int main()
{
    char FullFilename[1024]; int i;
    int rpA[4], ipA[4], rpN = 0;
    //printf("sizeof(DList) = %llu, sizeof(Data) = %llu, sizeof(DlistNode) = %llu, sizeof(DListNode*) = %llu\n", sizeof(DList), sizeof(Data), sizeof(DListNode), sizeof(DListNode*));
    DList* List = (DList*)malloc(sizeof(DList));
    DeclareDList(List);
    GenList(List, 4);
    PrintDList(List);

    //printf("Enter a file name : ");
    //fflush(stdin);
    //scanf("%s", FullFilename);
    
    // Чтение из файла всех элементов и добавление их в список работает.
    WriteData("b.bin", List);
    if (List->t != NULL)
        DestroyList(List);
    //ReadData("b.bin", List);
    printf("Enter the number of nodes from the file to insert into the list.\n");
    scanf("%d", &rpN);
    for (i = 0 ; i < rpN; i++)
    {
        printf("Enter node [%d] index in file (NOTE: indexing starts from 0) : ", i);
        scanf("%d", rpA+i);
        printf("Enter node [%d] index in your List (NOTE: indexing starts from 0) : ", i);
        fflush(stdin);
        scanf("%d", ipA+i);
    }
    printf("Indexes:\n");
    for (i = 0; i < rpN; i++)
    {
        printf("%d ", rpA[i]);
    }
    ReadSpecData("b.bin", List, rpN, rpA, ipA);
    PrintDList(List);
    free(List); 
    return 0;
}