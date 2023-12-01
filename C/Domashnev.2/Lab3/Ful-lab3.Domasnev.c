#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARR_SIZE 3
#define BLOCK_SIZE 7

/*
Спецификация
    Программа должна реализовывать следующие функции:
    1.	Добавление новой записи в начало списка V
    2.	Добавление новой записи в конец списка V
    3.	Вставка новой записи на заданную позицию VV
    4.	Удаление записи, находящейся на заданной позиции VV
    5.	Изменение записи, находящейся на заданной позиции VV
    6.	Очистка информационного массива V
    7.	Последовательный поиск записи в информационном массиве V
    8.	Вывод содержимого информационного массива на экран V
    9.	Вывод служебных данных и текущей структуры используемой структуры хранения V
Задачи:
    - [x] Посмотреть видео про списки
    - [ ] Отладить добавление нового узла
Статус:
    30 apr
        - 20-57 : Приступаю к отладке
	1 may
		- 11-43 : Отладил поиск блока
        - 12-20 : Отладил добавление по индексу
        - 12-33 : Отладил удаление по индексу
*/

// Объявим структуру данных информационного массива
typedef struct Data
{
    char C1_key;
    int A[ARR_SIZE];
    char C2;
} Data;

// Определим узел блокового списка
typedef struct BlockNode
{
    int elCnt;
    Data LocalDataStore[BLOCK_SIZE];
    // Указатель на предыдущий блок
    struct BlockNode* next;
    // Указатель на следующий блок
    struct BlockNode* prev;
} BlockNode;

// Определим блоковый список
typedef struct BlockList
{
    int size;
    BlockNode* t;
    BlockNode* h;
} BlockList;
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
void DeclareList(BlockList* List)
{
    List->size = 0;
    List->t = NULL;
    List->h = NULL;
}
// Приведение списка к состоянию инициализированного
void DestroyList(BlockList* List)
{
    BlockNode* tmpNode = List->t;
    while (tmpNode != NULL)
    {
        tmpNode = tmpNode->next;
        free(List->t);
        List->t = tmpNode;
    }

    List->t = NULL;
    List->h = NULL;
    List->size = 0;

    free(tmpNode);
    printf("[DestroyList]: List has been successfully destroyed.\n");
}
// Назначение: Возвращает адрес первого блока, для которого введенный индекс будет допустим.
BlockNode* findBlock(BlockList* List, int* p)
{
    if (*p >= List->size)
    {
        return NULL;
    }
    // Отладил
    BlockNode* curNode;
    if (*p > List->size / 2)
    {
        // Захожу в список с конца
		printf("[findBlock]: Start search at the end.\n");
        curNode = List->h;
        *p = List->size - 1 - *p;
		while (*p >= curNode->elCnt)
		{
			*p -= curNode->elCnt;
			curNode = curNode->prev;
		}
		*p = curNode->elCnt-1 - *p; 
        return curNode;
    }
    else
    {
        // Захожу в список с начала
		printf("[findBlock]: Start search from the begining.\n");
        curNode = List->t;
        while (*p >= curNode->elCnt)
        {
            *p -= curNode->elCnt;
            curNode = curNode->next;
        }
        return curNode;
    }
}
// correct 1
void InitList(BlockList* List, Data newData)
{
    BlockNode* newNode = (BlockNode*)malloc(sizeof(BlockNode));

    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->LocalDataStore[0] = newData;
    newNode->elCnt = 1;

    List->t = newNode;
    List->h = newNode;
    List->size = 1;

    printf("[InitList]: List was empty, list successfully initialized.\n");
}
// Добавление элемента в голову, в конец, на любую позицию.
void insToEnd(BlockList* List, Data newData)
{
    int i;
    if (List->t == NULL)
    {
        // Если список пустой, я его инициализирую
        InitList(List, newData);
        printf("[insToEnd]: List was empty, list successefully initialized.\n");
    }
    else if (List->t->elCnt < BLOCK_SIZE)
    {
        // Новый элемент помещаю в нулевую позицию блока
        for (i = List->t->elCnt - 1; i >= 0; i--)
        {
            List->t->LocalDataStore[i+1] = List->t->LocalDataStore[i];
        }
        List->t->LocalDataStore[0] = newData;
        List->t->elCnt++;
        List->size++;
    }
    else
    {
        BlockNode* newNode = (BlockNode*)malloc(sizeof(BlockNode));
        newNode->LocalDataStore[0] = newData;
        newNode->elCnt = 1;

        newNode->prev = NULL;
        List->t->prev = newNode;

        newNode->next = List->t;
        List->size++;

        List->t = newNode;
    }
}
void insToBg(BlockList* List, Data newData)
{
    if (List->h == NULL)
    {
        InitList(List, newData);
    }
    else if (List->h->elCnt < BLOCK_SIZE)
    {
        // Если в хвостовом блоке списка еще есть место => Добавляю по индексу, равному количеству добавленных элементов
        List->h->LocalDataStore[List->h->elCnt++] = newData;
        List->size++;
    }
    else
    {
        // Если в крайнем блоке нет свободного места
        BlockNode* newNode = (BlockNode*)malloc(sizeof(BlockNode));
        if (newNode == NULL)
        {
            printf("--- [insToPos]: malloc return NULL.\n");
            exit(1);
        }

        newNode->LocalDataStore[0] = newData;
        newNode->elCnt = 1;
        newNode->next = NULL;

        newNode->prev = List->h;
        List->h->next = newNode;
        // Теперь указатель на конец списка будет указывать на новый узел,
        // указатель на предыдущий узел старого хвоста сохраняется.
        List->h = newNode;
        List->size++;
    }
}
// Вставка это именно вставка, а не изменение или не замена элемента на заданной позиции
void insToPos(BlockList* List, Data newData, int* p)
{
    // Случай 1: индекс превышает число элементов в списке
    BlockNode *curNode;
    int i;
    if (*p >= List->size)
    {
        printf("Number of elements in List = [%d]\nDesired item position: [%d]\nPosition is >= List size\n=> newData will be inserted in the h of the List\n", List->size, p);
        insToBg(List, newData);
    }
    else if (p == 0)
    {
        printf("[insToPos]: Entered index (%d) == 0\nnewData will be inserted in the t of the List\n", p);
        insToEnd(List, newData);
    }
    else
    {
        // Поиск нужного индекса
        // Идем по блокам и вычитаем из индекса количество фактическое количество элементов в каждом блоке,
        // пока он не станет меньше количества элементов в рассматриваемом блоке
        curNode = findBlock(List, p);
        printf("curNode->next: %d.\n", curNode->next);
        if (curNode == NULL)
        {
            printf("[rmFromPos] Error: List index out of range, operation canceled.\n");
            return;
        }
        // Случай 1: в блоке есть свободная ячейка
        if (curNode->elCnt < BLOCK_SIZE)
        {
            // В таком случае сдвигаю на 1 вперед все элементы после точки вставки,
            // с элементом на этой позиции включительно

            // 22-09 -> Отладил
            for (i = curNode->elCnt; i >= *p; i--)
            {
                curNode->LocalDataStore[i] = curNode->LocalDataStore[i-1];
            }
            curNode->LocalDataStore[*p] = newData;
			printf("[insToPos]: newData successfully inserted in the block.\n");
        }
        else
        {
            // В противном случае создаем новый блок и переносим туда все элементы начиная с p
            BlockNode* newNode = (BlockNode*)malloc(sizeof(BlockNode));
            if (newNode == NULL)
            {
                printf("--- [insToPos]: malloc return NULL.\n");
                exit(1);
            }
			printf("[insToPos] case 2, index (p) = [%d]\nNew node created, I will try to insert newData.\n", *p);
			// Ошибка segmentation fault - попытка доступа к области памяти, к которой нет доступа

            newNode->elCnt = 0;
			printf("newNode elCnt = %d\n", newNode->elCnt);
            
            // Установил связи
            // Нужно рассмотреть случай когда curNode->next == NULL, тогда новый узел станет концом списка.
            if (curNode->next == NULL)
            {
                curNode->next = newNode;
                newNode->next = NULL;
                newNode->prev = curNode;
            }
            else
            {
                newNode->prev = curNode;
                newNode->next = curNode->next;
                curNode->next->prev = newNode;
                curNode->next = newNode;
            }
            
			int c = curNode->elCnt;
            // Переносим из блока curNode все элементы, начиная с p в новый блок X 
            printf("Loop.\n");
			for (i = *p; i < curNode->elCnt; i++)
            {
				// V
                newNode->LocalDataStore[++newNode->elCnt-1] = curNode->LocalDataStore[i]; c--;
            }
            // V
            curNode->elCnt = c;
			curNode->LocalDataStore[*p] = newData; curNode->elCnt++;
        }
        List->size++;
    }
}
void rmFromPos(BlockList* List, int* p)
{
    int i; BlockNode* curNode;
    // Удаляем один элемент в блоке
    // Если количество элементов в блоке > 1
    curNode = findBlock(List, p);
    if (curNode == NULL)
    {
        printf("[rmFromPos] Error: List index out of range, operation canceled.\n");
        return;
    }
    // если в списке один элемент, то вызываю DestroyList
    if (List->size == 1)
    {
        DestroyList(List);
    }
    else if (curNode->elCnt > 1)
    {
        for (i = *p; i < curNode->elCnt - 1; i++)
        {
            curNode->LocalDataStore[i] = curNode->LocalDataStore[i + 1];
        }
        curNode->elCnt--;
    }
    // Если в блоке один элемент -> удаляю целый блок
    else
    {
        if (curNode == List->t)
        {
            curNode->next->prev = NULL;
            List->t = curNode->next;
        }
        else if (curNode == List->h)
        {
            curNode->prev->next = NULL;
            List->h = curNode->prev;
        }
        else
        {
            curNode->prev->next = curNode->next;
            curNode->next->prev = curNode->prev;
        }
        curNode->elCnt--;
        free(curNode);
    }
    List->size--;
}
// Линейный мноаспектный поиск
// correct 1
void findInList(BlockList *List, Data sArg)
{
    BlockNode *tmpNode = List->t;
    int fflag = 0, i, j, eqC = 0;
    while (tmpNode != NULL)
    {
        for (i = 0; i < tmpNode->elCnt; i++)
        {
            if (sArg.C1_key == tmpNode->LocalDataStore[i].C1_key && sArg.C2 == tmpNode->LocalDataStore[i].C2)
            {
                for (j = 0; j < ARR_SIZE; j++)
                {
                    if (sArg.A[j] == tmpNode->LocalDataStore[i].A[j]) eqC++;
                }
                printf("eqC = %d\n", eqC);
                if (eqC == ARR_SIZE)
                {
                    PrintElem(tmpNode->LocalDataStore[i]);
                    printf("\n");
                }
                fflag = 1;
            }
        }
        tmpNode = tmpNode->next;
    }
    if (!fflag) printf("Element not found :(\n");
}
void changeField(BlockNode* curNode, int p)
{
    int option;
    printf("Which field do you want to change?\n"
           "1 - First symbol\n"
           "2 - Second symbol\n"
           "3 - Array\n"
           "4 - Cancel\n");
    fflush(stdin);
    scanf("%d", &option);
    switch (option)
    {
        case 1:
            printf("Enter symbol: ");
            fflush(stdin);
            scanf(" %c", &curNode->LocalDataStore[p].C1_key);
            break;
        case 2:
            printf("Enter symbol: ");
            fflush(stdin);
            scanf(" %c", &curNode->LocalDataStore[p].C2);
            break;
        case 3:
            for (int i = 0; i < ARR_SIZE; i++)
            {
                printf("Enter element [%d] of array: ", i);
                fflush(stdin);
                scanf("%d", &curNode->LocalDataStore[p].A[i]);
            }
            break;
        default:
            printf("There is no such option. Operation canceled\n-- __ |*_^| __ --\n");
            break;
    }
}
void changeElement(BlockList* List, int p)
{
    BlockNode* curNode;
    int elCnt = List->size;
    if (elCnt - 1 < p)
    {
        printf("Number of elements in list is %d. You cannot change an element with index greater than %d\n", elCnt, elCnt - 1);
        return;
    }
    curNode = findBlock(List, &p);
    if (curNode == NULL)
    {
        printf("[changeElement] Error: List List index out of range, operation canceled.\n");
    }
    changeField(curNode, p);
}
// --- Формирую список ---
void GenList(BlockList* List, int N)
{
    Data newData;
    if (List->t != NULL)
    {
        printf("[GenList]: This list has already been generated, canceling an operation.\n");
        return;
    }
    for (int i = 0; i < N; i++)
    {
        // Последовательно добавляю в хвост списка новые элементы
        newData.C1_key = rand() % 26 + 65;
        newData.C2 = rand() % 26 + 65;
        for (int j = 0; j < ARR_SIZE; j++)
            newData.A[j] = rand() % 1000;

        // Последовательно добавляю элементы в хвост списка
        insToBg(List, newData);
    }
    printf("[GenList]: List successfully has been generated.\n");
}
void PrintList(BlockList* List)
{
    int i, j, c = 0;
    BlockNode* tmpNode = List->t;
    // Выполняю проверку на то что список только объявлен, но не заполнен значениями
    if (tmpNode == NULL)
    {
        printf("\n[PrintList]: List is empty :(\n");
    }
    else
    {
        printf("\n--- BLOCK LIST ---\nThe number of elements in the block list: %d\n", List->size);
        while (tmpNode != NULL)
        {
            printf("\nBlock Node No%d (elements: %d):\n[", c, tmpNode->elCnt);
            for (i = 0; i < tmpNode->elCnt-1; i++)
            {
                PrintElem(tmpNode->LocalDataStore[i]); printf(",");
            }
            PrintElem(tmpNode->LocalDataStore[i]); printf("\n]\n");
            tmpNode = tmpNode->next; c++;
        }
        printf("\n--- THE END ---\n");
    }
}
Data GenNewData()
{
    Data newData;
    printf("Enter C1_key (1st character) : ");
    fflush(stdin);
    scanf(" %c", &newData.C1_key);
    printf("\nEnter C2 (2nd character) : ");
    fflush(stdin);
    scanf(" %c", &newData.C2);
    printf("\nLet's fill a mini-array:\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("[%d] el of array = ", i);
        fflush(stdin);
        scanf("%d", &newData.A[i]);
    }
    return newData;
}
void PrintFromPos(BlockList* List, int* p)
{
	int i;
    BlockNode* curNode = findBlock(List, p);
    // Нужно вывести определенный элемент
	PrintElem(curNode->LocalDataStore[*p]);
	printf("\n");
}
// Главная ф-ция
int main()
{
    srand(time(NULL)); char isexit = 'N'; int N = 0, p = 0;
    // Под список выделяем память в главной ф-ции, там же очищаем
    BlockList* List = (BlockList*)malloc(sizeof(BlockList));
    DeclareList(List);

	printf("Enter N : ");
	scanf("%d", &N);
    // Вызовем меню столько раз, сколько пользователь пожелает.
    GenList(List, N);
	PrintList(List);
	printf("Enter p (NOTE: indexing starts from 0) : ");
	fflush(stdin);
	scanf("%d", &p);
	Data newData;
	newData.C1_key = 'A'; newData.C2 = 'B';
	newData.A[0] = 777; newData.A[1] = 777; newData.A[2] = 777;
	// Соответственно, коль скоро я передаю по адресу, значит в меню каждый раз должно запрашиваться новое значение.
	int tmp = p;
	PrintFromPos(List, &p);
	rmFromPos(List, &tmp);
    //insToPos(List, newData, &tmp);
	PrintList(List);
    // Сбор мусора
    if (List->t != NULL)
        DestroyList(List); 
    free(List); 
    return 0;
}