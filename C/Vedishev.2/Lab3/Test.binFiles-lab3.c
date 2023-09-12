#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define STRING_SIZE 256

typedef struct 
{
    char name[STRING_SIZE];
    int age;
    double avg;
} Student;

// Будет записывать в указанных файл массив структр
bool write_data(char* filename, Student* data, int t);
// Возвращает указатель на адрес младшего байта выделенной под динамический массив области памяти
Student* read_data(char* filename, int* t);

int main()
{
    Student* sch = (Student*)malloc(sizeof(Student) * 3);

    strcpy(sch[0].name, "Sanya");
    sch[0].age = 132;
    sch[0].avg = 12;

    strcpy(sch[1].name, "Sergus");
    sch[1].age = 1232;
    sch[1].avg = 123;

    strcpy(sch[2].name, "Dedus");
    sch[2].age = 17777;
    sch[2].avg = 1;

    if (write_data("sch.bin", sch, 3)) printf("The data was successefully written\n");
    else
    {
        printf("Error writng to file.\n");
        return 1;
    }

    int t = 0;
    Student* DataStore = read_data("sch.bin", &t);

    if (DataStore != NULL)
    {
        for (int i = 0; i < t; i++)
        {
            printf("\n\tName: %s\n\tAge: %d\n\tAvg: %d\n", DataStore[i].name, DataStore[i].age, DataStore[i].avg);
        }
    }

    free(sch); return 0;
}

bool write_data(char* filename, Student* data, int t)
{
    FILE* f = fopen(filename, "wb");

    if (f == NULL) return false;

    if (fwrite(&t, sizeof(int), 1, f) != 1) return false;    

    for (int i = 0; i < 3; i++)
    {
        if (fwrite(data+i, sizeof(Student), 1, f) != 1) return false;
    }

    if (fclose(f) == EOF) return false;

    return true;
}

Student* read_data(char* filename, int* t)
{
    FILE* f = fopen(filename, "rb");
    if (f == NULL) return NULL;

    // Считаем сначала количество записей, потом структуры в массив структур.
    if (fread(t, sizeof(int), 1, f) != 1) return NULL;
    Student* DataStore = (Student*)malloc(sizeof(Student) * *t);
    if (DataStore == NULL)
    {
        printf("Global error!"); exit(1);
    }

    if (fread(DataStore, sizeof(Student), *t, f) != *t)
    {
        printf("Error reading structures\n");
        free(DataStore);
        return NULL;
    }

    // Закрываем файл, обрабатываем ошибки
    if (fclose(f) == EOF) 
    {
        printf("Error closing file\n");
        free(DataStore);
        return NULL;
    }

    printf("DataStore successfully created and filled\n");
    return DataStore;
}