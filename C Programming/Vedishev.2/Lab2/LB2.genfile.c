#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// будем использовать ф-цию ispunct
#define HOUSE_FORMAT_OUT "[\n\t\"street\": \"%s\", \n\t\"number\": %d,\n\t\"apartament number\": %d\n];\n"
#define F_HOUSE_FORMAT_OUT "[ \"%s\", %d, %d ];\n"
#define STREET_SIZE 100
#define ARR_SIZE 20
#define FILE_NAME 1024

typedef struct house_id {
    char street[ARR_SIZE];
    int num;
    int apat_num;
} house_id;

int main()
{
    int i;
    FILE* f = fopen("Streets.txt", "r");

    // Подсчитаем количестов символов и имен улиц в файле
    int c; // хранит считываемые символы, т.к fgetc() возвращает целые числа
    int characters = 0, streetsCount = 0; // количество символов и слов в файле
    bool comma = true;

    while (true)
    {
        // На каждой итерации цикла fgetc будет возвращать следующий символ из файла
        c = fgetc(f);

        // Условие выхода из цикла
        if (feof(f)) break;
        else if (ferror(f))
        {
            printf("Error reading file!\n");
            return 1;
        }
        // Считаем количество улиц в файле
        if (comma && !ispunct(c))
        {
            streetsCount++;
            comma = false;
        }
        else if (!comma && ispunct(c))
        {
            comma = true;
        }
    }
    // Количество улиц есть, теперь считаем их в массив:
    printf("Strets: %d\n", streetsCount);
    fclose(f);

    char** streets_a = (char**)malloc(streetsCount * sizeof(char*));
    for (i = 0; i < streetsCount; i++)
    {
        streets_a[i] = (char*)malloc(STREET_SIZE * sizeof(char));
    } 

    f = fopen("Streets.txt", "r");

    for (i = 0; i < streetsCount; i++)
    {
        fscanf(f, "%[^,]", streets_a[i]);
        fseek(f, 1, SEEK_CUR);
    }

    for (i = 0; i < streetsCount; i++)
    {
        printf("streets_a[%d] : %s\n", i, streets_a[i]);
    }
    fclose(f);

    // Сгенерируем информационный массив и запишем его в файл
    int N;
    printf("Enter the number of houses:\n");
    scanf("%d", &N);

    house_id* DataStore = (house_id*)malloc(N * sizeof(house_id));
    // Для того чтобы ф-ция выдавала различные значения при повторных вызовах главной ф-ции программы нужно чтобы параметр ф-ции srand() был переменной величиной, такой как время.
    // Ф-ция time() с параметром NULL возвращает текущее время.
    srand(time(NULL));
    for (i = 0; i < N; i++)
    {
        strcpy(DataStore[i].street, streets_a[rand() % streetsCount]);
        DataStore[i].num = rand() % 1001;
        DataStore[i].apat_num = rand() % 1001;
    }

    for (i = 0; i < N; i++)
    {
        printf(HOUSE_FORMAT_OUT, DataStore[i].street, DataStore[i].num, DataStore[i].apat_num);
    }

    // Запишем полученный информационный массив в файл
    char file_name[FILE_NAME];
    printf("Enter the name of a text file (without extension)\n");
    scanf("%s", file_name);
    f = fopen(strcat(file_name, ".txt"), "w+");

    for (i = 0; i < N; i++)
    {
        fprintf(f, F_HOUSE_FORMAT_OUT, DataStore[i].street, DataStore[i].num, DataStore[i].apat_num);
    }

    fclose(f);
    free(DataStore);
    return 0;
}