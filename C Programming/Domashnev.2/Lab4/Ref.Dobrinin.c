/*
   Древовидная структура с ключом int; Удаляемый узел заменяется самым левым дочерним узлом;
   Распределение равномерное; Реализация - связный список дочерних узлов;
   Степень дерева - 4; Метод обхода - обратный

   Ключи уникальные
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

// Самый правый лист в поддереве
struct TreeNode *rightMostLeaf(struct TreeNode *node)
{
    if (node == NULL)
        return NULL;
    while (node->Brother != NULL)
        node = node->Brother;
    rightMostLeaf(node->LeftChild);
    return node;
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
        struct TreeNode *parent = getParent(delNode, tree), *leaf;

        // Если удаляется корень
        if (parent == NULL)
        {
            leaf = rightMostLeaf(tree->Root->LeftChild->LeftChild);
            if (leaf == NULL)
                delNode->LeftChild->LeftChild = delNode->LeftChild->Brother;
            else
                leaf->LeftChild = delNode->LeftChild->Brother;
            tree->Root = delNode->LeftChild;
            tree->Root->Brother = NULL;
        }
        else
        {
            // Для организации связей
            struct TreeNode *lastNode = parent, *node = parent->LeftChild;
            int child;

            while (node != delNode)
            {
                lastNode = node;
                node = node->Brother;
            }

            if (lastNode->LeftChild == node)
                child = 1;
            else
                child = 0;

            if (node->LeftChild == NULL) // У удаляемого узла нет потомков
            {
                if (child)
                    lastNode->LeftChild = node->Brother;
                else
                    lastNode->Brother = node->Brother;
            }
            else
            {
                if (node->LeftChild->Brother != NULL) // У удаляемого узла > 1 потомка
                {
                    leaf = rightMostLeaf(node->LeftChild->LeftChild);
                    if (leaf == NULL)
                        node->LeftChild->LeftChild = node->LeftChild->Brother;
                    else
                        leaf->LeftChild = node->LeftChild->Brother;
                    node->LeftChild->Brother = node->Brother;
                }
                if (child)
                    lastNode->LeftChild = node->LeftChild;
                else
                    lastNode->Brother = node->LeftChild;
            }
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
        return;

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
            node->LeftChild = child;
        else
            prevChild->Brother = child;
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
    return node->Brother;
}

int main()
{
    int option, key, value;
    struct TreeNode *lastNode = NULL;
    struct Tree *tree = (struct Tree *)malloc(sizeof(struct Tree));
    tree->Root = NULL;

    // Меню
    do
    {
        printf("Choose option\n0 - Exit\n1 - Get root\n2 - Get node key\n3 - Set new key to node\n4 - Search node\n5 - Add node\n6 - Delete node\n7 - Get parent node\n8 - Get left most child\n9 - Get right sibling of node\n10 - Clear tree\n11 - Generate tree\n12 - Print tree\n13 - Print result of preorder traversal\n");
        fflush(stdin);
        scanf("%d", &option);
        switch (option)
        {
        case 0:
            if (tree->Root != NULL)
                clearTree(tree);
            free(tree);
            return 0;
        case 1:
            lastNode = getRoot(tree);
            if (lastNode != NULL)
                printf("Root data: %d\nRoot address: %p\n", lastNode->Data, lastNode);
            else
                printf("Tree is empty\n");
            break;
        case 2:
            printf("Last node data: %d\n", getLabel(lastNode));
            break;
        case 3:
            printf("Which key do you want to change?\n");
            scanf("%d", &key);
            printf("Which key do you want to change the current one to?\n");
            scanf("%d", &value);
            lastNode = search(key, tree);
            setLabel(value, lastNode, tree);
            break;
        case 4:
            printf("By which key do you want to find the node?\n");
            scanf("%d", &value);
            lastNode = search(value, tree);
            if (lastNode != NULL)
                printf("Node address: %p\n", lastNode);
            else
                printf("Node not found\n");
            break;
        case 5:
            printf("To the node with which key do you want to add a new node?\n");
            scanf("%d", &key);
            lastNode = search(key, tree);
            printf("Which key do you want to add?\n");
            scanf("%d", &value);
            addToParent(value, lastNode, tree);
            break;
        case 6:
            printf("Node with which key do you want to delete?\n");
            scanf("%d", &value);
            deleteNode(value, tree);
            break;
        case 7:
            printf("Parent of the node with which key do you want to get?\n");
            scanf("%d", &value);
            lastNode = getParent(search(value, tree), tree);
            if (lastNode != NULL)
                printf("Parent data: %d\nParent address: %p\n", lastNode->Data, lastNode);
            else
                printf("There is no node with such key or this node is the root\n");
            break;
        case 8:
            printf("Leftmost child of the node with which key do you want to get?\n");
            scanf("%d", &value);
            lastNode = leftMostChild(search(value, tree));
            if (lastNode != NULL)
                printf("Leftmost child data: %d\nLeftmost child address: %p\n", lastNode->Data, lastNode);
            else
                printf("There is no node with such key or this node is a leaf\n");
            break;
        case 9:
            printf("Right sibling of the node with which key do you want to get?\n");
            scanf("%d", &value);
            lastNode = rightSibling(search(value, tree));
            if (lastNode != NULL)
                printf("Right sibling data: %d\nRight sibling address: %p\n", lastNode->Data, lastNode);
            else
                printf("There is no such node or this node has no siblings\n");
            break;
        case 10:
            clearTree(tree);
            break;
        case 11:
            treeGenerate(tree);
            break;
        case 12:
            printTree(tree);
            break;
        case 13:
            traversalPrint(tree);
            break;
        default:
            printf("There is no such option\n");
            break;
        }
    } while (option != 0);

    return 0;
}