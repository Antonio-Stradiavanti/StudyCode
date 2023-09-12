//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include<locale.h>
#define STD_LEN 10
#define A_SIZE 3
#define MAXIMUM_FILE_NAME 1024
#define FILE_FORMAT "[ B : %d, A : %d %d %d, C : %s ]\n"
#define max(a, b) ((a > b) ? a : b)
/* Задание

    1. Заполнение информационного массива пользователем с клавиатуры
    2. Заполнение  информационного массива из файла
    3. Добавление записи в дерево
    4. Удаление выбранной записи из дерева
    5. Редактирование выбранной записи в дереве
    6. Поиск по совпадению в дереве
    7. Вывод текущей структуры дерева
*/
typedef struct
{
    int A[A_SIZE], B;
    char C[MAXIMUM_FILE_NAME + 1];
} Data;
typedef struct TreeNode
{ 
	Data* D;
    int H;
	struct TreeNode* L;
	struct TreeNode* R;
} TreeNode;
typedef struct
{
    int size;
	TreeNode* root;
} Tree;
int height(TreeNode* N)
{
    if (!N) return 0;
    return N->H;
}
void InitAvl(Tree* tree)
{
	tree->root = NULL; tree->size = 0;
    printf("[InitAvl->rs] : Дерево успешно инициализировано.\n");
}
/* Вставка узла в дерево */
TreeNode* getNewNode(Tree* tree, int* tmpA, int tmpB, char* tmpC)
{
    TreeNode* newNode;
    if ((newNode = (TreeNode*)malloc(sizeof(TreeNode))) == NULL)
    {
        printf("[insToBinTreeLeft->re1] : Ошибка выделения памяти.\n"); return NULL;
    }
    if ((newNode->D = (Data*) malloc(sizeof(Data))) == NULL)
    {
        printf("[insToBinTreeLeft->re2] : Ошибка выделения памяти.\n"); return NULL;
    }
    newNode->H = 1;

    newNode->D->B = tmpB; int i;
    for (i = 0; i < A_SIZE; i++)
        newNode->D->A[i] = tmpA[i];
    strcpy(newNode->D->C, tmpC);

    newNode->L = newNode->R = NULL;
    tree->size++; return (newNode);
}
void structCpy(TreeNode* curNode, TreeNode* tmpNode)
{
    curNode->L = tmpNode->L;
    curNode->R = tmpNode->R;
    curNode->D->B = tmpNode->D->B;
    strcpy(curNode->D->C, tmpNode->D->C);
    for (int i = 0; i < A_SIZE; i++)
        curNode->D->A[i] = tmpNode->D->A[i];
    curNode->H = tmpNode->H;
}
int getBF(TreeNode* curNode)
{
    if (!curNode) return 0;
    return height(curNode->L) - height(curNode->R);
}
// Применяется в случае когда дерево дисбалансировано влево.
TreeNode* rotR(TreeNode* z)
{
	
	TreeNode *y = z->L, *T3 = y->R;

    y->R = z; z->L = T3;

    z->H = max(height(z->L), height(z->R)) + 1;
    y->H = max(height(y->L), height(y->R)) + 1;

    return y;
}
// Применяется в случае когда дерево дисбалансировано вправо
TreeNode* rotL(TreeNode* z)
{
	TreeNode *y = z->R, *T2 = y->L;
	
    y->L = z; z->R = T2;

    z->H = max(height(z->L), height(z->R)) + 1;
    y->H = max(height(y->L), height(y->R)) + 1;

    return y;
}

/* Двойной Лево-правый и двойной право-левый повороты реализованы через 2 ф-ции выше, в первом случае выполняется сначала rotL, потом rotR, для право-левого все в точности наоборот. */
TreeNode* insToAvlTree(Tree* tree, TreeNode* curNode, int* tmpA, int tmpB, char* tmpC)
{
    // curNode -> предок.
    // Когда дошли до нуля, выполняем вставку.
    if (curNode == NULL) return (getNewNode(tree, tmpA, tmpB, tmpC));
    // Вместо двойного указателя возвращаем указатель.
    // Идем влево, вправо, проверяем на дубликат.
    if (tmpB < curNode->D->B)
        curNode->L = insToAvlTree(tree, curNode->L, tmpA, tmpB, tmpC);
    else if (tmpB > curNode->D->B)
        curNode->R = insToAvlTree(tree, curNode->R, tmpA, tmpB, tmpC);
    else return curNode;

    curNode->H = max(height(curNode->L), height(curNode->R)) + 1;
    int BF = getBF(curNode);
    // LL
    
    if (BF > 1 && tmpB < curNode->L->D->B)
        return rotR(curNode);
    /*
        LR
       (+2) z
           / \
     (-1) y  75
         /  \
        15   x (+1)
            /
        newNode
    */
    
    if (BF > 1 && tmpB > curNode->L->D->B)
    {
        curNode->L = rotL(curNode->L);
        return rotR(curNode);
    }
    // RR
    if (BF < -1 && tmpB > curNode->R->D->B)
        return rotL(curNode);
    /*   
        RL
       (-2) z
           / \
     (0) 22  y (+1)
            /  \
        (-1) x  80
              \
             newNode
    */ 
    if (BF < -1 && tmpB < curNode->R->D->B)
    {
        curNode->R = rotR(curNode->R);
        return rotL(curNode);
    }   
    return curNode;    
}
/* Удаление узла */
TreeNode* minValueNode(TreeNode* stNode)
{
	TreeNode* curNode = stNode;
	while (curNode->L)
		curNode = curNode->L;
	return curNode;
}
TreeNode* remFromAvlTree(Tree* tree, TreeNode* curNode, int tmpB)
{
    // ШАГ 1 : удаление узла из двоичного дерева поиска.
    if (curNode == NULL) return curNode;
    if (tmpB < curNode->D->B)
        curNode->L = remFromAvlTree(tree, curNode->L, tmpB);
    else if (tmpB > curNode->D->B)
        curNode->R = remFromAvlTree(tree, curNode->R, tmpB);
    else
    {
        TreeNode* tmpNode;
        // Случай 1 : у удаляемого узла <= 1 потомка.
        if (!curNode->L || !curNode->R)
        {
            tmpNode = curNode->L ? curNode->L : curNode->R;
            if (tmpNode == NULL)
            {
                // У текущего узла гарантированно нет потомков.
                tmpNode = curNode;
                curNode = NULL;
            }
            // Копируем значения из одной структуры в другую. 
            else structCpy(curNode, tmpNode);
            tree->size--; free(tmpNode->D); free(tmpNode);
        }
        // Сведем удаление узла с 2мя потомками к удалению листового узла или к удалению узла с одним потомком.
        else
        {
            // Находим узел с наименьшим значением в правом поддереве удаляемого узла (successor).
            tmpNode = minValueNode(curNode->R);
            // Обмен данными
            curNode->D->B = tmpNode->D->B;
            for (int i = 0; i < A_SIZE; i++)
                curNode->D->A[i] = tmpNode->D->A[i];
            strcpy(curNode->D->C, tmpNode->D->C);

            curNode->R = remFromAvlTree(tree, curNode->R, tmpNode->D->B);
        }
    }
    // ШАГ 2 : Выполним перебалансировку АВЛ дерева.
    // Если текущий узел - 0, выполним шаг назад, к его предку. 
    if (curNode == NULL) return curNode;

    curNode->H = max(height(curNode->L), height(curNode->R)) + 1;
    int BF = getBF(curNode);

    // LL
    if (BF > 1 && getBF(curNode->L) >= 0)
        return rotR(curNode);
    // LR
    if (BF > 1 && getBF(curNode->L) < 0)
    {
        curNode->L = rotL(curNode->L);
        return rotR(curNode);
    }
    // RR
    if (BF < -1 && getBF(curNode->R) <= 0)
        return rotL(curNode);
    if (BF < -1 && getBF(curNode->R) > 0)
    {
        curNode->R = rotR(curNode->R);
        return rotL(curNode);
    }
    return curNode;
} 
/* Поиск в дереве */
int lookupInAvlTree(Tree* tree, TreeNode* curNode, TreeNode** tmpNode, int tmpB)
{
	int retval;
	// Выход из рекурсии.
	if (curNode == NULL)
		return -1;
	if (tmpB < curNode->D->B)
		retval = lookupInAvlTree(tree, curNode->L, tmpNode, tmpB);
	else if (tmpB > curNode->D->B)
		retval = lookupInAvlTree(tree, curNode->R, tmpNode, tmpB);
	// Нашел:
	else
	{
        retval = 0;
        (*tmpNode) = curNode;
	}
	return retval;
}
void printDataStructure(TreeNode* curNode)
{
    int i;
    printf("\n[\n\tКлюч. поле B: %d\n\tМассив A: [ ", curNode->D->B);
    for (i = 0 ; i < A_SIZE-1; i++)
        printf("%d, ", curNode->D->A[i]);
    printf("%d ],\n\tСтрока C: %s\n]\n", curNode->D->A[i], curNode->D->C);
}
void LookupInAVL(Tree* tree)
{
    int tmpB;
    printf("Введите ключевые данные искомого узла (поиск осуществляется по элементу структуры данных B).\n> ");
    scanf("%d", &tmpB);
	TreeNode* tmp = NULL;
	lookupInAvlTree(tree, tree->root, &tmp, tmpB);
    if (tmp)
    {
        printf("[LookupInAVL->rs] : Искомый узел найден в АВЛ дереве, его данные:\n");
        printDataStructure(tmp);
    }
    else printf("[LookupInAVL->rf] : Искомый узел не найден в АВЛ дереве.\n");
}
void EditAvlNode(Tree* tree, int oldB)
{
	TreeNode* tmp = NULL;
	lookupInAvlTree(tree, tree->root, &tmp, oldB);
	if (tmp)
    {
        int i, newA[A_SIZE], newB; char newC[MAXIMUM_FILE_NAME + 1];
        printf("[EditAvlNode->pI1] : Введите новое значение ключ. поля\n> "); scanf("%d", &newB);
        printf("[EditAvlNode->pI2] : Введите новые значения поля массив:\n");
        for (i = 0; i < A_SIZE; i++)
        {
            printf("> Введите %d значение массива : ", i+1);
            scanf("%d", newA+i);
        }
        printf("[EditAvlNode->pI3] : Введите новое значение поля строка\n> ");
        scanf(" %[^\n]%1024c", newC);
        tmp->D->B = newB;
        strcpy(tmp->D->C, newC);
        for (i = 0; i < A_SIZE; i++)
            tmp->D->A[i] = newA[i];
    }
    else printf("[EditAvlNode->rf] : Нельзя изменить значение узла, узел с ключевым полем %d не существует.\n", oldB);
}
/* Очистка дерева */
void destrLeft(Tree* tree, TreeNode* curNode);
void destrRight(Tree* tree, TreeNode* curNode);
void destrLeft(Tree* tree, TreeNode* curNode)
{
	// curNode -> предок
    TreeNode** pos;
	// Зачем нам чтобы хранить указатель безопасно.
	if(!tree->size) return;
	if (!curNode) pos = &tree->root;
	else pos = &curNode->L;
	if (*pos != NULL)
	{
		destrLeft(tree, *pos);
		destrRight(tree, *pos);
        free((*pos)->D); free(*pos);
		// Тут тоже фактически изменяю значение указателя, а не объекта, на который он указывает.
		*pos = NULL;
		tree->size--;
	}
}
void destrRight(Tree* tree, TreeNode* curNode)
{
	TreeNode** pos;
	if(!tree->size) return;
	if (!curNode) pos = &tree->root;
	else pos = &curNode->R;
	if (*pos != NULL)
	{
		// Выполняем очистку левого поддерева
		destrLeft(tree, *pos);
		// Выполняем очистку правого поддерева
		destrRight(tree, *pos);
		free((*pos)->D); free(*pos);
		*pos = NULL;
		tree->size--;
	}
}
void DestroyAvl(Tree* tree)
{
	if (tree->root == NULL)
    {
        printf("[DestroyAvl->rc] : Дерево пустое.\n");
        return;
    }
	// Поехали.
    destrLeft(tree, NULL);
    tree->root = NULL; tree->size = 0;
	printf("[DestroyAvl->rs] : Дерево успешно очищено.\n");
}
/* Вывод дерева */
void printData(TreeNode* curNode, int L)
{
	if (curNode == NULL)
	{
		//printf("[printData] : curNode is NULL.\n");
		return;
	}
	for (int i = 0; i < L; i++)
		printf("  ");
	printf("%d: (%d) ", curNode->D->B, getBF(curNode));
	// Однозначного метода для определения есть ли у узла-родителя потомки нет, нужно рассмотреть все случаи
	if (curNode->L != NULL && curNode->R != NULL)
		printf("[%d, %d]\n", curNode->L->D->B, curNode->R->D->B);
	else if (curNode->L == NULL && curNode->R != NULL)
		printf("[%d]\n", curNode->R->D->B);
	else if (curNode->L != NULL && curNode->R == NULL)
		printf("[%d]\n", curNode->L->D->B);
	else 
		printf("[-]\n");
	// Выводим дочерние узлы данного узла.
	// Прямой обход, сначала вниз, потом к братьям.
	printData(curNode->L, L + 1);
	printData(curNode->R, L + 1);
}
void PrintAvl(Tree* tree)
{
	if (tree == NULL || tree->root == NULL || tree->size == 0)
	{
		printf("[PrintAvl->rc] : Дерево пустое.\n");
		return;
	}
	printf("\n\t/*=-*-=* Вывод АВЛ дерева *=-*-=*\\\n\n[PrintAvl->pI] : Количество узлов в дереве : %d.\n[Обозначения] : Ключевое поле узла (B) : (Его коэффициент баланса) [Левый потомок, правый потомок]\n\n", tree->size);
	printData(tree->root, 0);
    printf("\n\t\\*=-*-=* Конец АВЛ дерева *=-*-=*/\n\n");
}
/* Сформируем дерево */
/* 7. Сформировать дерево */
void genRandStr(char* tmpC, int len)
{
    char rCh[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
    int i, chL = strlen(rCh);
    for (i = 0; i < len; i++)
    {
        tmpC[i] = rCh[rand() % chL];
    }
    tmpC[i] = 0;
}
void MakeAvl(Tree* tree, int nC, int M, int mode)
{
	if (tree->root)
	{
		printf("[MakeAvl->rc1] : Дерево уже сформировано.\n"); return;
	}
	int i = 0, j = 0; M++; TreeNode* tmpNode = NULL;

    // Временное хранилище
    int tmpA[A_SIZE], tmpB; char tmpC[MAXIMUM_FILE_NAME + 1] = "";

	if (mode == 1)
	{
        // Из файла
		char fN[MAXIMUM_FILE_NAME + 1]; FILE* f; 
		printf("[MakeAvl->mod1->pI1] : Введите имя файла.\n[Примечание] : не забудьте указать его расширение : ");
		scanf(" %[^\n]%1024c", fN); printf("[MakeAvl->mod1->pI1] : Введенное имя файла : %s\n", fN); 
		if ((f = fopen(fN, "r")) == NULL)
		{
			printf("[MakeAvl->mod1->re1] : Не удалось открыть файл.\n"); return;
		}
		for (i = 0; i < nC; i++)
		{
			if (feof(f))
			{
				printf("[MakeAvl->mod1->pI2] : Из файла считано %d элементов.\n"); break;
			}
			if (ferror(f))
			{
				perror("[MakeAvl->mod1->re1] : "); clearerr(f);
                break;
			}
			fscanf(f, FILE_FORMAT, &tmpB, tmpA, tmpA+1, tmpA+2, tmpC);
			//printf("tmp bef = %d\n", tmp);
			// Он просто не добавляет дубликаты?
			tmpB %= M;
			while (!lookupInAvlTree(tree, tree->root, &tmpNode, tmpB))
				tmpB = rand() % M;
			//printf("tmp aft = %d\n", tmp);
			//printf("Есть ли 880 ? %d\n", lookupInAvlTree(tree, tree->root, &tmpNode, 880));
			tree->root = insToAvlTree(tree, tree->root, tmpA, tmpB, tmpC);
            strcpy(tmpC, "");
		}
		if (fclose(f) == EOF)
		{
			printf("[MakeAvl->mod1->re2] : Ошибка : Не удалось закрыть файл а следовательно и записать данные из буфера в файл и очистить память в куче, выделенную под буфер.\n"); return;
		}
	}
	else if (mode == 2)
	{
		// Случайным образом
		L:
		for (i = 0; i < nC; i++)
		{
			// У ключевого узла должно быть уникальное значение
            tmpB = rand() % M;
			while (!lookupInAvlTree(tree, tree->root, &tmpNode, tmpB))
				tmpB = rand() % M;
			// Срока и массив целых могут быть любыми
            for (j = 0; j < A_SIZE; j++)
                tmpA[j] = rand() % M;
            // Сгенерируем случайную строку.
            genRandStr(tmpC, STD_LEN);
            tree->root = insToAvlTree(tree, tree->root, tmpA, tmpB, tmpC);
            strcpy(tmpC, "");
		}
	}
	else if (mode == 3)
	{
		// Вручную
		if (nC > 50)
		{
			char W = 'N';
			printf("[MakeAvl->mod3->pN1] : Переданное количество узлов превышает 50, ввод такого количества чисел вручную может занять много времени, желаете выбрать автоматический режим формирования дерева? [Y/N].\n");
			scanf(" %c", &W);
			if (W == 'Y')
				goto L;
		}
		printf("[MakeAvl->mod3->pI2] : Введите %d значений узлов дерева с клавиатуры.\n", nC);
		for (i = 0; i < nC; i++)
		{
			printf(">> Введите значения полей %d узла. <<\n", i);
			printf("> Введите значение ключ. поля : "); scanf("%d", &tmpB);
			while (!lookupInAvlTree(tree, tree->root, &tmpNode, tmpB))
			{
				printf("> Такое значение ключ. поля уже есть, введите другое : "); scanf("%d", &tmpB);
			}
            printf("* Введите значения поля массив. *\n");
            for (j = 0; j < A_SIZE; j++)
            {
                printf("\t> Введите %d значение массива : ", j+1); scanf("%d", tmpA + j);
            }
            printf("> Введите значение поля строка : "); scanf(" %[^\n]%1024c", tmpC);
			tree->root = insToAvlTree(tree, tree->root, tmpA, tmpB, tmpC);
            strcpy(tmpC, "");
		}
	}
    else
    {
        printf("[MakeAvl->def->rc] : Нет такого режима.\n"); return;
    }
	printf("[MakeAvl->pI3] : Всего добавлено : %d , Желаемое количество узлов : nC = %d\n", tree->size, nC);
	printf("[MakeAvl->rs] : Успех : Дерево успешно сформированно.\n");
}
void MakeFile(int nC, int M)
{
	char fN[MAXIMUM_FILE_NAME + 1]; FILE* f; M++;// N -> количество чисел, записываемых в файл, максимально возможное число
	printf("[MakeFilr->pI1] : Введите имя файла.\n> [Примечание] : не забудьте указать его расширение : ");
	scanf(" %[^\n]%1024c", fN);
    if ((f = fopen(fN, "w")) == NULL)
	{
		printf("[genFile->re1] : Не удалось открыть файл.\n"); return;
	}
    char tmpC[MAXIMUM_FILE_NAME + 1];
	for (int i = 0; i < nC; i++)
    {
        genRandStr(tmpC, STD_LEN);
		fprintf(f, FILE_FORMAT, rand() % M, rand() % M, rand() %M, rand() %M, tmpC);
        strcpy(tmpC, "");
    }
	if (fclose(f) == EOF)
	{
		printf("[genFile->re2] : Не удалось закрыть файл а следовательно и записать данные из буфера в файл и очистить память в куче, выделенную под буфер.\n"); return;
	}
}
void InsertToAvl(Tree* tree)
{
    int i, j, nC = 0;
    printf("[InsertToAvl->pI1] : Сколько желаете добавить узлов?\n> ");
    scanf("%d", &nC);
    if (nC)
    {
        Data* DS;
        if ((DS = (Data*)malloc(nC * sizeof(Data))) == NULL)
            return;
        TreeNode* tmpNode;
        for (i = 0; i < nC; i++)
        {
            printf(">> Введите значения полей %d добавляемого узла. <<\n", i+1);
            printf("> Введите значение ключ. поля : "); scanf("%d", &DS[i].B);
            while (!lookupInAvlTree(tree, tree->root, &tmpNode, DS[i].B))
            {
                printf("> Такое значение ключ. поля уже есть, введите другое : "); scanf("%d", &DS[i].B);
            }
            printf("* Введите значения поля массив. *\n");
            for (j = 0; j < A_SIZE; j++)
            {
                printf("\t> Введите %d значение массива : ", j+1); scanf("%d", &DS[i].A[j]);
            }
            printf("> Введите значение поля строка : "); scanf(" %[^\n]%1024c", DS[i].C);
        }
        for (i = 0; i < nC; i++)
            tree->root = insToAvlTree(tree, tree->root, DS[i].A, DS[i].B, DS[i].C);
        free(DS);
    }
}
void RemoveFromAvl(Tree* tree)
{
    if (tree->size == 0)
    {    
        printf("[RemoveFromAvl->rc] : Дерево пустое.\n"); return;
    }
    int i, nC = 0;
    printf("[RemoveFromAvl->pI1] : Сколько желаете удалить узлов?\n> ");
    scanf("%d", &nC);
    if (nC)
    {
        int* B;
        if ((B = (int*)malloc(nC * sizeof(int))) == NULL)
            return;
        for (i = 0; i < nC; i++)
        {
            printf("> Введите ключевое значение (B) %d удаляемого узла : ", i+1);
            scanf("%d", B+i);
        }
        for (i = 0; i < nC; i++)
            tree->root = remFromAvlTree(tree, tree->root, B[i]);
        free(B);
    }
}
void menu1()
{
    printf(
        "\n\t*** Добро пожаловать! ***\n"
        "[Примечание] : Перед началом работы инициализируйте АВЛ дерево.\n\n"
        "1. Инициализировать АВЛ дерево\n\n"
        "2. Выход из программы\n\n\t***  +_+  ***\n"
    );
}
void menu2()
{
    printf(
        "\n\t*** Панель управления АВЛ деревом ***\n\n"
        "1. Сформировать АВЛ дерево (исходные данные : пустое АВЛ дерево)\n"
        "2. Сформировать файл для заполнения АВЛ дерева\n\n"
        "3. Очистить АВЛ дерево\n\n"
        "4. Добавить узел в АВЛ дерево\n"
        "5. Удалить узел из АВЛ дерева\n"
        "6. Поиск узла в дереве по значению\n"
        "7. Заменить старое значение существующего узла новым\n\n"
        "8. Вывести дерево в стандартный поток вывода (stdin)\n\n"
        "9. Вывести меню\n"
        "10. Выход из программы\n\n\t***  +_+  ***\n"
    );
}
void CP(Tree* tree)
{
    int c, flag = 0; 
    menu1();
    while (!flag)
    {
        printf("> Выберите команду : "); scanf("%d", &c);
        switch (c)
        {
        case 1:
            InitAvl(tree);
            flag++; goto M;
        break;
        case 2:
            return;
        break;
        default:
            printf("[CP->menu1->def] : Нет такой команды.\n");
        break;
        }
    }
    M:
    menu2(); int nC, M, mode, oldData, Data;
    while(1)
    {
        printf("> Выберите команду : "); scanf("%d", &c);   
        switch(c)
        {
            case 1:
                printf("[CP->menu2->c1] : Введите (через пробел) : количество узлов, значение максимального из них, режим заполнения дерева [1 -> Из файла, 2 -> Автоматически, 3 -> Вручную].\n> ");
                scanf("%d %d %d", &nC, &M, &mode);
                MakeAvl(tree, nC, M, mode);
            break;
            case 2:
                printf("[CP->menu2->c2] : Введите (через пробел) : количество узлов и значение максимального из них.\n> ");
                scanf("%d %d", &nC, &M);
                MakeFile(nC, M); 
            break;
            case 3:
                DestroyAvl(tree);
            break;
            case 4:
                InsertToAvl(tree);
            break;
            case 5:
                RemoveFromAvl(tree);
            break;
            case 6:
                LookupInAVL(tree);
            break;
            case 7:
                printf("[CP->menu2->c7] : Введите старое значение редактируемого узла.\n> "); scanf("%d", &oldData);
                EditAvlNode(tree, oldData);
            break;
            case 8:
                PrintAvl(tree);
            break;
            case 9:
                menu2();
            break;
            case 10:
                printf("[CP->menu2->c10] : Завершение работы\n"); return;
            break;
            default:
                printf("[CP->menu2->def] : Нет такой команды.\n"); 
            break;

        } 
    }
    
}
int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    CP(tree);
    free(tree);
    return 0;
}