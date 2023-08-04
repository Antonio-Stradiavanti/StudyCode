//#define _CRT_SECURE_NO_WARNINGS
//#define strdup _strdup
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <queue>
#define STR_LEN 32
#define M 4

// При записи строки в массив символов теряется указатель на динамически выделенную область памяти, для последнего нужно использовать ф-цию strdup;

// strdup() -> возвращает указатель на байтовую строку, завершающуюся нуль-терминатором, которая является копией строки, на которую указывает аругмент ф-ции. Используется вместо strcpy для динамических массивов символов.

using namespace std;
// uniform_int_distribution -> генерирует простое случайное число в указанном диапазоне
random_device rd;
mt19937 gen(rd());
// Генератор случайных чисел c++ -> Mersenne Twister pseudo-random generator fo 32-bit -> основанных на простом числе Мерсена
typedef struct TreeNode
{
    char Data[STR_LEN];
    struct TreeNode* LeftChild;
    struct TreeNode* brother;
} TreeNode;

typedef struct Tree
{
    // int size
    TreeNode* root;
} Tree;
/*
    Поиск осуществляется в порядке одного из обходов.
    Начинается с корня
    Прямой обход:
        - Рекурсивно посещаются узлы левого под-дерева,
        - Потом посещаются узлы следующих под-деревьев
*/
void treeSearchValue(TreeNode* curNode, TreeNode** res, char* sArg)
{
    if (curNode == NULL)
    {
        return;
    }
    if (strcmp(curNode->Data, sArg) == 0)
    {
        *res = curNode;
        return;
    }
    treeSearchValue(curNode->LeftChild, res, sArg);
    treeSearchValue(curNode->brother, res, sArg);
}
// - Search(m). Осуществляет поиск в дереве узла с ключом m Возвращает искомый узел или нулевой узел, если поиск окончился неудачей.
TreeNode* treeSearch(Tree* tree, char* sArg)
{
    // Если ничего не найдено, то ф-ция вернет NULL
    TreeNode* res = NULL; 
    treeSearchValue(tree->root, &res, sArg);
    return res;
}
/* геть-ф-ции */
// Возвращает узел, являющийся корнем дерева.
TreeNode* getRoot(Tree* tree)
{
    if (tree->root == NULL)
    {
        printf("[getRoot] : Error : Tree is empty.\n");
    }
    return tree->root;
}
// Возвращает ключ узла curNode.
char* getLabel(Tree* tree, TreeNode* curNode)
{
    if (curNode == NULL)
    {
        printf("[getLabel] : Error : curNode does not exist.\n");
    }
    return curNode->Data;
}
/* set-ф-ция */
// - SetLabel(n, m). Устанавливает ключ m узла n.
void setLabel(Tree* tree, TreeNode* dNode, char* Data)
{
    // Если такого узла нет или узел с таким значением узел существует вывожу сообщение об ошибке
    TreeNode* sNode = treeSearch(tree, Data);
    if (sNode != NULL && strcmp(sNode->Data, Data) == 0)
    {
        printf("[setLabel] : Operation canceled : Node with key Data = %s is already exist.\n");
        return;
    }
    strcpy(dNode->Data, Data);
}
// - Parent(n). Возвращает родителя узла n. Если n является корнем, возвращается нулевой узел.
TreeNode* findAncestor(TreeNode* curNode, TreeNode* reqNode)
{
    if (curNode == NULL) return NULL;
    if (curNode == reqNode)
    {
        printf("[findAncestor] : Error : The root has no parent.\n");
        return NULL;
    }
    TreeNode *ancestor = NULL, *child = curNode->LeftChild;
    while (child != NULL)
    {
        if (child == reqNode)
        {
            printf("[findAncestor] : Success : The desired node was successfully found.\n");
            return curNode;
        }
        ancestor = findAncestor(child, reqNode); 
        if (ancestor != NULL)
        {
            return ancestor;
        }
        child = child->brother;
    }
    return NULL;
}
TreeNode* getParent(Tree* tree, TreeNode* reqNode)
{
    TreeNode* Parent = NULL;
    Parent = findAncestor(tree->root, reqNode);
    return Parent;
}
// Ф-ция подсчета количества потомков у данного родительского узла.
TreeNode* bC(TreeNode* parentNode, int* cC)
{
    // childCount
    TreeNode* lastBrother = parentNode->LeftChild;
    if (lastBrother != NULL)
    {
        *cC = 1;
        while (lastBrother->brother != NULL)
        {
            (*cC)++;
            lastBrother = lastBrother->brother;
        }    
    }
    // Возвращает самого правого потомка
    return lastBrother;
}
// Добавляет узел с ключом m в дерево как дочернюю вершину узла n, если в результате выполнения операции степень дерева не изменится и непосредственно перед ее выполнением функция Search(m) возвратила нулевой узел.
void addToParent(Tree* tree, char* Data, TreeNode* parentNode)
{
    // Для поиска родительского узла как раз используется ф-ция search
    // Если непосредственно перед добавлением узла ф-ция search возвратила 0
    TreeNode* isNULL = treeSearch(tree, Data); int cC = 0;
    // При добавлении должна осуществляться проверка на количество дочерних узлов у данного узла
    // Случай 1 -> дерево - пустое
    if (tree->root == NULL)
    {
        printf("[addToParent]: The tree is empty, new value will be added to the root.\n");
        // Выделим память под шаблон структуры данных
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        // Память под структуру выделена => выделена память и под Data
        strcpy(newNode->Data, Data);
        newNode->brother = NULL;
        newNode->LeftChild = NULL;
        tree->root = newNode;
    }
    // Случай 2 -> узла с переданным ключом несуществует
    else if (isNULL == NULL)
    { 
        TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode)), *curNode = bC(parentNode, &cC);
        //newNode->Data = (char*)malloc(strlen(Data));
        strcpy(newNode->Data, Data);
        // Случай 1 -> У родительского узла нет потомков
        if (parentNode->LeftChild == NULL)
        {
            parentNode->LeftChild = newNode;
            newNode->brother = NULL;
            newNode->LeftChild = NULL;
            printf("[addToParent] : Debug info : newNode is added as the first child node for parentNode.\n");
        }
        // У родительского узла есть потомки, но их меньше 4х: 
        else if (cC++ < M)
        {
            curNode->brother = newNode;
            newNode->brother = NULL;
            newNode->LeftChild = NULL;
            printf("[addToParent] : Debug info : newNode is added as the [%d] brother node for parentNode.\n", cC);
        }
        else
        {
            printf("[addToParent] : Error : Can't add newNode parent node is full.\n"); 
            free(newNode);
        }
    } 
    // Случай 3 -> узел с переданным ключом уже существует:
    else 
    {
        printf("[addToParent]: treeNode with the specified data already exist.\n");
    }
}
TreeNode* mostRightRecursion(TreeNode* parent, int brothersC, int cC)
{
    if (parent->LeftChild == NULL || brothersC <= 4 - cC)
    {
        return parent;
    }
    int cC1 = 0;
    TreeNode* helpNode = bC(parent, &cC1);
    return mostRightRecursion(helpNode, brothersC, cC1);
}
// - Delete(m). Удаляет узел с ключом m. - Удаляемый узел заменяется самым левым дочерним узлом
TreeNode* RightMostLeaf(TreeNode* dNode)
{
    // Нужен самый правый лист.
    // Должен возвращать самого правого адрес того узла, левый потомок которого 0
    // идем сначала вниз, потом вправо до нуля
    if (dNode == NULL)
        return NULL;
    while (dNode->brother != NULL)
    {
        dNode = dNode->brother;
    }
    RightMostLeaf(dNode->LeftChild);
    return dNode;
}
void deleteNode(Tree* tree, char* Data) 
{

    if (tree->root == NULL)
    {
        printf("[deleteNode] : Operation canceled : Tree is empty.\n"); return;
    }
    TreeNode *delNode, *parent, *leaf;
    if ((delNode = treeSearch(tree, Data)) == NULL) {
        printf("[deleteNode] : Error : The node with the specified data does not exist.\n");
        return;
    }
    parent = getParent(tree, delNode);
    if (parent == NULL) 
    {
        // то это корень
        // И тогда доходим до самого правого потомка root->leftChile
        if ((leaf = RightMostLeaf(tree->root->LeftChild->LeftChild)) == NULL)
            delNode->LeftChild->LeftChild = delNode->LeftChild->brother;
            // Корнем стал новый левый потомок страрого корня.
            // У корня нет братьев
        else
            // У двойки есть потомки
            leaf->LeftChild = delNode->LeftChild->brother;
        tree->root = delNode->LeftChild;
        tree->root->brother = NULL;
    } else {
    // Не корень
        // Если не корень, то до узла надо дойти
        // lastNode -> узел перед удаляемым узлом.
        // delnode -> удаляемый узел, node -> второй указатель на удаляемый           узел, он используется для связи
        TreeNode *lastNode = parent, *node = parent->LeftChild, *helpNode2; int leftChldFlag;
        // Ищу предыдущий узел перед удаляемым V.
        while (node != delNode) 
        {
            lastNode = node;
            node = node->brother;
        }
        
        // Если удаляемый узел это левый потомок родителя, предыдущие связи не интересуют
        if (lastNode->LeftChild == node)
            leftChldFlag = 1;
        else
        // Если не левый потомок родителя, а где-то посередине, нас интересуют связи слева и справа, lastnode будет указывать не на родителя а на предшествующий удаляемому узел.
            leftChldFlag = 0;

        if (node->LeftChild == NULL)
        {
            // Если удаляемый узел -> лист
            if (leftChldFlag)
                lastNode->LeftChild = node->brother;
            else
                lastNode->brother = node->brother;
        } else {
            // У удаляемого узла > 1 потомка
            if (node->LeftChild->brother != NULL)
            {
                if ((leaf = RightMostLeaf(node->LeftChild->LeftChild)) == NULL)
                    // левый потомок удаляемого узла -> лист
                    node->LeftChild->LeftChild = node->LeftChild->brother;
                
                else
                    // Не лист, Самому правому потомку левого потомка уд узла присобачиваем его братьев 
                    leaf->LeftChild = node->LeftChild->brother;
            }
            if (leftChldFlag)
                // Если удаляемый узел левый потомок родителя
                lastNode->LeftChild = node->LeftChild;
            else
                // Если не левый, а где-то посередине или в конце
                lastNode->brother = node->LeftChild;
        }
    }
    free(delNode);
}
/* Печать дерева */
void preorderTraversal(TreeNode *curNode)
{
    if (curNode == NULL) return;
    printf("%s ", curNode->Data);
    preorderTraversal(curNode->LeftChild);
    preorderTraversal(curNode->brother);
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
    printf("]\n");
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
    printf("%s: ", curNode->Data);
    // Останется только напечатать дочерние узлы данного узла
    TreeNode * helpNode = curNode->LeftChild;
    if (helpNode == NULL)
        printf("[-]\n");
    else
    {
        if (helpNode->brother != NULL)
        {
            printf("[ %s, ", helpNode->Data);
            while (helpNode->brother->brother != NULL)
            {
                helpNode = helpNode->brother;
                printf("%s, ", helpNode->Data);
            }
            printf("%s ]\n", helpNode->brother->Data);
        }
        else
        {
            printf("[ %s ]\n", helpNode->Data);
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

/* Рекурсивный алгоритм Чтобы удалить дерево, мы должны обойти все узлы дерева и удалить их один за другим. */
void delPT(TreeNode *curNode)
{
    if (curNode == NULL) return;
    delPT(curNode->brother);
    delPT(curNode->LeftChild);
    free(curNode);
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
/* Реализация Генерации дерева с помощью равномерного распределения */
void genData(char* str, int N)
{
    if (N > STR_LEN) N = STR_LEN;
    for (int i = 0; i < N; i++) str[i] = gen() % ('Z' -  'A' + 1) + 'A';
    str[N] = 0;
}
//- LeftMostChild(n). Возвращает самый левый дочерний узел узла n. Если n является листом, возвращается нулевой узел.
TreeNode* LeftMostChild(Tree* tree, TreeNode* desNode)
{
    TreeNode* tmp = desNode;
    if (tmp == NULL || tmp->LeftChild == NULL)
    {
        return NULL;
    }
    while (tmp->LeftChild != NULL)
    {
        tmp = tmp->LeftChild;
    }
    return tmp;
}
//- RightSibling(n). Возвращает правого соседа узла n и нулевой узел, если такового не существует
TreeNode* RightSibling(Tree* tree, TreeNode* desNode)
{
    if (desNode == NULL || desNode->brother == NULL)
    {
        return NULL;
    }
    return desNode->brother;
}
unsigned childNodesCount(uniform_int_distribution<int> &distr, unsigned n, unsigned nodeCount)
{
    unsigned k = distr(gen);
    k = min(k, (unsigned)4);
    k = max(k, (unsigned)1);
    k = min(k, n - nodeCount);
    return k;
}
// - GenTree(). Формирует дерево заданного количества элементов
void GenTree(Tree* tree, unsigned n, unsigned d)
{
    uniform_int_distribution<int> distr(d, M);
    
    tree->root = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(tree->root->Data, "A");
    tree->root->LeftChild = NULL;
    tree->root->brother = NULL;

    TreeNode *p, *newNode, *prevNode; char tmp[STR_LEN] = "";
    // Корень уже есть
    int nodeCount = 1, k, i = 0; 
    int cl_index = 0;
    queue<TreeNode*> Layers_queue;

    Layers_queue.push(tree->root);
    
    while (nodeCount < n)
    {
        p = Layers_queue.front(); k = 4;
        prevNode = p;
        k = childNodesCount(distr, n, nodeCount);
        for (i = 0; i < k; i++)
        {
            newNode = (TreeNode*)malloc(sizeof(TreeNode));
            nodeCount++;
            //newNode->Data = (char*)malloc(nodeCount);
            if (newNode == NULL)
            {
                printf("[GenTree] : Failure : Error memory allocation.\n");
                exit(1);
            }
            genData(tmp, nodeCount);
            strcpy(newNode->Data, tmp); strcpy(tmp, "");
            newNode->LeftChild = NULL; 
            newNode->brother = NULL;
            if (i == 0)
            {
                // По адресу ноль записываю newNode
                prevNode->LeftChild = newNode;
                prevNode = prevNode->LeftChild;
            }
            else
            {
                prevNode->brother = newNode;
                prevNode = prevNode->brother;
            }
            Layers_queue.push(newNode);
        }
        Layers_queue.pop();
    }
    printf("[GenTree] : Success : The tree has been successfully generated.\n");
}
// По результатам работы программы необходимо оценить зависимость среднего времени операции произвольного доступа к элементу от размера дерева (количества уровней и количества узлов).
void help(){
    printf(
        "*** MENU ***\n(default order)\n"
        "0 - Exit\n"
        "1 - Root\n"
        "2 - GetLabel\n"
        "3 - SetLabel. Need value\n"
        "4 - Search. Need value\n"
        "5 - Add. Need value\n"
        "6 - Delete. Need value\n"
        "7 - Parent\n"
        "8 - LeftMostChild\n"
        "9 - RightSibling\n"
        "10 - MakeNull\n"
        "11 - Print preorder traversal\n"
        "12 - PrintTree\n"
        "13 - Generate. Need values\n"
        "14 - Help\n"
    );
}
void menu(Tree* tree)
{
    int command; char tmpS[STR_LEN] = "";
    TreeNode *tmpNode = NULL, *lastNode = NULL;
    int n = 0, avg = 0, d = 0;
    while(1)
    {
        printf("> ");
        fflush(stdin);
        cin >> command;
        switch (command)
        {
            case 0:
                printf("[menu->case0] : Goodbye\n");
                return;
            break;
            case 1:
                tmpNode = getRoot(tree);
                if (tree->root != NULL)
                {
                    printf("[menu->case1] : Root of the Tree:\n%s\n", tree->root->Data);
                    lastNode = tmpNode;
                }
            break;
            case 2:
                if (lastNode != NULL)
                    printf("[menu->case2] : Label of the current node : %s.\n", getLabel(tree, lastNode));
                else printf("[menu->case2] : Last node is empty.\n");
            break;
            case 3:
                if (lastNode != NULL)
                {                   
                    printf("[menu->case3] : Set label of current node. Enter new label\n> ");
                    cin >> tmpS;
                    setLabel(tree, lastNode, tmpS);
                    printf("[menu->case3] : New label : %s.\n", lastNode->Data);
                    strcpy(tmpS, "");
                }
                else printf("[menu->case3] : Last node is empty.\n");
            break;
            case 4:
                printf("[menu->case4] : Search node by value. Enter a search argument\n> ");
                cin >> tmpS;
                tmpNode = treeSearch(tree, tmpS);
                if (tmpNode != NULL)
                {
                    printf("[menu->case4] : Search result : %s.\n", tmpNode->Data);
                    lastNode = tmpNode;
                }
                else printf("[menu->case4] : Node with the specified data does not exist.\n");
                strcpy(tmpS, "");
            break;
            case 5:
                printf("[menu->case5] : Adding new child node to lastNode.\n");
                if (lastNode != NULL)
                {
                    printf("[menu->case5] : Enter value\n> ");
                    scanf("%32s", tmpS);
                    //cin >> tmpS;
                    addToParent(tree, tmpS, lastNode);
                    strcpy(tmpS, "");
                }
                else printf("[menu->case5] : Error lastNode is empty.\n");
            break;
            case 6:
                printf("[menu->case6] : Deleting node by value. Enter value\n> ");
                fflush(stdin);
                cin >> tmpS;
                deleteNode(tree, tmpS);
                strcpy(tmpS, "");
            break;
            case 7:
                printf("[menu->case7] : Parent of the current node.\n");
                tmpNode = getParent(tree, lastNode);
                if (tmpNode)
                {
                    printf("[menu->case7] : Success : %s.\n", tmpNode->Data);
                }
            break;
            case 8:
                printf("[menu->case8] : Left most child of current node\n");
                tmpNode = LeftMostChild(tree, lastNode);
                if (tmpNode) printf("[menu->case8] : Success : %s.\n", tmpNode->Data);
                else printf("[menu->case8] : Error : lastNode is leaf.\n");
            break;
            case 9:
                printf("[menu->case9] : Right sibling of current node\n");
                tmpNode = RightSibling(tree, lastNode);
                if (tmpNode) printf("[menu->case9] : Success : %s.\n", tmpNode->Data);
                else printf("Right sibling does not exist.\n");
            break;
            case 10:
                printf("[menu->case10] : Destroy Tree (makeNull).\n");
                destrTree(tree);
            break;
            case 11:
                printf("[menu->case11] : Print preorder traveral.\n");
                traversalPrint(tree);
            break;
            case 12:
                printf("[menu->case12] : Print the tree itself.\n");
                printTree(tree);
            break;
            case 13:
                printf("[menu->case13] : Generate the tree.\n");
                if (tree->root != NULL)
                {
                    char ch = 'Y';
                    printf("[menu->case14] : Tree already generated. Do you want to regenerate it? [Y/N]\n> ");
                    cin >> ch;
                    if (ch == 'Y') 
                    {
                        destrTree(tree);
                        goto label;    
                    }
                    else 
                    {
                        printf("[menu->case13] : Operation canceled : The tree has already been generated.\n"); break;
                    }
                }
                else
                {
                    label:
                    printf("Enter [1 -> number of nodes (n), 2 -> divergence].\n> "); fflush(stdin); cin >> n;
                    printf("> "); fflush(stdin); cin >> d;
                    GenTree(tree, n, d);
                }
            break;
            case 14:
                help();
            break;
            default:
                printf("[menu->default] : Unknown command.\n");
            break;
        }
    }
}
int main()
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    if (tree == NULL) return 1;
    tree->root = NULL;
    help();
    menu(tree);
    destrTree(tree);
    free(tree);
    return 0;
}