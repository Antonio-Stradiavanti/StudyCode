/*
   Древовидная структура с ключом int; Удаляемый узел заменяется самым левым дочерним узлом;
   Распределение равномерное; Реализация - связный список дочерних узлов;
   Степень дерева - 4; Метод обхода - обратный

   Ключи должны быть уникальными
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
#define TREEDEGREE 4

struct TreeNode
{
    int Data;
    struct TreeNode *LeftChild;
    struct TreeNode *Brother;
};

struct Tree
{
    struct TreeNode *Root;
};

struct TreeNode *getRoot(struct Tree *tree)
{
    return tree->Root;
}

int getLabel(struct TreeNode *node)
{
    return node->Data;
}

// Вспомогательная ф-ия для поиска значения в дереве в порядке обратного обхода
void findNodeByValue(struct TreeNode *curNode, struct TreeNode **result, int searchArg)
{
    if (curNode == NULL)
        return;
    findNodeByValue(curNode->LeftChild, result, searchArg);
    if (curNode->Data == searchArg)
    {
        *result = curNode;
        return;
    }
    findNodeByValue(curNode->Brother, result, searchArg);
}

// Поиск узла по значению в дереве
struct TreeNode *search(int value, struct Tree *tree)
{
    struct TreeNode *result = NULL;
    findNodeByValue(tree->Root, &result, value);
    return result;
}

// Изменение значения в указанном узле
void setLabel(int value, struct TreeNode *node, struct Tree *tree)
{
    struct TreeNode *searchedNode = search(value, tree);
    if (searchedNode != NULL && searchedNode->Data == value)
        printf("Operation canceled. Node with key %d is already exists\n", value);
    else
        node->Data = value;
}

// Вспомогательная ф-ия для вывода результата обратного обхода дерева
void postorderTraversal(struct TreeNode *curNode)
{
    if (curNode == NULL)
        return;
    postorderTraversal(curNode->LeftChild);
    printf("%d ", curNode->Data);
    postorderTraversal(curNode->Brother);
}

// Вывод результата обратного обхода
void traversalPrint(struct Tree *tree)
{
    if (tree->Root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    postorderTraversal(tree->Root);
    printf("\n");
}

// Вспомогательная ф-ия для вывода дерева (в порядке прямого обхода)
void printData(struct TreeNode *curNode, int level)
{
    if (curNode == NULL)
        return;
    for (int i = 0; i < level; i++)
        printf("|--");
    printf("%d\n", curNode->Data);
    printData(curNode->LeftChild, level + 1);
    printData(curNode->Brother, level);
}

// Вывод дерева
void printTree(struct Tree *tree)
{
    if (tree->Root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    printData(tree->Root, 0);
}

// Вспомогательная ф-ия для уничтожения дерева
void delLeaf(struct TreeNode *curNode)
{
    if (curNode == NULL)
    {
        return;
    }
    delLeaf(curNode->Brother);
    delLeaf(curNode->LeftChild);
    free(curNode);
}

// Уничтожение дерева
void clearTree(struct Tree *tree)
{
    if (tree->Root == NULL)
    {
        printf("Tree is already empty\n");
        return;
    }
    delLeaf(tree->Root);
    tree->Root = NULL;
}

// Вспомогательная ф-ия поиска родителя узла
void findParent(struct TreeNode **parent, struct TreeNode *curNode, struct TreeNode *reqNode)
{
    if (curNode == NULL)
        return;

    struct TreeNode *child = curNode->LeftChild;

    while (child != NULL)
    {
        if (child == reqNode)
            *parent = curNode;
        findParent(parent, child, reqNode);
        if (*parent != NULL)
            return;
        child = child->Brother;
    }
}

// Поиск родителя узла
struct TreeNode *getParent(struct TreeNode *node, struct Tree *tree)
{
    struct TreeNode *parent = NULL;
    if (tree->Root == NULL || tree->Root == node)
        return NULL;
    findParent(&parent, tree->Root, node);
    return parent;
}

// Добавление узла к имеющемуся родителю
void addToParent(int value, struct TreeNode *parentNode, struct Tree *tree)
{
    int childrenCount = 0;
    struct TreeNode *searchedNode = search(value, tree);

    // Если дерево пустое
    if (tree->Root == NULL)
    {
        printf("Tree is empty. New value will be added to the root\n");
        struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        newNode->Data = value;
        newNode->Brother = NULL;
        newNode->LeftChild = NULL;
        tree->Root = newNode;
    }
    else if (searchedNode == NULL)
    {
        struct TreeNode *curNode = parentNode->LeftChild, *lastNode;

        // Выясняю как добавить новое значение (как самого 1го потомка или как ещё одного вдобавок к имеющимся)
        if (curNode == NULL)
        {
            lastNode = parentNode;
        }
        else
        {
            childrenCount = 1;
            while (curNode->Brother != NULL)
            {
                childrenCount++;
                curNode = curNode->Brother;
            }
            lastNode = curNode;
        }

        if (childrenCount < TREEDEGREE)
        {
            struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            newNode->Data = value;
            newNode->LeftChild = NULL;
            newNode->Brother = NULL;

            // Поддержка связей в дереве
            if (lastNode == parentNode)
                lastNode->LeftChild = newNode;
            else
                lastNode->Brother = newNode;
        }
        else
        {
            printf("Cannot add new value. Parent node is full\n");
        }
    }
    else
    {
        printf("Node with key %d is already exists\n", value);
    }
}

// Удаление узла по значению
void deleteNode(int value, struct Tree *tree)
{
    if (tree->Root == NULL)
    {
        printf("Tree is empty. Cannot delete node with key %d\n", value);
        return;
    }
    struct TreeNode *delNode = search(value, tree);

    if (delNode != NULL)
    {
        struct TreeNode *parent;
        int tmp;

        // Смена значений левых потомков вверх к удаляемому узлу (значение удаляемого узла станет значением самого глубокого левого листа)
        if (delNode->LeftChild != NULL)
        {
            while (delNode->LeftChild != NULL)
            {
                tmp = delNode->Data;
                delNode->Data = delNode->LeftChild->Data;
                delNode->LeftChild->Data = tmp;
                delNode = delNode->LeftChild;
            }
        }

        // Корректировка связей
        parent = getParent(delNode, tree);
        if (parent->LeftChild == delNode)
            parent->LeftChild = delNode->Brother;
        else
        {
            struct TreeNode *lastNode = parent->LeftChild;
            while (lastNode->Brother != delNode)
                lastNode = lastNode->Brother;
            lastNode->Brother = delNode->Brother;
        }
        free(delNode);
    }
    else
        printf("There is no %d in the tree. Operation canceled\n", value);
}

// Максимальное количество узлов по глубине
int maxNodeCountByDepth(int depth)
{
    if (depth == 0)
        return 1;
    else
        return pow(TREEDEGREE, depth) + maxNodeCountByDepth(depth - 1);
}

// Глубина по количеству узлов
int depthByNodeCount(int nodeCount)
{
    int depth = 0;
    while (nodeCount > maxNodeCountByDepth(depth))
        depth++;
    return depth;
}

// Генерация дерева по глубине
void genTreeByDepth(struct Tree *tree, struct TreeNode *node, int depth, int *added)
{
    if (depth <= 0)
    {
        return;
    }

    struct TreeNode *prevChild = NULL;
    for (int i = 0; i < TREEDEGREE; i++)
    {
        struct TreeNode *child = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        int tmpData = rand() % 1000;
        while (search(tmpData, tree) != NULL)
            tmpData = rand() % 1000;
        child->Data = tmpData;
        child->LeftChild = NULL;
        child->Brother = NULL;

        if (prevChild == NULL)
        {
            node->LeftChild = child;
        }
        else
        {
            prevChild->Brother = child;
        }
        (*added)++;
        prevChild = child;
        genTreeByDepth(tree, child, depth - 1, added);
    }
}

// Добавление оставшихся узлов после генерации по глубине
void addRemained(struct TreeNode *node, struct Tree *tree, int *added, int nodeCount)
{
    if (node == NULL || *added >= nodeCount)
        return;

    addRemained(node->LeftChild, tree, added, nodeCount);
    addRemained(node->Brother, tree, added, nodeCount);
    for (int i = 0; i < TREEDEGREE; i++)
    {
        if (*added >= nodeCount)
            break;
        int tmpData = rand() % 1000;
        while (search(tmpData, tree) != NULL)
            tmpData = rand() % 1000;

        if (node->LeftChild == NULL || node->LeftChild->Brother == NULL || node->LeftChild->Brother->Brother == NULL || node->LeftChild->Brother->Brother->Brother == NULL)
        {
            addToParent(tmpData, node, tree);
            (*added)++;
        }
    }
}

// Вспомогательная ф-ия для генерации дерева
void genTree(struct Tree *tree, int depth, int *added, int nodeCount)
{
    genTreeByDepth(tree, tree->Root, depth - 1, added);
    int remainedNodes = nodeCount - maxNodeCountByDepth(depth - 1);
    addRemained(tree->Root, tree, added, nodeCount);
}

// Генерация дерева
void treeGenerate(struct Tree *tree)
{
    if (tree->Root != NULL)
    {
        char choice;
        printf("Tree isn't empty. Do you want to regenerate it? [y/n]: ");
        fflush(stdin);
        scanf("%c", &choice);
        if (choice == 'y')
            clearTree(tree);
        else
            return;
    }
    int nodeCount;
    printf("Enter the number of nodes in the tree: ");
    fflush(stdin);
    scanf("%d", &nodeCount);

    int added = 1, depth = depthByNodeCount(nodeCount);
    tree->Root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    tree->Root->Data = rand() % 1000;
    tree->Root->Brother = NULL;
    tree->Root->LeftChild = NULL;
    if (nodeCount > 1)
        genTree(tree, depth, &added, nodeCount);
}

// Поиск самого левого потомка узла
struct TreeNode *leftMostChild(struct TreeNode *node)
{
    struct TreeNode *tmp = node;
    if (tmp == NULL || tmp->LeftChild == NULL)
        return NULL;
    while (tmp->LeftChild != NULL)
        tmp = tmp->LeftChild;
    return tmp;
}

// Поиск правого соседа узла
struct TreeNode *rightSibling(struct TreeNode *node)
{
    if (node == NULL || node->Brother == NULL)
        return NULL;
    if (node->Brother != NULL)
        return node->Brother;
}

int main()
{
    struct Tree *tree = (struct Tree *)malloc(sizeof(struct Tree));
    tree->Root = NULL;
    addToParent(4, tree->Root, tree);
    addToParent(5, tree->Root, tree);
    addToParent(6, tree->Root, tree);
    addToParent(7, tree->Root, tree);
    addToParent(8, tree->Root, tree);
    addToParent(9, tree->Root->LeftChild->Brother->Brother, tree);
    addToParent(10, tree->Root->LeftChild, tree);
    addToParent(15, tree->Root->LeftChild, tree);
    addToParent(16, tree->Root->LeftChild, tree);
    addToParent(11, tree->Root->LeftChild->Brother->Brother->Brother, tree);
    addToParent(12, tree->Root->LeftChild, tree);
    addToParent(13, tree->Root->LeftChild->LeftChild, tree);
    addToParent(14, tree->Root->LeftChild->LeftChild->LeftChild, tree);

    printTree(tree);

    treeGenerate(tree);

    printTree(tree);

    clearTree(tree);
    free(tree);
    return 0;
}