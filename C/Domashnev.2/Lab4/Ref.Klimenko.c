#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 4 // максимальное количество дочерних узлов у родителя

struct Tree_Node {
    int data;
    struct Child_List_Node *children;
};

struct Child_List_Node {
    struct Tree_Node *node;
    struct Child_List_Node *next;
};

// создание нового узла списка Child_List_Node для заданного узла Tree_Node
struct Child_List_Node *create_child(struct Tree_Node *node) {
    struct Child_List_Node *child = (struct Child_List_Node *)malloc(sizeof(struct Child_List_Node));
    child->node = node;
    child->next = NULL;
    return child;
}

// создание узла Tree_Node с заданным значением
struct Tree_Node *create_node(int data) {
    struct Tree_Node *node = (struct Tree_Node *)malloc(sizeof(struct Tree_Node));
    node->data = data;
    node->children = NULL;
    return node;
}

// функция добавления нового дочернего узла к заданному родительскому узлу
void add_child(struct Tree_Node *parent) {
    // если у родителя не было детей, то просто добавляем 
    if (parent->children == NULL) {
        int child_data;
        printf("Введите значение ребенка: ");
        scanf("%d", &child_data);
        parent->children = create_child(create_node(child_data));
    // иначе, считаем количесвто имеещихся детей и если их меньше 4, то добавляем ребенка в конец списка    
    } else {
        int num_children = 0;
        struct Child_List_Node *sibling = parent->children;
        while (sibling->next != NULL) {
            num_children++;
            sibling = sibling->next;
        }
        if (num_children >= MAX_CHILDREN) {
            printf("Родитель не может иметь болле %d детей.\n", MAX_CHILDREN);
            return;
        }
        int child_data;
        printf("Введите значение ребенка: ");
        scanf("%d", &child_data);
        struct Tree_Node *child_node = create_node(child_data);
        struct Child_List_Node *child = create_child(child_node);
        sibling->next = child;
    }
}

// функция для поиска родителя с заданным значением 
struct Tree_Node *find_parent(struct Tree_Node *root, int parent_data) {
    if (root != NULL) {
        // если значение "корня" равны переданному значению, то возвращем корень 
        if (root->data == parent_data) {
            return root;
        }
        // иначе, начинаем обходить дочерние узлы
        struct Child_List_Node *child_node = root->children;
        while (child_node != NULL) {
            // рекурсивный вызов функции для каждого дочернего узла
            struct Tree_Node *node = find_parent(child_node->node, parent_data);
            // если рекурсивный вызов вернул указатель на узел, возвращаем его
            if (node != NULL) {
                return node;
            }
            // переходим к следующему дочернему узлу
            child_node = child_node->next;
        }
    }
    // если узел не найден
    return NULL;
}

// функция для красивого вывода дерева
void print_tree(struct Tree_Node *root, int level) {
    // проверяем, что корневой узел существует
    if (root != NULL) {
        // отступаем количесвто пробелов равное уровню узла (по 2 пробела на каждый уровень)
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        // выводим значение "корневого" узла
        printf("%d: ", root->data);
        // получаем первый дочерний узел "корня"
        struct Child_List_Node *child_node = root->children;
        // если дочерних узлов нет, то выводим [-]
        if (child_node == NULL) {
            printf("[-]\n");
        // иначе, выводим список дочерних узлов "корня", проходясь по всем братьям первого ребенка    
        } else {
            printf("[");
            while (child_node != NULL) {
                printf("%d", child_node->node->data);
                if (child_node->next != NULL) {
                    printf(", ");
                }
                child_node = child_node->next;
            }
            printf("]\n");
            // после выводим дочерние узлы для каждого дочернего узла, рекурсивно вызывая функцию вывода, увеличивая уровень
            child_node = root->children;
            while (child_node != NULL) {
                print_tree(child_node->node, level + 1);
                child_node = child_node->next;
            }
        }
    }
}

// функция для симметричного обхода дерева
void symmetrical_traversal(struct Tree_Node *node) {
    if (node != NULL) {
        // проверка наличия левого поддерва
        if (node->children != NULL) {
            // рекурсия для каждого левого поддерева
            symmetrical_traversal(node->children->node);
        }
        // выводим значение узла
        printf("%d ", node->data);

        struct Child_List_Node *child_node = NULL;
        // проверка наличия правых поддеревьев
        if (node->children != NULL) {
            // устанавливаем указатель на следующего брата, если имеется
            child_node = node->children->next;
        }
        // обходим правые поддеревья
        while (child_node != NULL) {
            // рекурсия для текущего поддерева
            symmetrical_traversal(child_node->node);
            // переход к следующему поддереву
            child_node = child_node->next;
        }
    }
}

// функция для поиска самого левого потомка для заданного узла
struct Tree_Node* find_leftmost_leaf(struct Tree_Node* node) {
    // если узла не существует
    if (node == NULL) {
        return NULL;
    }
    // если у узла нет детей (он является самым левым)
    if (node->children == NULL) {
        return node;
    }
    // иначе, вывзываем рекурсию для каждого первого ребенка узла
    return find_leftmost_leaf(node->children->node);
}

// функция для удаления узла
void delete_node(struct Tree_Node *root, int data) {
    if (root == NULL) {
        return;
    }
    if (data == root->data) {
        // находим самого левого потомка в поддереве
        struct Tree_Node *leftmost_leaf = find_leftmost_leaf(root);
        // запоминаем значение левого потомка
        int leftmost_leaf_data = leftmost_leaf->data;
        // удаляем самого левого потомка (лист)
        delete_node(root, leftmost_leaf_data);
        // заменяем значение удаляемого листа на самого левого потомка
        root->data = leftmost_leaf_data;
        return;
    }
    // задаем указатели на первого и предыдущего потомков "корня"
    struct Child_List_Node *child = root->children;
    struct Child_List_Node *prev_child = NULL;
    while (child != NULL) {
        // если нашли узел с заданым значением 
        if (child->node->data == data) {
            // если удаляемый узел не имеет потомков
            if (child->node->children == NULL) {
                // если удаляемый узел первый потомок 
                if (prev_child == NULL) {
                    // переносим указатель на брата
                    root->children = child->next;
                // если удаляемый узел в середине потомков 
                } else {
                    // переносим указатель через брата
                    prev_child->next = child->next;
                }
                free(child->node);
                free(child);
                return;
            // иначе, если удаляемый узел имеет потомков    
            } else {
                // находим самого левого потомка в поддереве
                struct Tree_Node *leftmost_leaf = find_leftmost_leaf(child->node);
                // запоминаем значение левого потомка
                int leftmost_leaf_data = leftmost_leaf->data;
                // удаляем самого левого потомка
                delete_node(root, leftmost_leaf_data);
                // заменяем значение удаляемого листа на самого левого потомка
                child->node->data = leftmost_leaf_data;
                return;
            }
        }
        // сохраняем указатель на текущего брата в предыдущего
        prev_child = child;
        // переходим к брату 
        child = child->next;
    }
    // если узел не найден в текущем поддереве, начинаем поиск в следующем, рекурсивно вызывая удаление
    child = root->children;
    while (child != NULL) {
        delete_node(child->node, data);
        child = child->next;
    }
}

// функция для генерации дочерних узлов в дереве
void add_children(struct Tree_Node* root, int node_count, int count_knot, int max_children, int min_children, int parent_data) {
    // если достигли нужного количества узлов
    if (node_count == count_knot) {
        return;
    }

    // генерируем по формуле число узлов из заданного диапозона
    int child_count = rand() % (max_children - min_children + 1) + min_children;
    // генерация дочерних узлов, пока не достигнем нужного количества всех узлов или конкретно детей у данного родителя
    for (int i = 0; i < child_count && node_count < count_knot; i++) {
        // находим нужного родителя
        struct Tree_Node *parent = find_parent(root, parent_data);
        // если у родителя не было детей, то создаем ему первого ребенка
        if (parent->children == NULL){
            parent->children = create_child(create_node(++node_count));
        // иначе ищем место для брата
        } else {
            // генерируем список текущих детей родителя
            struct Child_List_Node *sibling = parent->children;
            while (sibling->next != NULL){
                sibling = sibling->next;
            }
            // создаем ребенка
            struct Tree_Node *child_node = create_node(++node_count);
            struct Child_List_Node *child = create_child(child_node);
            sibling->next = child;
        }
    }
    // увеличиваем следубщего родителя для поиска
    parent_data++;
    // заново вывзываем функцию
    add_children(root, node_count, count_knot, max_children, min_children, parent_data);
}

// функция для генерации дерева
void generate_tree(struct Tree_Node *root, int count_knot, int max_children, int min_children) {
    int node_count = 1; // так как в дереве присутствует 1 корень
    int parent_data = 1;
    add_children(root, node_count, count_knot, max_children, min_children, parent_data);
}

int main() {
    struct Tree_Node *root = create_node(1);
    int comand = -1;
    
    while (comand != 0) {
        printf("-------------------------------------------\n");
        printf(
            "1 - Добавить дочерний узел\n"
            "2 - Вывод дерева\n"
            "3 - Симметричный обход дерева\n"
            "4 - Удалить узел\n"
            "5 - Генерация дерева\n"
            "0 - Выход из программы\n"
            "Команда - "
        );
        scanf("%d", &comand);
        switch (comand) {
            case 0:
                printf("Программа завершена");
                return 0;
            case 1:
                int parent_data;
                printf("Введите значение родительского узла: ");
                scanf("%d", &parent_data);
                struct Tree_Node *parent = find_parent(root, parent_data);
                if (parent != NULL) {
                    add_child(parent);
                } else {
                    printf("Родитель не найден.\n");
                }
                break;
            case 2:
                printf("Дерево:\n\n");
                print_tree(root, 0);
                printf("\n");
                break;
            case 3:
                printf("Симметричный обход дерева: ");
                symmetrical_traversal(root);
                printf("\n");
                break;
            case 4:
                int node_to_delete;
                printf("Удаляемый узел: ");
                scanf("%d", &node_to_delete);
                delete_node(root, node_to_delete);
                break;
            case 5:
                int count_knot, disp;
                printf("Укажите количество узлов и дисперсию: ");
                scanf("%d %d", &count_knot, &disp);
                int min_children = MAX_CHILDREN - disp;
                int max_children = MAX_CHILDREN + disp;
                generate_tree(root, count_knot, max_children, min_children);
                break;
            default:
                printf("Ошибка!\n");
                break;
        }
    }
    return 0;
}