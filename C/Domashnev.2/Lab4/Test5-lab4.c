#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define STR_LEN 256
#define M 4

typedef struct TreeNode
{
    int Data;
    struct TreeNode* LeftChild;
    struct TreeNode* brother;
} TreeNode;

typedef struct Tree
{
    // int size
    TreeNode* root;
} Tree;

void delPT(TreeNode *curNode)
{
    if (curNode == NULL) return;
    delPT(curNode->brother);
    delPT(curNode->LeftChild);
    free(curNode);
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
        child = child->brother;
    }
}

// Поиск родителя узла
struct TreeNode *getParent(struct TreeNode *node, struct Tree *tree)
{
    struct TreeNode *parent = NULL;
    if (tree->root == NULL || tree->root == node)
        return NULL;
    findParent(&parent, tree->root, node);
    return parent;
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
    findNodeByValue(curNode->brother, result, searchArg);
}

// Поиск узла по значению в дереве
struct TreeNode *search(int value, struct Tree *tree)
{
    struct TreeNode *result = NULL;
    findNodeByValue(tree->root, &result, value);
    return result;
}

void destrTree(Tree* tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        printf("[destrTree] : Operation canceled : The tree is already empty.\n");
        return;
    }
    // Запускаю рекурсию
    delPT(tree->root);
    // Признак пустого дерева
    tree->root = NULL;
    printf("[destrTree] : Success : The tree has been successfully destroyed.\n");
}

void addToParent(int value, struct TreeNode *parentNode, struct Tree *tree)
{
    int childrenCount = 0;
    struct TreeNode *searchedNode = search(value, tree);

    // Если дерево пустое
    if (tree->root == NULL)
    {
        printf("Tree is empty. New value will be added to the root\n");
        struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        newNode->Data = value;
        newNode->brother = NULL;
        newNode->LeftChild = NULL;
        tree->root = newNode;
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
            while (curNode->brother != NULL)
            {
                childrenCount++;
                curNode = curNode->brother;
            }
            lastNode = curNode;
        }

        if (childrenCount < M)
        {
            struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            newNode->Data = value;
            newNode->LeftChild = NULL;
            newNode->brother = NULL;

            // Поддержка связей в дереве
            if (lastNode == parentNode)
                lastNode->LeftChild = newNode;
            else
                lastNode->brother = newNode;
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

// Максимальное количество узлов по глубине
int maxNodeCountByDepth(int depth)
{
    if (depth == 0)
        return 1;
    else
        return pow(M, depth) + maxNodeCountByDepth(depth - 1);
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
void genTreeByDepth(struct Tree *tree, struct TreeNode *node, int depth, int *added, int *n)
{
    if (depth <= 0)
        return;

    struct TreeNode *prevChild = NULL;
    for (int i = 0; i < M; i++)
    {
        struct TreeNode *child = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        int tmpData = ++(*n);
        child->Data = tmpData;
        child->LeftChild = NULL;
        child->brother = NULL;

        if (prevChild == NULL)
            node->LeftChild = child;
        else
            prevChild->brother = child;
        (*added)++;
        prevChild = child;
        genTreeByDepth(tree, child, depth - 1, added, n);
    }
}

// Добавление оставшихся узлов после генерации по глубине
void addRemained(struct TreeNode *node, struct Tree *tree, int *added, int nodeCount, int *n)
{
    if (node == NULL || *added >= nodeCount)
        return;

    addRemained(node->LeftChild, tree, added, nodeCount, n);
    addRemained(node->brother, tree, added, nodeCount, n);
    for (int i = 0; i < M; i++)
    {
        if (*added >= nodeCount)
            break;
        int tmpData = ++(*n);

        if (node->LeftChild == NULL || node->LeftChild->brother == NULL || node->LeftChild->brother->brother == NULL || node->LeftChild->brother->brother->brother == NULL)
        {
            addToParent(tmpData, node, tree);
            (*added)++;
        }
    }
}

// Вспомогательная ф-ия для генерации дерева
void genTree(struct Tree *tree, int depth, int *added, int nodeCount, int *n)
{
    genTreeByDepth(tree, tree->root, depth - 1, added, n);
    int remainedNodes = nodeCount - maxNodeCountByDepth(depth - 1);
    addRemained(tree->root, tree, added, nodeCount, n);
}

// Генерация дерева
void treeGenerate(struct Tree *tree)
{
    if (tree->root != NULL)
    {
        char choice;
        printf("Tree isn't empty. Do you want to regenerate it? [y/n]: ");
        fflush(stdin);
        scanf("%c", &choice);
        if (choice == 'y')
            destrTree(tree);
        else
            return;
    }
    int nodeCount;
    printf("Enter the number of nodes in the tree: ");
    fflush(stdin);
    scanf("%d", &nodeCount);

    int added = 1, depth = depthByNodeCount(nodeCount), n = 1;
    tree->root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    tree->root->Data = n;
    tree->root->brother = NULL;
    tree->root->LeftChild = NULL;
    if (nodeCount > 1)
        genTree(tree, depth, &added, nodeCount, &n);
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
    // Останется только напечатать дочерние узлы данного узла
    TreeNode * helpNode = curNode->LeftChild;
    if (helpNode == NULL)
      printf("[-]\n");
    else
    {
      // где-то разыменовываем ноль.
      if (helpNode->brother != NULL)
      {
        printf("[ %d, ", helpNode->Data);
        while (helpNode->brother->brother != NULL)
        {
            helpNode = helpNode->brother;    
            printf("%d, ", helpNode->Data);
        }
        printf("%d ]\n", helpNode->brother->Data);
      }
      else
      {
        printf("[ %d ]\n", helpNode->Data);
      }
    }
    // Выводим дочерние узлы данного узла.
    // Прямой обход, сначала вниз, потом к братьям.
    printData(curNode->LeftChild, L+1);
    printData(curNode->brother, L);
}

void printTree(Tree* tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        printf("[printTree] : Operation canceled : Tree is empty.\n");
        return;
    }
    printData(tree->root, 0);
}

TreeNode* RightMostLeaf(TreeNode* dNode)
{
  // Нужен самый правый лист.
  // Должен возвращать самого правого адрес того узла, левый потомок которого 0
  // идем сначала вниз, потом вправо до нуля
  if (dNode == NULL)
    return NULL;
  if (dNode->LeftChild == NULL) 
    return dNode;
  while (dNode->brother != NULL)
  {
    dNode = dNode->brother;    
  }
  // Условие выхода из рекурсии
  RightMostLeaf(dNode->LeftChild);
}
void deleteNode(Tree* tree, int Data)
{
  
  TreeNode *delNode, *parent, *helpNode1; 
  if ((delNode = search(Data, tree)) == NULL) 
  {
     printf("[deleteNode] : Error : The node with the specified data does not exist.\n"); return; 
  }
  parent = getParent(delNode, tree);
  if (parent == NULL)
  {
    // то это корень
    // И тогда доходим до самого правого потомка root->leftChile
    if ((helpNode1 = RightMostLeaf(tree->root->LeftChild->LeftChild)) == NULL)
    {
        delNode->LeftChild->LeftChild = delNode->LeftChild->brother; 
        printf("\nif : delNode->LeftChild->LeftChild : %d\n", delNode->LeftChild->LeftChild);
      // Корнем стал новый левый потомок страрого корня.
        // У корня нет братьев
    }
    else
    {
      // У двойки есть потомки
      printf("\nelse : helpNode1->leftchild = %d\n", helpNode1->Data);
      helpNode1->LeftChild = delNode->LeftChild->brother;
    }
    tree->root = delNode->LeftChild;
    tree->root->brother = NULL;
    free(delNode);
  }
  // Не корень
  else
  {
    // Если не корень, то до узла надо дойти
    // lastNode -> узел перед удаляемым узлом.
    // delnode -> удаляемый узел, node -> второй указатель на удаляемый           узел, он используется для связи
    TreeNode *lastNode = parent, *node = parent->LeftChild, *helpNode2;
    // Ищу предыдущий узел перед удаляемым V.
    while (node != delNode)
    {
      lastNode = node; 
      node = node->brother; 
    }
    printf("lastNode = %d delNode = %d, delNode->brother\n", lastNode->Data, node->Data, delNode->brother);
    // Если удаляемый узел это левый потомок родителя, предыдущие связи не интересуют
    if (lastNode->LeftChild == node)
    {
      // Если удаляемый узел -> лист
      if (node->LeftChild == NULL)
      { 
        // Если лист, то его брат становится левым дочерним узлом родителя.
        lastNode->LeftChild = node->brother; 
        //printf("lastNode->LeftChild = %d", lastNode->LeftChild->Data);
      }
      else // Если не лист
      {
        // Не лист и есть братья. 
        if (node->LeftChild->brother != NULL)
        {
          if ((helpNode1 = RightMostLeaf(delNode->LeftChild->LeftChild)) == NULL)
          {
            node->LeftChild->LeftChild = node->LeftChild->brother;
          }
          else
          {
            helpNode1->LeftChild = node->LeftChild->brother;
          }
          node->LeftChild->brother = node->brother;
        }
        // Восстанавливаю связи между братьями родителя удаляемого узла и левым потомком удаляемого узла.
        lastNode->LeftChild = node->LeftChild;
      }
    }
    // Если удаляемый узел где-то в середине, lastNode -> брат удаляемого узла, нужно рассматривать предыдущие связи
    else if (lastNode->brother == node)
    {
      printf("here\n");
      // node == D, node->LeftChild == PP
      if (node->LeftChild != NULL)
      {
        printf("here2\n");
        if (node->LeftChild->brother != NULL)
        {
          // изначально передаем ноль
          if ((helpNode1 = RightMostLeaf(node->LeftChild->LeftChild)) ==  NULL)
          {
            printf("here4\n");
            // Делаем вывод что : это лист!!! и следовательно
            node->LeftChild->LeftChild = node->LeftChild->brother;
          }
          // Братья уходят вниз
          else
          {
            printf("here3, helpNode->Data = %d\n", helpNode1->Data);
            helpNode1->LeftChild = node->LeftChild->brother;
            // lastNode предшествующий удаляемому узел.
          }
          node->LeftChild->brother = node->brother;
        }
        // Просто ставим PP на место D
        lastNode->brother = node->LeftChild;
      }
      // Если удаляемый узел в середине и лист.
      else
      {
        lastNode->brother = node->brother;
      }
    }

    free(delNode);
  }
  /*
     Алгоритм удаления включает 3 случая: 
	- Начало алгоритма удаления → поиск в дереве удаляемого элемента.
	1. Элемента с ключом, равным х нет.
	2. Элемент с ключом - лист или имеет не более 1 потомка. (1 и 2) →   
    аналогично удалению узла в линейном списке (выполняется только     
    нормализация связей)
	3. Элемент с ключом имеет 2х потомков → в этом случае удаляемый элемент       нужно заменить на самый правый элемент его левого поддерева или на   
     самый левый его правого поддерева.
		- <u>Рекурсивная процедура:</u>
			- Включает вспомогательную рекурсивную процедуру, которая              вызывается в случае удаления элемента, имеющего 2х                   и более потомков.
			- При удалении элемента необходимо изменять ссылку на этот             элемент в его родителе. Удаляемые элементы просматривают из          их родителей.
  
    Удаляемый узел заменяется своим левым поддеревом, а правое           поддерево удаляемого узла становится правым поддеревом самого        правого элемента правого поддерева левого поддерева удаляемого       узла.
*/
}

int main(void) {
  Tree* tree = (Tree*)malloc(sizeof(Tree)); int 
  delNode = 0;
  tree->root = NULL;
  treeGenerate(tree);
  printTree(tree);
  printf("Enter delNode : \n");
  scanf("%d", &delNode);
  deleteNode(tree, delNode);
  printf("\n");
  printTree(tree);
  //printf("rightmost->data = %d\n", (RightMostLeaf(tree->root->LeftChild->LeftChild)->Data));
  // Возвращает адрес левого потомка 25
  destrTree(tree);
  free(tree);
  return 0;
}