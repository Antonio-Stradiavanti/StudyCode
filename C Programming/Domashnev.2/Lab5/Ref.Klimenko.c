#include <stdio.h>
#include <stdlib.h>

void traversal_by_levels(int** matrix, int start_vertex, int count_vertex){
    // создаем массив посещенных вершин и заполняем его нулями
    int visited[count_vertex];
    for(int i = 0; i < count_vertex; i++){
        visited[i] = 0;
    }

    // создаем "очередь" и помещаем в нее стартовую вершину
    int queue[count_vertex], front = 0, rear = 0;
    queue[rear] = start_vertex;
    rear++;
    visited[start_vertex] = 1;
    int lvl = 0;

    // выполняем обход графа
    while(front < rear){
        printf("\nПосещенные вершины на %d уровне: ", lvl);
        int level_vertex_count = rear - front;
        
        // выводим посещенные вершины на текущем уровне
        for(int i = 0; i < level_vertex_count; i++){
            // извлекаем вершину из "очереди" и выводим ее
            int current_vertex = queue[front];
            printf("%d ", current_vertex + 1);
            front++;

            // добавляем в "очередь" все смежные, не посещённые вершины
            for(int j = 0; j < count_vertex; j++){
                if(matrix[current_vertex][j] == 1 && visited[j] == 0){
                    queue[rear] = j;
                    rear++;
                    visited[j] = 1;
                }
            }
        }
        lvl++;
    }
}

int main() {
    int count_vertex;
    int order = 0;

    printf("Введите количество вершин в графе: ");
    scanf("%d", &count_vertex);

    // выделяем память для матрицы смежности
    int** matrix = (int**)malloc(count_vertex * sizeof(int*));
    for(int i = 0; i < count_vertex; i++) {
        matrix[i] = (int*)malloc(count_vertex * sizeof(int));
    }
    
    // выделяем память для массива степени графа (храним степень для каждой вершины)
    int** order_matrix = (int**)malloc(count_vertex * sizeof(int*));
    for(int i = 0; i < count_vertex; i++){
        order_matrix[i] = (int*)malloc(sizeof(int*));
    }
    
    for(int i = 0; i < count_vertex; i++){
        order_matrix[i][1] = 0;
    }

    int k = 0; // переменная для симметричного заполнения матрицы смежности
    int temp;
    printf("Заполните матрицу смежности (1 - вершины смежные; 0 - вершины не смежные):\n");
    for(int i = 0; i < count_vertex; i++){
        for(int j = k; j < count_vertex; j++){
            // заполнение матрицы 0 по диагонали
            if(i == j){
                matrix[i][j] = 0;
                matrix[j][i] = 0;
            }else{
                printf("matrix[%d][%d] = ", i + 1, j + 1);
                scanf("%d", &temp);
                // проверка для соблюдения степени графа (количество смежных вершин не превышает 4)
                if(temp == 1){
                    order_matrix[i][1]++;
                    order_matrix[j][1]++;
                    if(order_matrix[i][1] < 5){
                        matrix[i][j] = temp;
                        matrix[j][i] = matrix[i][j];
                    }else{
                        printf("Степень графа превысила допустимое значение! Заполняем автоматически 0!\n");
                        matrix[i][j] = 0;
                        matrix[j][i] = 0;
                    }
                }else{
                    matrix[i][j] = temp;
                    matrix[j][i] = matrix[i][j];
                }
            }
        }
        k++;
    }

    // вывод введенной матрицы смежности
    printf("----------------------------\n");
    printf("Матрица смежности:\n");
    for(int i = 0; i < count_vertex; i++){
        for(int j = 0; j < count_vertex; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }    
    // вызываем обход графа по уровням
    int start_vertex;
    printf("----------------------------\n");
    printf("Введите стартовую вершину: ");
    scanf("%d", &start_vertex);
    traversal_by_levels(matrix, start_vertex - 1, count_vertex);
    printf("\n----------------------------\n");
    
    // Освобождаем выделенную память
    for(int i = 0; i < count_vertex; i++){
        free(matrix[i]);
        free(order_matrix[i]);
    }
    free(matrix);
    free(order_matrix);
    
    return 0;
}