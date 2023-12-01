// Индексированный блоковый список (неравномерное индексирование блоков, размер блока 6, размер индексной таблицы 5)

#include <stdio.h>
#include <stdlib.h>
#define N 70       // Количество записей в исходном информационном массиве
#define ARRAYSIZE 5
#define BLOCKSIZE 6
#define INDEXTABLESIZE 5

struct Data
{
    char symbol1;
    int array[ARRAYSIZE];
    char symbol2;
};

struct BlockNode
{
    int elementCount;
    struct Data data[BLOCKSIZE];
    struct BlockNode *next;
    struct BlockNode *previous;
};

struct IndexRow
{
    int firstElemIndex;
    struct BlockNode *indexedNode;
};

struct BlockList
{
    struct BlockNode *begin;
    struct BlockNode *end;
    struct IndexRow indexTable[INDEXTABLESIZE];
    int blockCount;
};

struct Data createAdditionalNote()
{
    struct Data newData;
    printf("Enter first symbol: ");
    fflush(stdin);
    scanf("%c", &newData.symbol1);
    printf("Fill the array\n");
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        printf("Enter element [%d] of array: ", i);
        fflush(stdin);
        scanf("%d", &newData.array[i]);
    }
    printf("Enter second symbol: ");
    fflush(stdin);
    scanf("%c", &newData.symbol2);
    return newData;
}

// Добавление в пустой список
void addToEmpty(struct BlockList *list, struct Data newData)
{
    struct BlockNode *newNode = (struct BlockNode *)malloc(sizeof(struct BlockNode));
    newNode->previous = NULL;
    newNode->data[0] = newData;
    newNode->elementCount = 1;
    newNode->next = NULL;
    list->begin = newNode;
    list->end = newNode;
    list->blockCount = 1;
}

// Добавление новой записи в начало списка
void addToBeginning(struct BlockList *list, struct Data newData, int isFilled)
{
    if (list->begin->elementCount < BLOCKSIZE)
    {
        for (int i = list->begin->elementCount - 1; i >= 0; i--)
            list->begin->data[i + 1] = list->begin->data[i];
        list->begin->data[0] = newData;
        list->begin->elementCount++;
    }
    else
    {
        struct BlockNode *newNode = (struct BlockNode *)malloc(sizeof(struct BlockNode));
        newNode->data[0] = newData;
        newNode->elementCount = 1;
        newNode->next = list->begin;
        list->begin->previous = newNode;
        list->begin = newNode;
        list->blockCount++;
    }
    if (isFilled)
        for (int i = 0; i < INDEXTABLESIZE; i++)
            list->indexTable[i].firstElemIndex++;
}

// Добавление новой записи в конец списка
void addToEnd(struct BlockList *list, struct Data newData)
{
    if (list->end->elementCount < BLOCKSIZE)
    {
        list->end->data[list->end->elementCount] = newData;
        list->end->elementCount++;
    }
    else
    {
        struct BlockNode *tmp = (struct BlockNode *)malloc(sizeof(struct BlockNode));
        tmp->data[0] = newData;
        tmp->elementCount = 1;
        tmp->next = NULL;
        tmp->previous = list->end;
        list->end->next = tmp;
        list->end = tmp;
        list->blockCount++;
    }
}

// Вычисления кол-ва записей в информационном массиве
int listElemCount(struct BlockList *list)
{
    int elementCount = 0;
    struct BlockNode *tmp = tmp = list->begin;
    while (tmp != NULL)
    {
        elementCount += tmp->elementCount;
        tmp = tmp->next;
    }
    return elementCount;
}

// Поиск блока по индексной таблице
void findStartBlock(struct BlockList *list, struct BlockNode **curNode, int *indexInTable, int *isInIndexTable, int *indexInBlock, int index, int isFilled)
{
    int left = 0, right = 1, direction, elemCount = listElemCount(list), count = 0, tmpIndex;
    struct BlockNode *tmp;

    // Поиск нужного блока В ИНДЕКСНОЙ ТАБЛИЦЕ и выяснение направления движения
    if (isFilled)
    {
        for (int i = 0; i < INDEXTABLESIZE; i++)
        {
            if (list->indexTable[i].firstElemIndex >= index)
            {
                if (i == 0)
                {
                    if ((list->indexTable[i].firstElemIndex - index) <= list->indexTable[i].firstElemIndex / 2)
                    {
                        *curNode = list->indexTable[i].indexedNode;
                        tmpIndex = list->indexTable[i].firstElemIndex;
                        direction = left;
                    }
                    else
                    {
                        *curNode = list->begin;
                        tmpIndex = 0;
                        direction = right;
                    }
                    *indexInTable = i;
                }
                else
                {
                    if ((list->indexTable[i].firstElemIndex - index) <= (list->indexTable[i].firstElemIndex - list->indexTable[i - 1].firstElemIndex) / 2)
                    {
                        *curNode = list->indexTable[i].indexedNode;
                        tmpIndex = list->indexTable[i].firstElemIndex;
                        direction = left;
                    }
                    else
                    {
                        *curNode = list->indexTable[i - 1].indexedNode;
                        tmpIndex = list->indexTable[i - 1].firstElemIndex;
                        direction = right;
                    }
                    *indexInTable = i;
                }
                break;
            }
            else if (list->indexTable[i].firstElemIndex < index && i == INDEXTABLESIZE - 1)
            {
                if ((index - list->indexTable[i].firstElemIndex) <= (elemCount - list->indexTable[i].firstElemIndex) / 2)
                {
                    *curNode = list->indexTable[i].indexedNode;
                    tmpIndex = list->indexTable[i].firstElemIndex;
                    direction = right;
                }
                else
                {
                    *curNode = list->end;
                    tmpIndex = elemCount - 1;
                    direction = left;
                }
                *indexInTable = i;
            }
        }
    }
    else
    {
        if (index > elemCount / 2)
        {
            *curNode = list->end;
            tmpIndex = elemCount - list->end->elementCount;
            direction = left;
        }
        else
        {
            *curNode = list->begin;
            tmpIndex = 0;
            direction = right;
        }
    }

    // Поиск нужного блока
    tmp = *curNode;
    while (tmpIndex != index)
    {
        if (direction == right)
        {
            tmpIndex++;
            count++;
            if (count > tmp->elementCount - 1)
            {
                tmp = tmp->next;
                count = 0;
            }
        }
        else
        {
            if (count == 0)
                tmp = tmp->previous;

            tmpIndex--;
            count++;
            if (count > tmp->elementCount)
            {
                tmp = tmp->previous;
                count = 1;
            }
        }
    }
    *curNode = tmp;

    // Есть ли этот блок в индексной таблице
    *isInIndexTable = 0;
    for (int i = 0; i < INDEXTABLESIZE; i++)
    {
        if (*curNode == list->indexTable[i].indexedNode)
        {
            *isInIndexTable = 1;
            break;
        }
    }

    // Выяснение индекса элемента относительно блока, в котором он находится
    if (direction == right)
        *indexInBlock = count;
    else
    {
        if (*isInIndexTable)
            *indexInBlock = 0;
        else
        {
            if (count == 0)
                *indexInBlock = tmp->elementCount - count - 1;
            else
                *indexInBlock = tmp->elementCount - count;
        }
    }
}

// Вставка новой записи на заданную позицию
void addToPosition(struct BlockList *list, struct Data newData, int index, int isFilled)
{
    struct BlockNode *curNode, *tmp;
    int elementCount = listElemCount(list), indexInTable = 0, isInIndexTable = 1, indexInBlock;
    if (elementCount - 1 < index)
    {
        printf("Number of elements in list is %d. You cannot add an element with index greater than %d using this function.\nTo add the element with such index try 'addToEnd' function\n", elementCount, elementCount - 1);
        return;
    }

    // Поиск стартового блока и введенного индекса внутри этого блока
    findStartBlock(list, &curNode, &indexInTable, &isInIndexTable, &indexInBlock, index, isFilled);

    // Если есть место в текущем блоке, то добавляю запись в этот блок
    if (indexInBlock < curNode->elementCount && curNode->elementCount < BLOCKSIZE)
    {
        for (int i = curNode->elementCount - 1; i >= indexInBlock; i--)
            curNode->data[i + 1] = curNode->data[i];
        curNode->data[indexInBlock] = newData;
        curNode->elementCount++;
    }
    // Добавление новой записи на место в текущем блоке, если места нет
    else if (indexInBlock < curNode->elementCount)
    {
        // Если в следующем блоке есть место для записи
        if (curNode->next != NULL && curNode->next->elementCount < BLOCKSIZE)
        {
            for (int i = curNode->next->elementCount - 1; i >= 0; i--)
                curNode->next->data[i + 1] = curNode->next->data[i];

            curNode->next->data[0] = curNode->data[curNode->elementCount - 1];

            for (int i = curNode->elementCount - 2; i >= indexInBlock; i--)
                curNode->data[i + 1] = curNode->data[i];

            curNode->data[indexInBlock] = newData;
            curNode->next->elementCount++;
        }
        // Создание нового блока
        else
        {
            struct BlockNode *newNode = (struct BlockNode *)malloc(sizeof(struct BlockNode));

            newNode->data[0] = curNode->data[curNode->elementCount - 1];
            for (int i = curNode->elementCount - 2; i >= indexInBlock; i--)
                curNode->data[i + 1] = curNode->data[i];

            curNode->data[indexInBlock] = newData;
            newNode->elementCount = 1;

            // Создание связей между блоками
            if (curNode->next != NULL)
            {
                newNode->next = curNode->next;
                curNode->next->previous = newNode;
                newNode->previous = curNode;
                curNode->next = newNode;
            }
            else
            {
                newNode->next = NULL;
                newNode->previous = curNode;
                curNode->next = newNode;
                list->end = newNode;
            }
            list->blockCount++;
        }
    }

    // Обновление данных в индексной таблице
    if (isFilled)
    {
        if (index < list->indexTable[0].firstElemIndex)
            for (int i = INDEXTABLESIZE - 1; i >= indexInTable; i--)
                list->indexTable[i].firstElemIndex++;
        else if (index <= list->indexTable[INDEXTABLESIZE - 1].firstElemIndex)
            for (int i = INDEXTABLESIZE - 1; i > indexInTable; i--)
                list->indexTable[i].firstElemIndex++;
    }
}

// Изменение поля структуры в блоке для след ф-ии
void changeField(struct BlockNode *node, int index)
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
        scanf("%c", &node->data[index].symbol1);
        break;
    case 2:
        printf("Enter symbol: ");
        fflush(stdin);
        scanf("%c", &node->data[index].symbol2);
        break;
    case 3:
        for (int i = 0; i < ARRAYSIZE; i++)
        {
            printf("Enter element [%d] of array: ", i);
            fflush(stdin);
            scanf("%d", &node->data[index].array[i]);
        }
        break;
    case 4:
        break;
    default:
        printf("There is no such option. Operation canceled\n");
        break;
    }
}

// Изменение записи на заданной позиции
void changeNote(struct BlockList *list, int index, int isFilled)
{
    struct BlockNode *curNode, *tmp;
    int elementCount = listElemCount(list), indexInTable = 0, isInIndexTable = 1;
    if (elementCount - 1 < index)
    {
        printf("Number of elements in list is %d. You cannot change an element with index greater than %d\n", elementCount, elementCount - 1);
        return;
    }

    findStartBlock(list, &curNode, &indexInTable, &isInIndexTable, &index, index, isFilled);

    changeField(curNode, index);
}

// Очистка списка
void clearList(struct BlockList *list, int *isFilled)
{
    struct BlockNode *tmp = list->begin;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        free(list->begin);
        list->begin = tmp;
    }
    list->blockCount = 0;
    *isFilled = 0;
}

// Удаление элемента списка по индексу
void deleteByPosition(struct BlockList *list, int index, int isFilled)
{
    struct BlockNode *curNode, *tmp;
    int elementCount = listElemCount(list), indexInTable = 0, isInIndexTable = 1, indexInBlock;
    if (elementCount - 1 < index)
    {
        printf("Number of elements in list is %d. You cannot delete an element with index greater than %d\n", elementCount, elementCount - 1);
        return;
    }

    findStartBlock(list, &curNode, &indexInTable, &isInIndexTable, &indexInBlock, index, isFilled);

    // Удаление происходит благодаря сдвигу элементов, случай когда кол-во записей в блоке > 1
    if (indexInBlock < curNode->elementCount && curNode->elementCount > 1)
    {
        for (int i = indexInBlock; i < curNode->elementCount - 1; i++)
            curNode->data[i] = curNode->data[i + 1];
        curNode->elementCount--;
    }
    // Удаление, если число записей равно 1 (нужно удалить блок)
    else
    {
        if (list->blockCount == 1)
        {
            clearList(list, &isFilled);
        }
        else if (curNode->previous == NULL)
        {
            curNode->next->previous = curNode->previous;
            list->begin = curNode->next;
        }
        else if (curNode->next == NULL)
        {
            curNode->previous->next = curNode->next;
            list->end = curNode->previous;
        }
        else
        {
            curNode->previous->next = curNode->next;
            curNode->next->previous = curNode->previous;
        }

        if (isInIndexTable && isFilled)
        {
            if (curNode->next != list->indexTable[indexInTable + 1].indexedNode)
                list->indexTable[indexInTable].indexedNode = curNode->next;
            else if (indexInTable > 0 && curNode->previous != list->indexTable[indexInTable - 1].indexedNode)
                list->indexTable[indexInTable].indexedNode = curNode->previous;
            else
                for (int i = indexInTable; i < INDEXTABLESIZE - 1; i++)
                    list->indexTable[i] = list->indexTable[i + 1];
        }

        free(curNode);
        list->blockCount--;
    }

    // Обновление данных в индексной таблице
    if (isFilled)
    {
        if (index < list->indexTable[0].firstElemIndex)
            for (int i = INDEXTABLESIZE - 1; i >= indexInTable; i--)
                list->indexTable[i].firstElemIndex--;
        else if (index <= list->indexTable[INDEXTABLESIZE - 1].firstElemIndex)
            for (int i = INDEXTABLESIZE - 1; i > indexInTable; i--)
                list->indexTable[i].firstElemIndex--;
    }
}

void listSearch(struct BlockList *list, char searchArg)
{
    struct BlockNode *tmp;
    int found = 0;
    tmp = list->begin;
    while (tmp != NULL)
    {
        for (int i = 0; i < tmp->elementCount; i++)
        {
            if (searchArg == tmp->data[i].symbol1)
            {
                printf("%c [", tmp->data[i].symbol1);
                for (int j = 0; j < ARRAYSIZE; j++)
                {
                    if (j != ARRAYSIZE - 1)
                        printf("%d, ", tmp->data[i].array[j]);
                    else
                        printf("%d] ", tmp->data[i].array[j]);
                }
                printf("%c\n", tmp->data[i].symbol2);
                found = 1;
            }
        }
        tmp = tmp->next;
    }
    if (!found)
        printf("Element not found\n");
}

// Генерирование исходного списка
void listGenerate(struct BlockList *list)
{
    struct Data newData;
    for (int i = 0; i < N; i++)
    {
        newData.symbol1 = rand() % 26 + 65;
        for (int j = 0; j < ARRAYSIZE; j++)
            newData.array[j] = rand() % 100;
        newData.symbol2 = rand() % 26 + 65;
        if (i == 0)
            addToEmpty(list, newData);
        else
            addToEnd(list, newData);
    }
}

// Вывод всего списка
void printList(struct BlockList *list)
{
    struct BlockNode *tmp = list->begin;
    if (tmp == NULL)
        printf("List is empty\n");
    else
    {
        printf("BLOCK LIST\n");
        while (tmp != NULL)
        {
            for (int i = 0; i < tmp->elementCount; i++)
            {
                printf("%c [", tmp->data[i].symbol1);
                for (int j = 0; j < ARRAYSIZE; j++)
                {
                    if (j != ARRAYSIZE - 1)
                        printf("%d, ", tmp->data[i].array[j]);
                    else
                        printf("%d] ", tmp->data[i].array[j]);
                }
                printf("%c\n", tmp->data[i].symbol2);
            }
            tmp = tmp->next;
        }
    }
}

// Заполнение индексной таблицы
int fillIndexTable(struct BlockList *list, int *isFilled)
{
    // Шаг между индексированными блоками
    int stepInIndexing = list->blockCount / INDEXTABLESIZE, skippedBlockCount, index = 0;
    struct BlockNode *tmp;
    tmp = list->begin;
    if (!*isFilled && stepInIndexing > 1)
    {
        for (int i = 0; i < INDEXTABLESIZE; i++)
        {
            skippedBlockCount = stepInIndexing;
            while (tmp != NULL && skippedBlockCount != 0)
            {
                skippedBlockCount--;
                index += tmp->elementCount;
                tmp = tmp->next;
            }
            list->indexTable[i].firstElemIndex = index;
            list->indexTable[i].indexedNode = tmp;
        }
        return 1;
    }
    else
        return 0;
}

// Вывод индексной таблицы
void printIndexTable(struct BlockList *list, int isFilled)
{
    if (!isFilled)
        printf("The index table is not filled in\n");
    else
    {
        printf("INDEX TABLE\n"
               "Index\tAddress\n");
        for (int i = 0; i < INDEXTABLESIZE; i++)
        {
            printf("%d\t%p\n", list->indexTable[i].firstElemIndex, list->indexTable[i].indexedNode);
        }
    }
}

void menu(struct BlockList *list, int *isFilled)
{
    struct Data newData;
    int operation, index;
    char searchArg;
    do
    {
        printf("Choose operation with block list\n"
               "1 - Add an element to the beginning of the list\n"
               "2 - Add an element to the end of the list\n"
               "3 - Add an element to the position in the list\n"
               "4 - Delete an element at the position in the list\n"
               "5 - Change an element at the position in the list\n"
               "6 - Clear the list\n"
               "7 - Search in the list\n"
               "8 - Print the list\n"
               "9 - Print the service data\n"
               "10 - Exit\n");
        fflush(stdin);
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
            newData = createAdditionalNote();
            if (list->begin == NULL)
                addToEmpty(list, newData);
            else
                addToBeginning(list, newData, *isFilled);
            break;
        case 2:
            newData = createAdditionalNote();
            if (list->begin == NULL)
                addToEmpty(list, newData);
            else
                addToEnd(list, newData);
            break;
        case 3:
            newData = createAdditionalNote();
            printf("Enter the index by which you want to add the element: ");
            fflush(stdin);
            scanf("%d", &index);
            if (list->begin == NULL)
            {
                if (index >= 0)
                {
                    printf("There are no elements in the list. New element is added as the first element in the list\n");
                    addToEmpty(list, newData);
                }
            }
            else
                addToPosition(list, newData, index, *isFilled);
            break;
        case 4:
            printf("Enter the index by which you want to delete the element: ");
            fflush(stdin);
            scanf("%d", &index);
            deleteByPosition(list, index, *isFilled);
            break;
        case 5:
            printf("Enter the index by which you want to change the element: ");
            fflush(stdin);
            scanf("%d", &index);
            changeNote(list, index, *isFilled);
            break;
        case 6:
            clearList(list, isFilled);
            break;
        case 7:
            printf("Enter the symbol that will be searching for: ");
            fflush(stdin);
            scanf("%c", &searchArg);
            listSearch(list, searchArg);
            break;
        case 8:
            printList(list);
            break;
        case 9:
            printIndexTable(list, *isFilled);
            break;
        case 10:
            break;
        default:
            printf("There is no such operation\n");
            break;
        }
    } while (operation != 10);
}

int main()
{
    // Создание блокового списка
    struct BlockList *list = (struct BlockList *)malloc(sizeof(struct BlockList));
    int isFilled = 0;

    // Генерирование исходного информационного массива
    listGenerate(list);

    // Заполнение индексной таблицы
    isFilled = fillIndexTable(list, &isFilled);

    // Меню
    menu(list, &isFilled);

    // Освобождение всей выделенной памяти
    clearList(list, &isFilled);
    free(list);
    return 0;
}