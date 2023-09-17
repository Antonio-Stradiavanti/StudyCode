#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#define R 5
struct a {
    int b;
    char mass[R];
};
// сортировка лент методом обмена
void sort(struct a* data,int n) {
    struct a tmp; int noSwap;
    for (int i = n - 1; i >= 0; i--) {
        noSwap = 1;
        for (int j = 0; j < i; j++) {
            if (data[j].b > data[j + 1].b) {
                tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;}}
int main()
{
    int n;
    printf("Введите колличество создаваемых структур");
    scanf("%d", &n);

    //Выделяем память для массива структур
    struct a* arr = (struct a*)malloc(sizeof(struct a) * n);

    //Заполняем массив структур
    for (int i = 0; i < n; i++) {
        printf("Заполнение %d структуры\n", i + 1);
        printf("Введите целое число:");
        scanf("%d", &arr[i].b);
        printf("Введите слово из 5 букв\n");
        for (int j = 0; j < R; j++) {
            printf("%d буква:", (j + 1));
            scanf(" %c", &arr[i].mass[j]);
        }
    }
    //Вывод созданного массива
    printf("Проверка введённых данных\n");
    for (int i = 0; i < n; i++) {
        printf("%d \n", arr[i].b);
        for (int j = 0; j < R; j++) {
            printf(" %c ", arr[i].mass[j]);
        }
        printf("\n");
    }
// kol == n
// n == N
    //Выделяем память для лент
    int kol = floor(sqrt(n));// Кол-во лент округ. в меньшую сторону
    int razmer = n / kol;// Размер лент наименьний
    int ostat = n % kol;//наибольший, если есть
    struct a** lent;
    lent = (struct a**)malloc(sizeof(struct a*) * kol);
    int* razmermass;
    razmermass = (int*)malloc(sizeof(int) * kol);
    for (int i = 0; i < kol; i++) {
        if (i < ostat) {
            lent[i] = (struct a*)malloc(sizeof(struct a) * (razmer + 1));
            razmermass[i] = razmer + 1;
        }
        else {
            lent[i] = (struct a*)malloc(sizeof(struct a) * razmer);
            razmermass[i] = razmer;
        }
 }
// Подразбиение массива на ленты
    for (int j = 0; j < kol; j++) {
        if (razmermass[j] > razmer) {
            for (int i = 0; i < (razmer + 1); i++) {
                lent[j][i] = arr[j + i * kol];
            }
        }
        else {
            for (int i = 0; i < razmer; i++) {
                lent[j][i] = arr[j + i * kol];
            }
        }
    }
//Вывод лент для их проверки
    printf("Полученные ленты:");
    for (int i = 0; i < kol; i++) {
        for (int j = 0; j < razmermass[i]; j++) {

            printf("%d ", lent[i][j].b);
            for (int k = 0; k < R; k++) {
                printf(" %c ", lent[i][j].mass[k]);
            }
        } printf("\n");
    }
    free(arr);
//Сортировка лент
    for (int i = 0; i < kol; i++) {
        sort(lent[i], razmermass[i]);
}
//Слияние лент
    int *ycaz;
    ycaz = (int*)malloc(sizeof(int) * kol);
    for (int i = 0; i < kol; i++) {
        ycaz[i] = 0;
    }
    int min = 2376725375183;
    int indexlent = 0;
    struct a* newarr = (struct a*)malloc(sizeof(struct a) * n);//Сортированный массив структур
    int indexnewarr = 0;
    while (indexnewarr!=n) {
        min = 2376725375183;
        for (int i = 0; i < kol; i++) {
            if (ycaz[i]<razmermass[i] && lent[i][ycaz[i]].b < min) {
                min = lent[i][ycaz[i]].b;
                indexlent = i;
            }
        }
        newarr[indexnewarr] = lent[indexlent][ycaz[indexlent]];
        ycaz[indexlent] += 1;
        indexnewarr += 1;
}
    for (int i = 0; i < kol; i++) {
        free(lent[i]);
    }
    free(lent);
//Вывод сортированного массива
    for (int i = 0; i < n; i++) {
        printf("Сортированный массив:");
        printf("%d\n", newarr[i].b);
        for (int j = 0; j < R; j++) {
            printf(" %c", newarr[i].mass[j]);
        }
        printf("\n");}
	 return 0;}
