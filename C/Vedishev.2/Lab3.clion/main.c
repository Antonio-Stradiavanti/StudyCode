#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define STR_LEN 1024

/*
Спецификация:
    - Создание структуры данных «с нуля» - вначале структура данных не содержит ни одного элемента;
	- Добавление данных из двоичного файла;
	- Выгрузку данных в двоичный файл;
	- Следующие операции над структурой данных:
	    1. Добавление элемента (если возможно: в начало, конец, произвольную заданную позицию).
	    2. Удаление элемента (если возможно: из начала, из конца, из произвольной заданной позиции).
	    3. Поиск элемента (если возможно).
	    4. Замена «старого» значения элемента на заданное новое (поиск по значению).
	    5. Установка значения элемента по заданному индексу (поиск по индексу).
	    6. Получение значения элемента по заданному индексу.
	    7. Удаление всех элементов.
	    8. Генерация структуры данных с заданным числом элементов.
	    9. Вывод на экран элементов структуры (для стеков, деков, очередей нужно использовать дополнительные временные «хранилища», а не реализовывать не присущие данным структурам функции).
	    10. Структура пуста/не пуста?
	    11. Передвинуть указатель структуры на n элементов вперед, назад (только для списков).
	- Выход из программы.
Задачи:
    - [x] Посмотреть видео про двоичные файлы
    - [x] Отладить ф-цию rmFromPos
    - [x] Реализовать процедуру выгрузки данных в двоичный файл
        - [x] Отладить ее
    - [x] Реализовать процедуру добавления произвольного количества данных по индексу из двоичного файла
        - [x] Отладить ее
    - [x] Узнать про позицию в файле
    - [ ] Перенести написанные ф-ции, сформировать отчет.
Статус:
    25 apr
        19-37 : написал ф-цию добавления элемента на любую позицию
        20-50 : написал вывод списка, проверку на пустоту
        21-24 : написал ф-ции замены элемента
    26 apr
        11-25 : Выполнил отладку ф-ции rmFromPos
    28 apr

*/

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
void DeclareDList(DList* List)
{
    List->size = 0;
    List->t = NULL;
    List->h = NULL;
}
// --- Основыные ф-ции работы со списком ---
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

    printf("\n--- [InitList]: The list has been successfully initialized ---\n");
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

    List->size = 0;

    printf("\n--- [DestroyList]: The list has been successfully destroyed and is now empty ---\n");
}
// Проверка списка на пустоту
int isEmpty(DList* List)
{
    if (List->t == NULL) return 1;
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
        printf("--- [InsToBg]: List now contains [ 1 ] node ---\n");
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
        printf("--- [InsToEnd]: List now contains [ 1 ] node ---\n");
        return;
    }
    // При использовании malloc всегда проверяй возвращаемое ф-цией значение
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    if (newNode == NULL)
    {
        printf("--- [InsToEnd]: malloc return NULL. Error => exiting ---\n");
        // Завершаю выполнение всей программы
        exit(1);
    }
    newNode->next = NULL;
    newNode->El = newData;

    newNode->prev = List->h;
    List->h->next = newNode;

    List->h = newNode;
    List->size++;
    printf("--- [InsToEnd]: Node successfully created and inserted. List now contains [ %d ] nodes ---\n", List->size);
}
// 3. На любую позицию
void insToPos(DList* List, Data newData, int p)
{
    int c = List->size-1;
    if (p <= 0)
    {
        printf("\n--- [InsToPos]: newData will be inserted in the beginning of the list ---\n");
        insToBg(List, newData);
    }
    else if (p >= c)
    {
        printf("\n--- [InsToPos]: newData will be inserted in the end of the list ---\n");
        insToEnd(List, newData);
    }
    else
    {
        DListNode *curNode, *newNode = (DListNode*)malloc(sizeof(DListNode));
        if (newNode == NULL)
        {
            printf("--- [InsToPos]: malloc return NULL. Error => exiting ---\n");
            exit(1);
        }
        // Для всех остальных случаев ситуации расписаны
        curNode = findNode(List, p);
        newNode->El = newData;

        newNode->prev = curNode->prev;
        curNode->prev->next = newNode;
        curNode->prev = newNode;
        newNode->next = curNode;

        List->size++;
        printf("--- [InsToPos]: Node successfully created and inserted in the [ %d ] position ---\n", p);
    }
}
// --- Удаление элемента по индексу ---
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
    FILE* f = fopen("/home/stradiavanti/Workspaces/C Programming/Vedishev.2/Lab3/streets.txt", "r");
    if (f == NULL)
    {
        printf("It's not possible to generate list, the streets file does not exist :(\n");
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
// Сформируем структуру полезных данных узла
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
// --- Вывод полезной информации узла в стандартный поток вывода ---
void PrintEl(Data El)
{
    printf("\n\t[\n\t\tC1_key: %c,\n\t\tCA: %s\n\t]", El.C1_key, El.CA);
}
// Печать элемента по заданному индексу
void PrintFromPos(DList* List, int p)
{
    DListNode* curNode = findNode(List, p);
    PrintEl(curNode->El);
}
// Печать списка
void PrintDList(DList* List)
{
    int i, eflag = isEmpty(List);
    if (eflag)
    {
        printf("\nList is empty :(\n"); return;
    }
    printf("--- DOUBLE LINKED LIST ---\nThe number of elements in the list: %d\n[\n", List->size);
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
// correct
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
// --- Поиск элемента ---
// Если список не пустой, то в нем можно искать
void findInList(DList *List, Data sArg)
{
    DListNode *tmpNode = List->t;
    int fflag = 0, i;
    while (tmpNode != NULL)
    {
        if (sArg.C1_key == tmpNode->El.C1_key && strcmp(sArg.CA, tmpNode->El.CA) == 0)
        {
            PrintEl(tmpNode->El);
            fflag = 1;
        }
        tmpNode = tmpNode->next;
    }
    if (!fflag) printf("Element not found :(\n");
}
// --- Запись и чтение поолезных данных узла из двоичного файла
int WriteData(char* FullFilename, DList* List)
{
    DListNode* curNode = List->t; int p = 0;
    if (curNode == NULL)
    {
        printf("--- [WriteData] Error: List is empty. ---\n");
        return 1;
    }
    // Открываю файл в режиме записи в двоичный файл
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
    // Закрываю открытый файл, очищаю динамическую память, выделенную для буфера
    if (fclose(f) == EOF) return 1;
    return 0;
}
int ReadSpecData(char* FullFilename, DList* List)
{
    FILE* f; int i, t = 0, pN = 0;
    Data* tmpData = (Data*)malloc(sizeof(Data));
    f = fopen(FullFilename, "rb");
    if (f == NULL)
    {
        printf("[ReadSpecData] Error: can't open the file.\n");
        return 1;
    }
    // Считываю общее количество узлов в файле
    if (fread(&t, sizeof(int), 1, f) != 1) return 1;
    printf("Enter the number of nodes from the file to insert into the list.\n");
    fflush(stdin);
    scanf("%d", &pN);
    if (pN > t)
    {
        printf("[ReadSpecData] Error: number of desired nodes [ %d ] >= [ %d ] number of nodes in the file.\n", pN, t);
        free(tmpData); return 1;
    }
    int* rpA = (int*) malloc(pN*sizeof(int));
    int* ipA = (int*) malloc(pN*sizeof(int));
    if (rpA == NULL || ipA == NULL)
    {
        printf("--- [menu->case12]: malloc return NULL. Error => exiting ---\n");
        free(rpA); free(ipA); free(tmpData);
        exit(1);
    }
    for (i = 0; i < pN; i++)
    {
        printf("Enter node [%d] index in file (NOTE: indexing starts from 0) : ", i);
        fflush(stdin);
        scanf("%d", rpA+i);
        printf("Enter node [%d] index in your List (NOTE: indexing starts from 0) : ", i);
        fflush(stdin);
        scanf("%d", ipA+i);
    }
    printf("Indexes:\n[ ");
    for (i = 0; i < pN; i++)
    {
        printf("%d ", rpA[i]);
    }
    printf("]\n");
    for (i = 0; i < pN; i++)
    {
        if (rpA[i] >= t)
        {
            printf("[ReadSpecData] Error: (current node index) rpA[i] -> [%d] >= [%d] t -> (nodes in file), exiting\n", rpA[i], t);
            free(rpA); free(ipA); free(tmpData);
            return 1;
        }
        else
        {
            fseek(f, sizeof(Data)*(rpA[i]) + sizeof(int), SEEK_SET);
        }
        if (fread(tmpData, sizeof(Data), 1, f) != 1)
        {
            printf("[ReadSpecData] Error reading from the file of the [ %d ] node\n", rpA[i]);
            free(rpA); free(ipA); free(tmpData);
            return 1;
        }
        insToPos(List, *tmpData, ipA[i]);
    }
    if (fclose(f) == EOF)
    {
        printf("Error closing file\n");
        free(tmpData); free(rpA); free(ipA);
        return 1;
    }
    free(rpA); free(ipA); free(tmpData);
    return 0;
}
void menu(DList* List)
{
    Data newData, sArg; char FullFilename[STR_LEN];
    int i, op, p = 0, N = 0, eflag = 0, pN = 0;
    printf("Choose operation with list\n"
           "1 -> Add an element to the list\n"
           "2 -> Remove an element from the list\n"
           "3 -> Searching for an item in the list\n"
           "4 -> Replacing the \"old\" element value with the specified new one (search by value)\n"
           "5 -> Setting the value of an element by a given index (index search)\n"
           "6 -> Getting the value of an element by a given index\n"
           "7 -> Destroy the list\n"
           "8 -> Generating the list\n"
           "9 -> Print the list\n"
           "10 -> Is the list empty?\n"
           "11 -> Upload data to a binary file\n"
           "12 -> Insert some data from the binary file\n");
    fflush(stdin);
    scanf("%d", &op);
    //printf("op : %d", op);
    switch (op)
    {
        case 1:
            printf("Enter index (NOTE: indexing starts from 0) : ");
            fflush(stdin);
            scanf("%d", &p);
            newData = GenNewData();
            insToPos(List, newData, p);
            break;
        case 2:
            printf("Enter index (NOTE: indexing starts from 0) : ");
            fflush(stdin);
            scanf("%d", &p);
            rmFromPos(List, p);
            break;
        case 3:
            printf("Let's create multi-aspect search argument\n");
            sArg = GenNewData();
            findInList(List, sArg);
            break;
        case 4:
            sArg = GenNewData();
            chEl1(List, sArg);
            break;
        case 5:
            printf("Enter index (NOTE: indexing starts from 0) : ");
            fflush(stdin);
            scanf("%d", &p);
            chEl2(List, p);
            break;
        case 6:
            printf("Enter index (NOTE: indexing starts from 0) : ");
            fflush(stdin);
            scanf("%d", &p);
            PrintFromPos(List, p);
            break;
        case 7:
            if (List->t != NULL)
            {
                DestroyList(List);
            }
            else
            {
                printf("List already has been destroyed.\n");
            }
            break;
        case 8:
            eflag = isEmpty(List);
            if (eflag)
            {
                printf("Enter the number of elements : ");
                fflush(stdin);
                scanf("%d", &N);
                GenList(List, N);
            }
            else
            {
                printf("This list has already been generated\n");
            }
            break;
        case 9:
            PrintDList(List);
            break;
        case 10:
            eflag = isEmpty(List);
            if (eflag)
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
            break;
        case 11:
            printf("Enter a file name : ");
            fflush(stdin);
            scanf(" %[^\n]%*c", FullFilename);
            WriteData(FullFilename, List);
            break;
        case 12:
            printf("Enter a file name : ");
            fflush(stdin);
            scanf(" %[^\n]%*c", FullFilename);
            ReadSpecData(FullFilename, List);
            break;
        default:
            printf("There is no such option.\n");
            break;
    }
}
int main()
{
    srand(time(NULL)); char isexit = 'N';
    DList* List = (DList*)malloc(sizeof(DList));
    DeclareDList(List);

    do {
        menu(List);
        printf("is exit? [Y/N] : ");
        fflush(stdin);
        scanf(" %c", &isexit);
    } while (isexit != 'Y');

    // Если список не пустой я его очищаю
    if (List->t != NULL)
        DestroyList(List);

    free(List);
    return 0;
}