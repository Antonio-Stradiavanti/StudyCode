//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#define AVL_LFT_HEAVY 1
#define AVL_RGT_HEAVY -1
#define AVL_BALANCED 0


/* Задание

    1. Заполнение информационного массива пользователем с клавиатуры
    2. Заполнение  информационного массива из файла
    3. Добавление записи в дерево
    4. Удаление выбранной записи из дерева
    5. Редактирование выбранной записи в дереве
    6. Поиск по совпадению в дереве
    7. Вывод текущей структуры дерева
*/

// Использование доп. структуры необходимо для того чтобы отделить формирование данных и фактическую вставку узла в двоичное дерево.
typedef struct
{
	int Data, hidden, factor;
} AvlNode;
typedef struct TreeNode
{ 
	AvlNode* Data;
	// Засунуть data, hidden и factor сюда.
	struct TreeNode* L;
	struct TreeNode* R;
} TreeNode;

typedef struct
{
    int size;
	TreeNode* root;
} Tree;

void sizeOfAvlTree(Tree* tree)
{
    printf("[sizeOfAvlTree->rs] : Размер АВЛ дерева : %d.\n", tree->size);
}
void initAvlTree(Tree* tree)
{
	if (tree->root)
	{
		printf("[InitAvlTree->rc] : Дерево уже инициализированно.\n"); return;
	}
	tree->root = NULL; tree->size = 0;
    printf("[InitAvlTree->rs] : Дерево успешно инициализировано.\n");
}
/* 2. Очитка дерева */
void delLeaf(TreeNode *curNode)
{
    if (curNode == NULL)
        return;
    delLeaf(curNode->L);
    delLeaf(curNode->R);
    free(curNode);
}
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
	if (*pos)
	{
		destrLeft(tree, *pos);
		desrtRight(tree, *pos);
		free((*pos)->Data); free(*pos);
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
	if (*pos)
	{
		// Выполняем очистку левого поддерева
		destrLeft(tree, curNode->L);
		// Выполняем очистку правого поддерева
		destrRight(tree, curNode->R);
		free((*pos)->Data); free(*pos);
		*pos = NULL;
		tree->size--;
	}
}
void destroyAvlTree(Tree* tree)
{
	if (tree->root == NULL)
    {
        printf("[destroyAvlTree->rc] : Дерево пустое.\n");
        return;
    }
	// Поехали.
    destrLeft(tree, NULL);
    tree->root = NULL;
}
/* 3. Вставка узла в АВЛ дерево */

// Передаю А как двойной указатель, потому что я фактически изменяю значение указателя, в конце у меня предок А указывает на B.
void rotLeft(TreeNode** A)
{
	
	// У A коэффициент баланса == 2.
	TreeNode *B, *grandchld;
	B = (*A)->L;
	// Выполним одиночный левый поворот
	if ( B->Data->factor == AVL_LFT_HEAVY ) // +1
	{
		// Если нарушен баланс влево
		// A -> A, B -> A->L, X -> B->L
		// Левым поддеревом А становится правый дочерний узел B
		(*A)->L = B->R;
		// А становится правым поддеревом B
		B->R = *A;
		// Устанавливаем коэффициенты баланса для А и B на 0.
		(*A)->Data->factor = B->Data->factor = AVL_BALANCED;
		// Предок A указывает на B
		*A = B;
	} // Выполним двойной лево-правый поворот
	else 
	{
		// Пусть Х, узел вызвавший появление у А коэффициента баланса 2 -> левое поддерево внука.
		// Пусть (Let) корень правого поддерева B → внук (grandchild).
		grandchld = B->R; 
		// X станет корнем правого поддерева B.
		B->R = grandchld->L;
		// B теперь → левое поддерево внука.
		grandchld->L = B;
		// Левый потомок А → Правый потомок внука.
		(*A)->L = grandchld->R;
		grandchld->R = *A;
		
		switch (grandchld->Data->factor)
		{
		case AVL_LFT_HEAVY:
			(*A)->Data->factor = AVL_RGT_HEAVY;
			B->Data->factor = AVL_BALANCED;
		break;
		case AVL_BALANCED:
			(*A)->Data->factor = B->Data->factor = AVL_BALANCED;
		break;
		case AVL_RGT_HEAVY:
			(*A)->Data->factor = AVL_LFT_HEAVY;
			B->Data->factor = AVL_BALANCED;
		break;
		}
		grandchld->Data->factor = AVL_BALANCED;
		*A = grandchld;

	} 
	return;
}

void rotRight(TreeNode** A)
{
	TreeNode *B, *grandchld;
	B = (*A)->R;
	// Выполним одиночный Правый поворот
	if (B->Data->factor == AVL_RGT_HEAVY)
	{
		(*A)->R = B->L;
		B->L = *A;
		(*A)->Data->factor = B->Data->factor = AVL_BALANCED;
		*A = B;
	}
	else // Выполним двойной право-левый поворот
	{
		grandchld = B->L;
		B->L = grandchld->R;
		(*A)->R = grandchld->L;
		grandchld->L = *A;

		switch (grandchld->Data->factor)
		{
		case AVL_LFT_HEAVY:
			(*A)->Data->factor = AVL_BALANCED;
			B->Data->factor = AVL_RGT_HEAVY;
		break;
		case AVL_BALANCED:
			(*A)->Data->factor = B->Data->factor = AVL_BALANCED;
		break;
		case AVL_RGT_HEAVY:
			(*A)->Data->factor = AVL_LFT_HEAVY;
			B->Data->factor = AVL_BALANCED;
		break;
		}
		grandchld->Data->factor = AVL_BALANCED;
		*A = grandchld;
	}
	return;
}
// Вставляет узел в двоичное дерево в качестве левого потомка узла curNode
int insToBinTreeLeft(Tree* tree, TreeNode* parent, AvlNode* Data)
{
	TreeNode *newNode, **pos; 
	if (parent == NULL)
	{
		if (tree->size > 0) 
		{
			printf("[insToBinTreeLeft->rc1] : Вставка узла в корень допустима только для пустого дерева.\n"); return -1;
		}
		// Выполняем вставку в корень дерева
		*pos = &tree->root;
	}
	else
	{
		// Добавляем новый узел к листовому узлу в левой ветви родителя
		if (parent->L != NULL) 
		{
			printf("[insToBinTreeLeft->rc2] : Вставка узла допустима только для листового узла.\n"); return -1;
		}
		pos = &parent->L;
	}
	if ((newNode = (TreeNode*)malloc(sizeof(TreeNode))) == NULL)
	{
		printf("[insToBinTreeLeft->re1] : Ошибка выделения памяти.\n"); return -1;
	}
	newNode->Data = Data;
	newNode->L = newNode->R = NULL;
	*pos = newNode; tree->size++; return 0;
}
int insToBinTreeRight(Tree* tree, TreeNode* parent, AvlNode* Data)
{
	TreeNode *newNode, **pos;
	if (parent == NULL)
	{
		if (tree->size > 0)
		{
			printf("[insToBinTreeRight->rc1] : Вставка узла в корень допустима только для пустого дерева.\n");return -1;
		}
		*pos = &tree->root;
	}
	else
	{
		if (parent->R != NULL)
		{
			printf("[insToBinTreeRight->rc2] : Вставка узла допустима только для листового узла.\n"); return -1;
		}
		*pos = &parent->R;
	}
	if ((newNode = (TreeNode*)malloc(sizeof(TreeNode))) == NULL)
	{
		printf("[insToBinTreeRight->re1] : Ошибка выделения памяти.\n"); return -1;
	}
	newNode->L = newNode->R = NULL;
	newNode->Data = Data;
	*pos = newNode; tree->size++; return 0;
}
int insToAvlTree(Tree* tree, TreeNode** curNode, int Data, int* balanced)
{
	// balanced -> 

	// В процессе рекурсии будет изменяться значение указателя на curNode, поэтому используется двойной указатель.
	
	AvlNode* newAvlNode; int retv; // revt -> флаг возвращаемого ф-цией значения.

	// Идем рекурсивно вниз, добавляем новый узел.
	
	// 1. -> дерево пустое.
	if (*curNode == NULL)
	{
		if ((newAvlNode = (AvlNode*)malloc(sizeof(AvlNode))) == NULL)
		{
			printf("[insToAvlTree->re1] : Ошибка выделения памяти.\n"); return -1;
		}
		newAvlNode->factor = AVL_BALANCED;
		newAvlNode->hidden = 0;
		newAvlNode->Data = Data;
		// Нормальная операция вставки.
		return insToBinTreeLeft(tree, *curNode, newAvlNode);
	}
	else
	{
		// Вставляем узел в непустое дерево.
		if (Data < (*curNode)->Data->Data)
		{
			// Если у родительского узла левое поддерево пустое
			if ((*curNode)->L == NULL)
			{
				// Создаем новый узел.
				if ((newAvlNode = (AvlNode*)malloc(sizeof(AvlNode))) == NULL)
				{
					printf("[insToAvlTree->re2] : Ошибка выделения памяти.\n"); return -1;
				}
				newAvlNode->factor = AVL_BALANCED; newAvlNode->hidden = 0;
				newAvlNode->Data = Data;
				// Может вернуть -1, если произойдет ошибка выделения памяти.
				if (insToBinTreeLeft(tree, *curNode, newAvlNode) != 0)
				{
					printf("[insToAvlTree->re3] : Ошибка при  добавлении узла.\n"); return -1;
				}
				*balanced = 0;
			}
			else // Спускаемся вниз до листа.
			{
				// Если не равен 0, то завершаю рекурсию.

				// Вернет -1 <=> когда curNode->L == NULL, попытается добавить узел к корню, но дерево не пустое, таким образом выйдем из рекурсии.
				if ((retv = insToAvlTree(tree, &(*curNode)->L, Data, balanced)) != 0)
					return retv;
			}
			// При добавлении узла определяем как был затронут баланс дерева.
			if (!(*balanced))
			{
				switch ((*curNode)->Data->factor)
				{
				case AVL_LFT_HEAVY:
					rotLeft(curNode);
					*balanced = 1;
				break;
				case AVL_BALANCED:
					(*curNode)->Data->factor = AVL_LFT_HEAVY;
				break;
				case AVL_RGT_HEAVY:
					(*curNode)->Data->factor = AVL_BALANCED;
					*balanced = 1;
				break;
				}
			}
		} // Определяем направление движения.
		else if (Data > (*curNode)->Data->Data)
		{
			if ((*curNode)->R == NULL)
			{
				if ((newAvlNode = (AvlNode*)malloc(sizeof(AvlNode))) == NULL)
				{
					printf("[insToAvlTree->re4] : Ошибка выделения памяти.\n"); return -1;
				}
				newAvlNode->Data = Data;
				newAvlNode->factor = AVL_BALANCED;
				newAvlNode->hidden = 0;
				if (insToBinTreeRight(tree, *curNode, newAvlNode) != 0)
				{
					printf("[insToAvlTree->re5] : Ошибка при  добавлении узла.\n"); return -1;
				}
				*balanced = 0;
			}
			else
			{
				if ((retv = insToAvlTree(tree, &(*curNode)->R, Data, balanced)) != 0)
					return retv;
			}
			// Балансируем дерево
			if (!*balanced)
			{
				switch ((*curNode)->Data->factor)
				{
				case AVL_LFT_HEAVY:
					(*curNode)->Data->factor = AVL_BALANCED;
					*balanced = 1;
				break;
				case AVL_BALANCED:
					(*curNode)->Data->factor = AVL_RGT_HEAVY;
				break;
				case AVL_RGT_HEAVY:
					rotRight(curNode);
					*balanced = 1;
				break;
				}
			}	
		} // Больший и меньший данного узла узел не найден => он может быть скрыт.
		else
		{
			if (!(*curNode)->Data->hidden) return 1;
			else
			{
				// Скрытый узел, такой узел, который удален из дерева.
				(*curNode)->Data->Data = Data;
				(*curNode)->Data->hidden = 0;
				*balanced = 1;
			}
		}
	}
	return 0;
}
int Insert(Tree* tree, int d)
{
	int balanced = 0;
	return insToAvlTree(tree, &tree->root, d, &balanced);
}
/* 4. Удаление узла в АВЛ дереве */

int hideNodeInAvlTree(Tree* tree, TreeNode* curNode, int Data)
{
	int retval;
	if (curNode == NULL) return -1;
	if (curNode->Data->Data < Data)
		retval = hideNodeInAvlTree(tree, curNode->L, Data);
	else if (curNode->Data->Data > Data)
		retval = hideNodeInAvlTree(tree, curNode->R, Data);
	else
	{
		curNode->Data->hidden = 1; retval = 0;
	}
	return retval;
}
int Remove(Tree* tree, int d)
{
	return hideNodeInAvlTree(tree, tree->root, d);
}
/* 5. Поиск узла в АВЛ дереве */
// Передаем некоторый узел, начиная с которого ищем и в качестве аргумента данные. 
int lookupInAvlTree(Tree* tree, TreeNode* curNode, int* Data)
{
	int retval;
	// Выход из рекурсии.
	if (curNode == NULL)
		return -1;
	if (curNode->Data->Data < *Data)
		retval = lookupInAvlTree(tree, curNode->L, Data);
	else if (curNode->Data->Data > *Data)
		retval = lookupInAvlTree(tree, curNode->R, Data);
	// Нашел:
	else
	{
		// Если не скрыт, возвращаю искомое значение:
		if (!curNode->Data->hidden)
		{
			*Data = curNode->Data->Data;
			retval = 0;
			printf("[lookupInAvlTree->rs] : Искомый узел успешно найден, его данные : %d\n", *Data);
		}
		else
		{
			printf("[lookupInAvlTree->rf] : Искомый узел не найден в дереве.\n"); return -1;
		}
	}
}
int Lookup(Tree* tree, int* d)
{
	return lookupInAvlTree(tree, tree->root, d);
}

/* Вывод дерева */

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

/* Сформировать дерево */

void GenBinTree(Tree* tree)
{
    if (tree == NULL)
    {
        printf("[GenBinTree->r0] : В функцию передан NULL.\n");
        return;
    }
	if (tree->root)
	{
		printf("[GenBinTree->r1] : Дерево уже сформировано.\n"); return;
	}
    
	printf("[GenBinTree->r3] : Успех : Дерево успешно сформированно.\n"); 
}


int main()
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
	
    InitAvlTree(tree);
    GenBinTree(tree);
	printTree(tree);
    DestrTree(tree);
	free(tree); return 0;
}
