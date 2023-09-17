#include <stdio.h>
#include <stdlib.h>
#define N 3

struct file{
    char surname[20];
    int deg;
};

int main(){
    FILE* f;
    char name[35];
    int n = N;
    printf("name of file: ");
    scanf("%s", name);
    // -- открытие файла, с обработкой ошибок
    f = fopen(name, "r");
    if (f == NULL){
        printf("Error file\n");
    }
    fclose(f);
    // --
    int function = 0;
    int count;
    // Массив данных из файла
    struct file mas[N];
    // Типа менюшка
    printf("1 – чтение\n2-вывод\n3-расчет среднего\n4-добавление\n5-удаление\n");
    while (function != -1){
        printf("fuction № ");
        scanf("%d", &function);
        // Чтение
        if ((function == 1) || (function == 2) || (function == 3)){
            count = 0;
            f = fopen(name, "r");
            while ((count / 2) != n){
                count++;
                if (count % 2 == 1){
                    fscanf(f, "%s", mas[(count - 1) / 2].surname);
                }
                else{
                    fscanf(f, "%d", &mas[(count - 1) / 2].deg);
                }
            }
            fclose(f);
        }
        // Вывод
        if (function == 2){
            for (int i = 0 ; i < n; i++){
                printf("%s %d\n", mas[i].surname, mas[i].deg);
            }
        }
        // Расчет
        if (function == 3){
            float srednee = 0;
            for (int i = 0; i < n; i++){
                srednee += mas[i].deg;
            }
            srednee /= n;
            printf("srednee = %.2f\n", srednee);
        }
        // Добавление в файл
        if (function == 4){
            f = fopen(name, "w");
            char surname[20];
            int deg;
            printf("count of elements: ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++){
                printf("new surname: ");
                scanf("%s", surname);
                fprintf(f, "%s\n", surname);

                printf("new degree = ");
                scanf("%d", &deg);
                fprintf(f, "%d\n", deg);
            }
            fclose(f);
        }
        // Удаление из файла
        if (function == 5){
            f = fopen(name, "r");
            int del_element;
            printf("delete element # ");
            scanf("%d", &del_element);
            count = 0;
            char x[20];
            int y;
            int point = 0;
            while ((count / 2) != n){
                count++;
                if ((count - 1) / 2 != del_element){
                    if (count % 2 == 1){
                        fscanf(f, "%s", mas[(count - 1 - point) / 2].surname);
                    }
                    else{
                        fscanf(f, "%d", &mas[(count - 1 - point) / 2].deg);
                    }
                }
                else{
                    point++;
                    if (count % 2 == 1){
                        fscanf(f, "%s", x);
                    }
                    else{
                        fscanf(f, "%d", &y);
                    }
                }
            }
            fclose(f);
            n--;
            f = fopen(name, "w");
            for (int i = 0; i < n; i++){
                fprintf(f, "%s\n", mas[i].surname);
                fprintf(f, "%d\n", mas[i].deg);
            }
            fclose(f);
        }
    }
    return 0;
}