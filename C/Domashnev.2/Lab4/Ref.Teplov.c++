#include <vector>
#include <iostream>
#include <iomanip>
#include <random>

#define BR_C 5
#define ADR_S 10
#define VAL_S 4

using namespace std;

struct TreeNode{
    unsigned value = 0;
    TreeNode * parent;
    TreeNode * childrens[BR_C] {nullptr};
} tree;

struct serviceInformation{
    unsigned nodesCount = 0;

    // Количество узлов со степенью i. Индекс 0 - кол-во листьев
    unsigned NodeChildrens[BR_C+1] {0};
    float averageChildren = 0;

    long long maxAccessTime = 0;
    long long minAccessTime = 0;
    long long sumLeafsAccessTime = 0.0;
    long long startTime = 0;
    long long endTime = 0;
    long scanTime = 0;
    long averageAccessTime = 0;

    unsigned minHeight = 0;
    unsigned maxHeight = 0;
    unsigned summaryHeight = 0;
    float averageHeight = 0;
} servInfo;

random_device rd;
mt19937 gen(rd());

/* Объявления основных функций */
TreeNode * root();
unsigned getLabel(TreeNode *);
void setLabel(TreeNode *, unsigned);
TreeNode * search(unsigned);
void add(unsigned, TreeNode*);
void del(unsigned);
TreeNode* parent(TreeNode*);
TreeNode * leftMostChild(TreeNode*, bool);
TreeNode* rightSibling(TreeNode*, bool);
void makeNull(TreeNode*);

void treeWalk(TreeNode);
void printTree(TreeNode, unsigned);
void printServInfo(TreeNode, unsigned);
void generate(unsigned, unsigned, unsigned);

void help();
/* Определения функций */

TreeNode* root(){
    return &tree;
}

unsigned getLabel(TreeNode* p){
    return p->value;
}

void setLabel(TreeNode* p, unsigned value){
    TreeNode * prev = search(value);
    if (prev){
        cout << "Request denied. Node with label " << value <<" is already exists at " << prev << endl;
    }
    else{
        p->value = value;
    }
}

void search_step(TreeNode* p, TreeNode* &answ, unsigned val){
    // Найден ответ либо узел не существует
    if (answ || !p){
        return;
    }

    // Левый узел и значение текущего
    search_step(p->childrens[0], answ, val);
    if (p->value == val){
        answ = p;
        return;
    }

    // Последующие узлы
    for(int i = 1; i < BR_C; i++){
        search_step(p->childrens[i], answ, val);
    }
}

TreeNode * search(unsigned value){
    TreeNode * res = nullptr;
    search_step(&tree, res, value);
    return res;
}

void add(unsigned value, TreeNode* p){
    // Если дерево пустое
    if (p == &tree && !p->value){
        cout << "Tree root is empty. Overriding root value to: " << value << endl;
        p->value = value;
        return;
    };

    int newPos;
    // Если дочерний узел - пустой указатель, то прерываем цикл
    for (newPos=0; newPos < BR_C; newPos++){
        if (!p->childrens[newPos]){
            break;
        }
    }
    if (newPos == BR_C){
        cout << "Parent node is full" << endl;
        return;
    }

    TreeNode * NewNode = search(value);
    if (NewNode){
        cout << "Node with this key is already exist at adress: " << NewNode << endl;
        return;
    }

    NewNode = (TreeNode *)malloc(sizeof(TreeNode));
    NewNode->value = value;
    for(int i = 0; i < BR_C; i++){
        NewNode->childrens[i] = nullptr;
    }

    NewNode->parent = p;
    p->childrens[newPos] = NewNode;

    cout << "Node is added at adress: " << NewNode << endl;
    return;
}

bool delNode(TreeNode * p){
    /*  
    Удаляет узел путём замены его на правый дочерний узел
    Если текущий узел - лист, то он удаляется через free()
    Флаг bool говорит о том, что дочерний узел был удален и
    его следует убрать из списка дочерних узлов.
    */
    int rightNode = BR_C-1;
    for(; rightNode > -1; rightNode--){
        if (p->childrens[rightNode]){
            break;
        }
    }

    if (rightNode == -1 && p == &tree){
        // Узел является корнем дерева и листом
        tree.value = 0;
        return 0;
    }
    else if(rightNode == -1){
        free(p);
        return 1;
    }
    else{
        p->value = p->childrens[rightNode]->value;
        if(delNode(p->childrens[rightNode])){
            p->childrens[rightNode] = nullptr;
        }
    }
    return 1;
}

void del(unsigned value){
    TreeNode * trg = search(value);
    if (!trg){
        cout << "Target node not found" << endl;
        return;
    }
    if (delNode(trg)){
        cout << "Node has been deleted" << endl;
    }
    else{
        cout << "No childerns detected. Cleared root value" << endl;
    }
}

TreeNode* parent(TreeNode* p){
    return p->parent;
}

TreeNode * leftMostChild(TreeNode* p){
    int lPos;
    for(lPos = 0; lPos < BR_C; lPos++){
        if(p->childrens[lPos]){
            break;
        }
    }
    if(lPos == BR_C){
        cout << "Node is a leaf, no children nodes" << endl;
        return nullptr;
    }
    else{
        return p->childrens[lPos];
    }
}

TreeNode* rightSibling(TreeNode* p){
    TreeNode * prt = parent(p);
    if (!prt){
        cout << "Node is a root, no siblings" << endl;
        return nullptr;
    }
    int currNodePos = 0;
    for(; currNodePos < BR_C; currNodePos++){
        if (prt->childrens[currNodePos] == p){
            break;
        }
    }
    if (currNodePos == BR_C){
        cout << "Impossible Error: node is not a children of it`s parent node" << endl;
        return nullptr;
    }
    int rightSibling = currNodePos+1;
    for(; rightSibling < BR_C; rightSibling++){
        if (rightSibling){
            break;
        }
    }
    if (rightSibling == BR_C){
        cout << "Right Sibling not found or doesn`t exist" << endl;
        return nullptr;
    }
    return prt->childrens[rightSibling];
}

void makeNull(TreeNode *p=&tree){
    for(int i = 0; i < BR_C; i++){
        if (p->childrens[i]){
            makeNull(p->childrens[i]);
        }
    }
    if (p == &tree){
        tree.value = 0;
        for(int i = 0; i < BR_C; i++){
            tree.childrens[i] = nullptr;
        }
    }
    else{
        free(p);
    }
}

void treeWalk(TreeNode* p = &tree){
    if(!p){
        return;
    }
    if(!tree.value){
        cout << "Tree is empty" << endl;
        return;
    }
    int childNode;
    for(; childNode<BR_C ; childNode++){
        if (p->childrens[childNode]) break;
    }
    if (childNode < BR_C){
        treeWalk(p->childrens[childNode]);
    }
    cout << p->value << " ";
     
    for(++childNode ; childNode < BR_C ; childNode++){
        treeWalk(p->childrens[childNode]);
    }

    if (p == &tree) cout << endl;
    return;
}

void printTree(TreeNode *p = &tree, int level=0){
    if(!p){
        return;
    }
    if(!tree.value){
        cout << "Tree is empty" << endl;
        return;
    }
    int node = 0;
    // Левый дочерний узел
    for(; node < BR_C; node++){
        if (p->childrens[node]) break;
    }
    if(node < BR_C){
        printTree(p->childrens[node], level + 1);
    }
    // Текущий узел
    for(int i = level; i>0; i--){
        cout << "-";
    }
    cout << p->value << endl;

    // Правые дочерние узлы
    for(++node; node < BR_C; node++){
        if (p->childrens[node]) printTree(p->childrens[node], level+1);
    }
}

void printNode(TreeNode * p){
    cout << setw(VAL_S) << left << p->value << " ";
    cout << setw(ADR_S) << left << p << endl;
}

void clearServInfo(){
    servInfo.nodesCount = 0;

    for(int i = 0; i < BR_C+1; i++){
        servInfo.NodeChildrens[i] = 0;
    }
    servInfo.averageChildren = 0;

    servInfo.maxAccessTime = 0;
    servInfo.minAccessTime = 0;
    servInfo.sumLeafsAccessTime = 0.0;
    servInfo.startTime = 0;
    servInfo.endTime = 0;
    servInfo.scanTime = 0;
    servInfo.averageAccessTime = 0;

    servInfo.minHeight = 0;
    servInfo.maxHeight = 0;
    servInfo.summaryHeight = 0;
    servInfo.averageHeight = 0;
}

void displayServInfo(){
    cout << endl << "== Size block ==" << endl;
    cout << "Nodes count: " << servInfo.nodesCount << endl;

    cout << "Children nodes statistic (count of nodes n with x childrens)" << endl;
    cout << " " << setw(3) << left << "x:" << " " << setw(8) << left << "n:" << endl;
    for(int i = 0; i < BR_C+1; i++){
        cout << " " << setw(3) << left << i << " " << setw(8) << left << servInfo.NodeChildrens[i] << endl;
    }

    cout << "Average children nodes count: " << servInfo.averageChildren << endl;

    cout << endl << "== Time Block ==" << endl;
    cout << "Full scan time: " << servInfo.scanTime << endl;
    cout << "Max leaf access time: " << servInfo.maxAccessTime << endl;
    cout << "Min leaf access time: " << servInfo.minAccessTime << endl;
    cout << "Average leaf access time: " << servInfo.averageAccessTime << endl;

    cout << endl << "== Height Block ==" << endl;
    cout << "Max leaf height: " << servInfo.maxHeight << endl;
    cout << "Min leaf height: " << servInfo.minHeight << endl;
    cout << "Average leaf height: " << servInfo.averageHeight << endl;
     
    return;
}

void printServInfo(TreeNode *p = &tree, unsigned height = 0){
    if (!p){
        return;
    }
    time_t currTime = time(NULL);
    if (p == &tree){
        if (!tree.value){
            cout << "Tree is empty" << endl;
            return;
        }
        // Корневой узел
        clearServInfo();
        servInfo.startTime = currTime;
        cout << setw(ADR_S) << left << "NODE" << " ";
        cout << setw(VAL_S) << left << "VALUE" << " ";
        cout << "CHILDRENS" << endl;
    }

    int children_count = 0;
    int InfoNode = 0;
    int node = 0;

    // Поиск первого дочернего узла
    for(; node < BR_C; node++){
        if(p->childrens[node]){
            break;
        }
    }
    
    // Левая ветвь
    if(node < BR_C){
        printServInfo(p->childrens[node], height+1);
    }
    // информация по текущему узлу
    cout << setw(ADR_S) << left << p << " ";
    cout << setw(VAL_S) << left << p->value << " ";

    for(; InfoNode < BR_C; InfoNode++){
        if (p->childrens[InfoNode]){
            children_count++;
            cout << setw(ADR_S) << left << p->childrens[InfoNode] << " ";
        }
    }
    cout << endl;

    servInfo.nodesCount++;
    servInfo.NodeChildrens[children_count]++;

    // Если текущий узел - лист
    if (!children_count){
        // Статистика высот листьев
        if(!servInfo.minHeight){
            servInfo.minHeight = height;
        }
        else{
            servInfo.minHeight = min(servInfo.minHeight, height);
        }
        servInfo.maxHeight = max(servInfo.maxHeight, height);
        servInfo.summaryHeight += height;

        // Статистика времени доступа к листьям
        long long timeDelta = servInfo.startTime - (long long)currTime;
        if(!servInfo.minAccessTime){
            servInfo.minAccessTime = timeDelta;
        }
        servInfo.maxAccessTime = timeDelta;
        servInfo.sumLeafsAccessTime += timeDelta;
        servInfo.endTime = currTime;
    }

    for(++node ; node < BR_C; node++){
        if(p->childrens[node]){
            printServInfo(p->childrens[node], height+1);
        }
    }

    if(p==&tree){
        servInfo.endTime = (long long)time(NULL);

        servInfo.averageAccessTime = servInfo.sumLeafsAccessTime / (float)servInfo.NodeChildrens[0];
        servInfo.averageHeight = servInfo.summaryHeight / (float)servInfo.NodeChildrens[0];
        servInfo.averageChildren = servInfo.nodesCount / (float)(servInfo.nodesCount - servInfo.NodeChildrens[0]);

        cout << endl;
        displayServInfo();
    }
    return;
}

unsigned childNodesCount(normal_distribution<> &gauss, unsigned n, unsigned nodeCount){
    unsigned k = round(gauss(gen));
    k = min(k, (unsigned)BR_C);
    k = max(k, (unsigned)1);
    k = min(k, n - nodeCount);
    return k;
}

void generate(unsigned n, unsigned s, unsigned d){
    // layer == уровень
    // Встроенный класс
    normal_distribution<> gauss (s, d);
    // Очищает дерево перед генерацией.
    makeNull();

    TreeNode * p;
    unsigned nodeCount = 0;
    unsigned k;
    
    tree.value = 1;
    nodeCount += 1;

    vector<TreeNode*> currentLayer;
    vector<TreeNode *> nextLayer{&tree};
    // Current Layer index
    unsigned cl_index = 0;

    // А генерацию дерева я делал по узлам Для каждого листа по нормальному создавал несколько потомков, добавлял их в очередь листьев и убирал текущий узел

    // Симметричный обход
    while (nodeCount < n){
        // Количестов элементов в векторе
        if (cl_index == currentLayer.size()){
            // Убирает текущий узел
            currentLayer = nextLayer;
            cl_index = 0;
            // Удаляет все элементы из контейнера nextLayer
            nextLayer.clear();
        }
        // Абстрактная реализация очереди
        // Первый предок всегда корешок
        p = currentLayer[cl_index++];
        // Ф-ция определяет количество дочерних узлов на текущем уровне дерева.

        // На определенном уровне
        k = childNodesCount(gauss, n, nodeCount);

        for(unsigned i = 0; i < k; i++){
            // Добавляю новый узел
            TreeNode *pl = (TreeNode*)malloc(sizeof(TreeNode));
            // Увеличиваю Количество добавленных узлов, постоянно растет
            //nodeCount++;
            pl->value = ++nodeCount; // -> гарантирует уникальность значений.

            // Добавил узел, занулил всех потомков 
            for(unsigned j = 0; j < (unsigned)BR_C; j++){
                pl->childrens[j] = nullptr;
            }
            // Предок текущего узла -> нулевой узел на текущем уровне, добавляет по уровням, переходит к следующему

            // А у меня: p->lch = pl 

            pl->parent = p;
            p->childrens[i] = pl;
            // Кладу в конец вектора, увеличиваю размер вектора на 1. 
            nextLayer.push_back(pl);
        }
    }
    return;
}

void help(){
    cout << "== Help menu ==";
    cout << "0 - Exit" << endl;
    cout << "1 - Root" << endl;
    cout << "2 - GetLabel" << endl;
    cout << "3 - SetLabel. Need value" << endl;
    cout << "4 - Search. Need value" << endl;
    cout << "5 - Add. Need value" << endl;
    cout << "6 - Delete. Need value" << endl;
    cout << "7 - Parent" << endl;
    cout << "8 - LeftMostChild" << endl;
    cout << "9 - RightSibling" << endl;
    cout << "10 - MakeNull" << endl;
    cout << "11 - TreeWalk" << endl;
    cout << "12 - PrintTree" << endl;
    cout << "13 - PrintServInfo" << endl;
    cout << "14 - Generate(n, s, d). Need values" << endl;
    cout << "15 - Help" << endl;
    cout << endl << endl;
}

int main(){
    int command = -1;
    unsigned temp_int = 0;
    TreeNode * lastNode = &tree;
    TreeNode * tempNode = nullptr;
    unsigned n, s, d = 0;
    help();

    for (int i = 0; i < BR_C; i++){
        tree.childrens[i] = nullptr;
    }

    while(1){
        cout << "> ";
        cin >> command;
        switch (command)
        {
        case 0:
            makeNull();
            cout << "Goodbye" << endl;
            return 0;
            break;
        case 1:
            cout << "Root of tree: ";
            tempNode = root();
            printNode(tempNode);
            lastNode = tempNode;
            break;
        case 2:
            cout << "Label of the current node: " << getLabel(lastNode) << endl;
            break;
        case 3:
            cout << "Set label of current node" << endl;
            cout << "Label (int): ";
            cin >> temp_int;
            if(!cin) break;
            if(!temp_int){
                cout << "Value must be greater that zero" << endl;
                break;
            }
            setLabel(lastNode, temp_int);
            cout << "New node label: ";
            printNode(lastNode);
            break;
        case 4:
            cout << "Search node by value. Enter value: ";
            cin >> temp_int;
            if (!cin) break;
            if(!temp_int){
                cout << "Value must be greater that zero" << endl;
                break;
            }
            tempNode = search(temp_int);
            if (tempNode){
                cout << "Found node: ";
                lastNode = tempNode;
                printNode(lastNode);
            }
            else{
                cout << "Node not found" << endl;
            }
            break;
        case 5:
            cout << "Adding new node. Enter value: ";
            cin >> temp_int;
            if (!cin) break;
            if(!temp_int){
                cout << "Value must be greater that zero" << endl;
                break;
            }
            add(temp_int, lastNode);
            break;
        case 6:
            cout << "Deleting node. Enter value: ";
            cin >> temp_int;
            if (!cin) break;
            if(!temp_int){
                cout << "Value must be greater that zero" << endl;
                break;
            }
            del(temp_int);
            break;
        case 7:
            cout << "Parent of the current node: ";
            tempNode = parent(lastNode);
            if (tempNode){
                printNode(tempNode);
            }
            else{
                cout << "Current node is root" << endl;
            }
            break;
        case 8:
            cout << "Left most child of current node: ";
            tempNode = leftMostChild(lastNode);
            if (tempNode){
                printNode(tempNode);
            }
            break; 
        case 9:
            cout << "Right sibling of current node: ";
            tempNode = rightSibling(lastNode);
            if (tempNode){
                printNode(tempNode);
            }
            break; 
        case 10:
            cout << "Cleared tree" << endl;
            makeNull();
            break; 
        case 11:
            cout << "Tree walk sequence" << endl;
            treeWalk();
            break; 
        case 12:
            cout << "Full tree structure" << endl;
            printTree();
            break; 
        case 13:
            cout << "Tree technical information" << endl;
            printServInfo();
            break; 
        case 14:
            cout << "Generating tree." << endl;
            cout << "Enter nodes count: ";
            cin >> n;
            if (!cin) break;
            if(!n){
                cout << "Value must be greater that zero" << endl;
                break;
            }
            cout << "Enter average chilrens count: ";
            cin >> s;
            if (!cin) break;
            if(!s){
                cout << "Value must be greater that zero" << endl;
                break;
            }
            cout << "Enter average derivation: ";
            cin >> d;
            if (!cin) break;
            generate(n, s, d);
            cout << "Finished generating tree" << endl;
            break;
        case 15:
            help();
            break;
        default:
            if(!cin){
                cout << "Input Error" << endl;
                cin.clear();
                cin.ignore('\n', 1000);
            }
            else{
                cout << "Unknown command" << endl;
            }
            break;
        }
    }
}