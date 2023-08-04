#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#define AVG_STR_LEN 1024
#define TASK_TEMPLATE "\t\t\t\t___*** Вариант №%d ***___\n[Задание:] Написать программу для заполнения массива и выполнения над ним операции: %s. Каждый элемент массива представлен структурой, содержащей следующие поля: "
#define TTV1 TASK_TEMPLATE"{%s, %s, %s}.\n"
#define TTV2 TASK_TEMPLATE"{%s, %s}.\n"
#define TTV3 TASK_TEMPLATE"%s.\n"

typedef struct 
{
    // Случайное число от 1 до 30
    int fieldNum;

    char operation[AVG_STR_LEN];

    char field1[AVG_STR_LEN];
    char field2[AVG_STR_LEN];
    char field3[AVG_STR_LEN];
} Vars;

void GenDataStore(Vars** DataStore, int size)
{
    char fN1[1024], fN2[1024];
    // Буфера
    char bufScanFields[1024], bufWritefields[3][512], bufScanOp[256], bufWriteOp[256];
    //printf("[GenDataStore->in] : Введите имя файла, содержащего операции над массивом для каждого варианта:\n");
    //scanf(" %[^\n]%1024c", fN1);
    //printf("[GenDataStore->in] : Введите имя файла, содержащего поля структур для каждого варианта:\n");
    //fflush(stdin);
    //scanf(" %[^\n]%1024c", fN2);
    FILE *fOp, *fFs;
    // Файл 1 для операций
    if ((fOp = fopen("Operations.txt", "r")) == NULL)
    {
        printf("[GenDataStore->err] : Не удалось открыть файл f1.\n");
        return;
    }
    if ((fFs = fopen("Fields.txt", "r")) == NULL)
    {
        printf("[GenDataStore->err] : Не удалось открыть файл f2.\n");
        return;
    }
    // Считываем в буфер строку и из строки считываем в массив.
    int i = 0, j, added = 0;
    // Если дошли до конца файла, ставим указатель на начало.
    while (added != size)
    {
        if (feof(fOp))
            fseek(fOp, 0, SEEK_SET);  
        if (feof(fFs))
            fseek(fFs, 0, SEEK_SET);
        if (ferror(fOp) || ferror(fFs))
        {
            perror("Ошибка : "); return;
        }
        fgets(bufScanFields, 1024,fFs);
        sscanf(bufScanFields, "%*c%[^,] %*c%[^,] %*c%[^.]", bufWritefields[0], bufWritefields[1], bufWritefields[2]);
        // ---
        fgets(bufScanOp, 256,fOp);
        sscanf(bufScanOp, "%*c%[^]]", bufWriteOp);
        // ---
        if (DataStore[i] == NULL)
        {
            DataStore[i] = (Vars*)malloc(sizeof(Vars));     
        }
        // Считываем из буфера в field1, field2, field3
        //printf("here\nDataStore[i] = %d\n", DataStore[i]);
        // Нужно перебрать от конца до начала и сдвинуть все влево
        for (j = 1; j < strlen(bufWritefields[1]); j++)
            bufWritefields[1][j - 1] = bufWritefields[1][j];
        bufWritefields[1][j-1] = 0;
        for (j = 1; j < strlen(bufWritefields[2]); j++)
            bufWritefields[2][j - 1] = bufWritefields[2][j];
        bufWritefields[2][j-1] = 0;
        // Подсчитаем количество строковых полей без -
        DataStore[i]->fieldNum = 0;
        for (j = 0; j < 3; j++)
        {
            if (bufWritefields[j][0] != '-')
                DataStore[i]->fieldNum++;
        }
        //printf("here\nDataStore[i] = %d\n", DataStore[i]);
        strcpy(DataStore[i]->field1, bufWritefields[0]);
        strcpy(DataStore[i]->field2, bufWritefields[1]);
        strcpy(DataStore[i]->field3, bufWritefields[2]);
        
        strcpy(DataStore[i]->operation, bufWriteOp);

        strcpy(bufWriteOp, ""); strcpy(bufWritefields[0], ""); strcpy(bufWritefields[1], ""); strcpy(bufWritefields[2], ""); 
        added++; i++;
    // Считываем из файла и записываем в буфер, из буфера в структру.
    }
    fclose(fOp); fclose(fFs);
}
void destrDataStore(Vars** DataStore, int size)
{
    if (!DataStore[0])
    {
        printf("[destrDataStore] : Отмена операции, информационный массив пуст.\n"); return;
    }
    for (int i = 0; i < size; i++)
    {
        if (DataStore[i] != NULL)
            free(DataStore[i]);   
    }
}
void printDataStore(Vars** DataStore, int size)
{
    if (DataStore[0] == NULL)
    {
        printf("[printDataStore] : Массив пуст.\n"); return;
    }
    printf("---Data Store---\n");
    int i;
    for (i = 0; i < size-1; i++)
    {
        if (DataStore[i] != NULL)
        {
            printf("[\n\tНомер : %d\n\tКоличество полей : %d,\n\tОперация : \"%s\",\n\tПоле1 : \"%s\",\n\tПоле2 : \"%s\",\n\tПоле3 : \"%s\"\n],\n", i, DataStore[i]->fieldNum, DataStore[i]->operation, DataStore[i]->field1, DataStore[i]->field2, DataStore[i]->field3);
        }
    }
    printf("[\n\tКоличество полей : %d,\n\tОперация : \"%s\",\n\tПоле1 : \"%s\",\n\tПоле2 : \"%s\",\n\tПоле3 : \"%s\"\n]\n", DataStore[i]->fieldNum, DataStore[i]->operation, DataStore[i]->field1, DataStore[i]->field2, DataStore[i]->field3);
}
int makeTasks(Vars** DataStore, int size)
{
    int i, field;
    char variant[64];
    FILE* f;
    for (i = 0; i < size; i++)
    {
        snprintf(variant, 64, "Вариант %d.txt", i + 1);
        if ((f = fopen(variant, "w")) == NULL)
        {
            printf("[makeTasks->err] : Ошибка при создании %d-го файла.\n", i + 1); return -1;
        }

        // Тебе нужно чтобы номера вариантов шли по порядку, а все остальное через рандом.
        field = rand() % size;
        // Считаем количество полей с черточками структуре по индексу field  
        if (!strcmp(DataStore[field]->field2, "-") && !strcmp(DataStore[field]->field3, "-"))
        {
            fprintf(f, TTV3, i+1, DataStore[rand() % size]->operation, DataStore[field]->field1);    
        }
        else if (strcmp(DataStore[field]->field2, "-") != 0 && !strcmp(DataStore[field]->field3, "-"))
        {
            fprintf(f, TTV2, i+1, DataStore[rand() % size]->operation, DataStore[field]->field1, DataStore[field]->field2);
        }
        else
        {
            fprintf(f, TTV1, i+1, DataStore[rand() % size]->operation, DataStore[field]->field1, DataStore[field]->field2, DataStore[field]->field3);
        }
        if (fclose(f)==EOF)
        {
            printf("[makeTasks->err] : Ошибка при закрытии %d-го файла.\n", i + 1); return -2;
        }
        strcpy(variant, "");
    }
}

int main()
{
    setlocale(LC_ALL, "RUS"); int varNum;
    printf("[main->in] : Введите желаемое количество вариантов : ");
    fflush(stdin); scanf("%d", &varNum);
    Vars** DataStore = (Vars**)malloc(varNum * sizeof(Vars*));
    for (int i = 0 ; i < varNum; i++)
        DataStore[i] = NULL;
    // Создать файлы с названиями полей и операций.
    GenDataStore(DataStore, varNum);
    printDataStore(DataStore, varNum);
    makeTasks(DataStore, varNum);
    destrDataStore(DataStore, varNum);
    free(DataStore); return 0;
}