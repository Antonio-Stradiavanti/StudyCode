//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<locale.h>
#define MAXIMUM_FILE_NAME 1024
typedef struct TreeNode
{
	int Data;
	struct TreeNode* L;
	struct TreeNode* R;
} TreeNode;
typedef struct
{
	int size;
	TreeNode* root;
} Tree;
typedef struct
{
	int front, rear, size;
	TreeNode** array;
} Queue;
//Черновик и Отладка
void initTree(Tree* tree)
{
	if (!tree->root)
	{
		printf("[initTree] : Отмена операции : Дерево уже инициализированно.\n"); return;
	}
	tree->root = NULL; tree->size = 0;
}
void destrR(TreeNode *curNode) // VVV
{
	if (curNode == NULL) return;
	destrR(curNode->L);
	destrR(curNode->R);
	free(curNode);
}
void DestrTree(Tree* tree)
{
	if (tree->root == NULL)
	{
		printf("[destrTree] : Отмена операции : Дерево пустое.\n");
		return;
	}
	// Запускаю рекурсию
	destrR(tree->root);
	// Признак пустого дерева
	tree->root = NULL;
	printf("[destrTree] : Успех : Дерево уничтожено.\n");
}
// Служебные ф-ции для генерации дерева
TreeNode* getNewNode(int Data)
{
	TreeNode* newNode;
	if ((newNode = (TreeNode*)malloc(sizeof(TreeNode))) == NULL)
	{
		printf("[getNewNode] : Критическая ошибка : Не удалось выделить область памяти запрашиваемого размера, аварийное завершение работы.\n"); exit(1);
	}
	newNode->Data = Data; newNode->L = NULL; newNode->R = NULL;
	return newNode;
}
Queue* createQ(int size)
{
	// Выделить память под очередь
	Queue* Q;
	if ((Q = (Queue*)malloc(sizeof(Queue))) == NULL)
	{
		printf("[createQ] : Критическая ошибка : Не удалось выделить область памяти запрашиваемого размера, отмена операции.\n"); return NULL;
	}
	Q->size = size;
	// rear -> Хвостовая часть
	Q->front = Q->rear = -1;
	if ((Q->array = (TreeNode**)malloc(Q->size * sizeof(TreeNode*))) == NULL)
	{
		printf("[createQ] : Критическая ошибка : Не удалось выделить область памяти запрашиваемого размера, отмена операции.\n"); return NULL;
	}
	int i;
	for (i = 0; i < Q->size; i++)
		Q->array[i] = NULL;
	return Q;
}
// Утилиты для работы с очередью
int isQEmpty(Queue* Q)
{
	return Q->front == -1;
}
int isQFull(Queue* Q)
{
	return Q->rear == Q->size - 1;
}
int isHasOnlyOneItem(Queue* Q)
{
	return Q->front == Q->rear;
}
// Вставка элемента в очередь
void Enqueue(Queue* Q, TreeNode* curNode)
{
	if (isQFull(Q))
	{
		printf("[Enqueue] : Отмена операции : В очереди нет свободного места.\n"); return;
	}
	// Просто помещаю новый элемент в конец массива, rear служит для его индексации
	Q->array[++Q->rear] = curNode;
	// Если это первый элемент, убрать флаг пустоты
	if (isQEmpty(Q)) ++Q->front;
}
// Извлечение элемента из начала очереди
TreeNode* Dequeue(Queue* Q)
{
	// Если очередь пуста, вернуть 0
	if (isQEmpty(Q))
	{
		printf("[Dequeue] : Отмена операции : Очередь пуста.\n"); return NULL;
	}
	// Очередь в текущей реализации просто указывает на элементы из дерева, она хранит только указатели на них, поэтому при извелечении элемента из очереди нужно просто пометить этот элемент как свободный, сдвинув флаг front, на место извеленного элемента теперь можно вставлять другие элементы с помощью операции enqueue
	TreeNode* tmp = Q->array[Q->front];
	// Делаем очередь пустой
	if (isHasOnlyOneItem(Q))
		Q->front = Q->rear = -1;
	// Сдвигаем указатель на начало очереди
	else 
		++Q->front;
	return tmp;
}
TreeNode* getQFront(Queue* Q)
{
	return Q->array[Q->front];
}
int hasBothChild(TreeNode* curNode)
{
	return curNode && curNode->L && curNode->R; 
}
void genTreeInsert(Tree* tree, int Data, Queue* Q)
{
	// В очереди содержатся указатели на узлы, расположенные на одном уровне При заполнении узла потомками он извлекается из очереди.
	TreeNode *newNode = getNewNode(Data), *front;
	if (!tree->root)
	{
		printf("[genTreeInsert] : Успех : Переданное дерево было пустым, дерево успешно инициализированно.\n"); tree->root = newNode;
	}
	else
	{
		// Если очередь пуста.
		if (isQEmpty(Q))
		{
			printf("[genTreeInsert] : Примечание : Очередь была пуста, добавим в нее корень дерева.\n");
			Enqueue(Q, tree->root);
		}
		front = getQFront(Q);
		if (!front->L) front->L = newNode;
		else if (!front->R) front->R = newNode;
		// Извлечь элемент из начала очереди.
		if (hasBothChild(front)) 
		{
			Dequeue(Q);
			printf("[genTreeInsert] : Примечание : Указатель на узел был удален из начала очереди.\n"); 
		}
	}
	// Ставить новый элемент в очередь, это уже новый уровень.
	Enqueue(Q, newNode);
}
void treeSearchValue(TreeNode* curNode, TreeNode** res, int Data)
{
	if (curNode == NULL) return;
	if (curNode->Data == Data)
	{
		*res = curNode;
		return;
	}
	treeSearchValue(curNode->L, res, Data);
	treeSearchValue(curNode->R, res, Data);
}
TreeNode* searchTree(Tree* tree, int Data)
{
	// Если ничего не найдено, то ф-ция вернет NULL
	TreeNode* res = NULL;
	treeSearchValue(tree->root, &res, Data);
	return res;
}
// Обход дерева
void preorderTraversal(TreeNode *curNode)
{
	if (curNode == NULL) return;
	printf("%d, ", curNode->Data);
	preorderTraversal(curNode->L);
	preorderTraversal(curNode->R);
}
void traversalPrint(Tree *tree)
{
	if (tree->root == NULL)
	{
		printf("[traversalPrint] : Operation canceled : Tree is empty.\n");
		return;
	}
	printf("[ ");
	preorderTraversal(tree->root);
	printf("%d ]\n", tree->root->Data);
}
// Печать дерева
void printData(TreeNode* curNode, int L)
{
	if (curNode == NULL)
	{
		//printf("[printData] : curNode is NULL.\n");
		return;
	}
	for (int i = 0; i < L; i++)
		printf("  ");
	printf("%d: ", curNode->Data);
	// Однозначного метода для определения есть ли у узла-родителя потомки нет, нужно рассмотреть все случаи
	if (curNode->L == NULL && curNode->R == NULL)
		printf("[-]\n");
	else if (curNode->L == NULL && curNode->R != NULL)
		printf("[ %d ]\n", curNode->R->Data);
	else if (curNode->L != NULL && curNode->R == NULL)
		printf("[ %d ]\n", curNode->L->Data);
	else
		printf("[ %d, %d ]\n", curNode->L->Data, curNode->R->Data);
	// Выводим дочерние узлы данного узла.
	// Прямой обход, сначала вниз, потом к братьям.
	printData(curNode->L, L + 1);
	printData(curNode->R, L + 1);
}
void printTree(Tree* tree)
{
	if (tree == NULL || tree->root == NULL)
	{
		printf("[printTree] : Operation canceled : Tree is empty.\n");
		return;
	}
	printf("[printTree] : Количестов узлов в дереве : %d.\n", tree->size);
	printData(tree->root, 0);
}
// Подсчет среднего геометрического узлов по сути это тот же прямой обход только 
void GM(TreeNode* curNode, float* res, int* N)
{
	if (curNode == NULL) return;
	(*res) = (*res) * curNode->Data; (*N)++;
	GM(curNode->L, res, N);
	GM(curNode->R, res, N);
}
float sumUpGM(Tree* tree)
{
	float res = 1; int N = 0;
	GM(tree->root, &res, &N);
	/*
	Среднее геометрическое:
	- Корень степени n, где n -> количество узлов из произведения всех значений узлов.
	*/
	printf("N = %d\n", N);
	return pow(res, 1.0/N);
}
// Добавление узла к родителю
void addToParent(Tree *tree, TreeNode *parentNode, int Data)
{
	TreeNode *searchedNode = searchTree(tree, Data);

	// Если дерево пустое
	if (tree->root == NULL)
	{
		printf("[addToParent] : Примечание : Дерево пустое, новый узел будет добавлен в корень дерева.\n");
		TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
		newNode->Data = Data;
		newNode->L = NULL;
		newNode->R = NULL;
		tree->root = newNode;
	}
	else if (searchedNode == NULL)
	{
		// Если узла нет в дереве.
		TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
		newNode->Data = Data;
		newNode->L = NULL;
		newNode->R = NULL;
		if (parentNode->L == NULL)
			parentNode->L = newNode;
		else if (parentNode->R == NULL)
			parentNode->R = newNode;
		else
		{
			printf("[addToParent] : Отмена операции у родительского узла уже есть 2 потомка.");
			free(newNode);
		}
	}
	else
	{
		printf("[addToParent] : Отмена операции : Узел с переданным ключем %d уже существует.\n", Data);
	}
}
// Глубина дерева -> длина пути от корня до самого глубокого узла
/*
int maxNodeCountByDepth(int depth) // V
{
	// Если глубина 4, условно говоря в дереве 4 яруса, то максимальное количество узлов -> 31
	if (depth == 0)
		// Тогда получим один узел -> корень
		return 1;
	else
		// Количество узлов на каждом уровне дерева зависит от его степепи, степень дерева есть основание показательной ф-ции
		return pow(2, depth) + maxNodeCountByDepth(depth - 1);
}
// Глубина по количеству узлов. Размер дерева -> количество узлов в нем
int depthByNodeCount(int size) // V Считает правильно.
{
	int depth = 0;
	while (size > maxNodeCountByDepth(depth))
		depth++;
	return depth+1;
}
*/
void GenBinTree(Tree* tree, int nC, int mode, Queue* Q)
{
	if (tree->root)
	{
		printf("[GenBinTree] : Отмена операции : Дерево уже сформировано.\n"); return;
	}
	tree->root = (TreeNode*)malloc(sizeof(TreeNode));
	tree->size = 1;

	tree->root->Data = 1;
	tree->root->L = NULL;
	tree->root->R = NULL;

	Enqueue(Q, tree->root);
	printf("Очередь пуста? %d", isQEmpty(Q));

	int i = 0, M = 1;
	if (nC > 1)
	{
		int* DataStore = (int*)calloc(nC, sizeof(int));
		printf("[GenBinTree->mod2] : Введите максимальное значение узла дерева : "); scanf("%d", &M);
		if (mode == 1)
		{
			// Из файла
			char fN[MAXIMUM_FILE_NAME + 1]; FILE* f; 
			printf("[GenBinTree->mod1] : Введите имя файла.\n[Примечание] : не забудьте указать его расширение : ");
			fflush(stdin);
			scanf("%1024s", fN); printf("имя файла : %s\n", fN); 
			if ((f = fopen(fN, "r")) == NULL)
			{
				printf("[GenBinTree->mod1] : Ошибка : Не удалось открыть файл.\n"); return;
			}
			// Считываем данные из файла в массив dataStore
			for (i = 0; i < nC; i++)
				fscanf(f, "%d ", DataStore + i);
			for (i = 0; i < nC; i++)
				printf("%d ", DataStore[i]);
			printf("\n");
			if (fclose(f) == EOF)
			{
				printf("[GenBinTree->mod1] : Ошибка : Не удалось закрыть файл а следовательно и записать данные из буфера в файл и очистить память в куче, выделенную под буфер.\n"); return;
			}
		}
		else if (mode == 2)
		{
			// Случайным образом
			L:
			for (i = 0; i < nC; i++)
				DataStore[i] = 1 + (rand() % M);
			printf("\n[ ");
			for (i = 0; i < nC - 1; i++)
				printf("%d, ", DataStore[i]);
			printf("%d ]\n", DataStore[i]);
			printf("DataStore = %d, nC = %d\n", DataStore, nC);
		}
		else 
		{
			// Вручную
			if (nC > 50)
			{
				char W = 'N';
				printf("[GenBinTree->mod3] : Предупреждение : Переданное количество узлов превышает 50, ввод такого количества чисел вручную может занять много времени, желаете выбрать автоматический режим формирования дерева? [Y/N].\n");
				scanf(" %c", &W);
					if (W == 'Y')
					{
						goto L;
					}
			}
			printf("[GenBinTree->mod3] : Введите %d значений узлов дерева с клавиатуры.\n", nC);
			for (i = 0; i < nC; i++)
				scanf("%d", DataStore + i);
		}

		//depth = depthByNodeCount(nC);
		for (i = 0; i < nC; i++)
		{
			// Проверка на уникальность добавляемых значений.
			while (searchTree(tree, DataStore[i]))
				DataStore[i] = rand() % M;
			genTreeInsert(tree, DataStore[i], Q);
			tree->size++;
		}
		printf("[GenBinTree] : Всего добавлено : %d , Желаемое количество узлов : nC = %d\n", tree->size-1, nC);
		free(DataStore);
	}
	printf("[GenBinTree] : Успех : Дерево успешно сформированно.\n");
} 
void GenFile(char* fN, int N, int M)
{
	FILE* f; // N -> количество чисел, записываемых в файл, максимально возможное число
	if ((f = fopen(fN, "w")) == NULL)
	{
		printf("[genFile] : Ошибка : Не удалось открыть файл.\n"); return;
	}
	for (int i = 0; i < N; i++)
		fprintf(f, "%d ", rand() % (M + 1));
	if (fclose(f) == EOF)
	{
		printf("[genFile] : Ошибка : Не удалось закрыть файл а следовательно и записать данные из буфера в файл и очистить память в куче, выделенную под буфер.\n"); return;
	}
}
int main()
{
	//srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	Tree* tree = (Tree*)malloc(sizeof(Tree)); TreeNode* tmp;
	initTree(tree);
    //int depth; depth = depthByNodeCount(10);
    //printf("depth : %d\n", depth);
	int i;
	// Размер очереди -> количестов элементов на последнем уровне дерева
	Queue* Q = createQ(10);
	//for (i = 0; i < 10; i++)
		//genTreeInsert(tree, i, Q);
	//GenFile("tst2.txt", 10, 100);
	GenBinTree(tree, 5, 2, Q);
	tmp = searchTree(tree, 94);
	if (tmp != NULL)
		addToParent(tree, tmp, 104);
	printTree(tree);
	traversalPrint(tree);
	float res = sumUpGM(tree); printf("res = %f\n", res);
	DestrTree(tree);
	//menu(tree);
	free(Q); free(tree); return 0;
}