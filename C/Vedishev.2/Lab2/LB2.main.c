#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARR_SIZE 20
#define FILE_NAME 1024
#define HOUSE_FORMAT_OUT "[\n\t\"street\": \"%s\", \n\t\"number\": %d,\n\t\"apartament number\": %d\n];\n"
#define F_HOUSE_FORMAT_OUT "[ \"%s\", %d, %d ];\n"
#define F_HOUSE_FORMAT_IN "[ \"%[^\"]\", %d, %d ];\n"

typedef struct house_id {
    char street[ARR_SIZE];
    int num;
    int apat_num;
} house_id;

int main() {
    // argc, argv[]
    // Объявление основных переменных
    int i, line_c = 0, function = 0, insert_index, delete_index;
    FILE* f; FILE* f1; house_id insert_item;
    char c, file_name[FILE_NAME], file_name1[FILE_NAME], isexit = 'N';

    // Нужно считать уже созданный файл
    // TODO создать менюшку

    printf("Enter the name of the file you want to open (without extension)\n");
    scanf("%s", file_name);
    f = fopen(strcat(file_name, ".txt"), "r");
    if (f == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    // Определеим количество строк в файле. В любом существующем файле есть хотябы одна строка. Для того чтобы пройтись по файлу нужно последовательно считать из него все символы.
    do 
    {
        // Строки в файле в Unix-подобных операционных системах заканчиваются пробельным символом \n
        c = fgetc(f);
        if (c == '\n') line_c++;

    } while( c != EOF );
    house_id* DataStore = (house_id*)malloc(line_c * sizeof(house_id));
    
    // Менюшка:
    do
    {
        printf("Choose function:\n[1 -> read from a file, 2 -> print DataStore, 3 -> print total values, 4 -> add record to the DataStore, 5 -> remove record from the DataStore, 6 -> Write the DataStore to a new file]\n");
        fflush(stdin);
        scanf("%d", &function);

        switch (function)
        {
        case 1:
            // 1. Читаем из файла
            // Поставим файловую позицию потока в начало файла
            fseek(f, 0, SEEK_SET);
            for (i = 0; i < line_c; i++)
            {
                fscanf(f, F_HOUSE_FORMAT_IN, DataStore[i].street, &DataStore[i].num, &DataStore[i].apat_num);
            }
            printf("DataStore susseccfully filled!\n");    
            break;
        case 2:
            // 2. Выведем полученный информационный массив
            for (i = 0; i < line_c; i++)
            {
                printf("--- house: %d ---\n"HOUSE_FORMAT_OUT, i, DataStore[i].street, DataStore[i].num, DataStore[i].apat_num);
            }
            break;
        case 3:
            // 3. Расчет итоговых значений по массиву данных
            int total_apart_num = 0;
            for (i = 0; i < line_c; i++)
            {
                total_apart_num += DataStore[i].apat_num;
            }
            printf("--- Total number of apartments: %d ---\n", total_apart_num);
            break;
        case 4:
            // Добавление записи в конец информационного массива
            printf("Enter new house:\n");
            printf("Enter street: "); fflush(stdin); scanf("%s", insert_item.street);
            printf("Enter house num: "); fflush(stdin); scanf("%d", &insert_item.num);
            printf("Enter number of apartements: "); fflush(stdin); scanf("%d", &insert_item.apat_num);
            line_c++;
            house_id* DataStore_old = DataStore;
            DataStore = (house_id*)realloc(DataStore, sizeof(line_c));
            
            strcpy(DataStore[line_c-1].street, insert_item.street);
            DataStore[line_c-1].num = insert_item.num;
            DataStore[line_c-1].apat_num = insert_item.apat_num;

            printf("DataStore old = %d; DataStore new = %d\n", DataStore, DataStore_old);
            if (DataStore_old != DataStore)
            {
                free(DataStore_old);
            }
            // Сделать доп проверку на различие адресов DataStore и DataStore_old 
            break;
        case 5:
            // Удаление записи из информационного массива по индексу
            printf("Enter value index to delete:\n");
            scanf("%d", &delete_index);
            for (i = delete_index; i < line_c; i++)
            {
                strcpy(DataStore[i].street, DataStore[i+1].street);
                DataStore[i].num = DataStore[i+1].num;
                DataStore[i].apat_num = DataStore[i+1].apat_num;
            }
            line_c--;
            DataStore = (house_id*)realloc(DataStore, sizeof(line_c));
            break;
        case 6: 
            // Запись обработанного массива данных в любой файл. Откроем новый файл в режиме запись
            printf("Enter the name of the file you want to write out DataStore (without extension)\n");
            scanf("%s", file_name1);
            f1 = fopen(strcat(file_name1, ".txt"), "w");

            for (i = 0; i < line_c; i++)
            {
                fprintf(f1, F_HOUSE_FORMAT_OUT, DataStore[i].street, DataStore[i].num, DataStore[i].apat_num);
            }
            printf("Edited DataStore successfully written to a new file!\n");
            fclose(f1);
            break;
        default:
            printf("You entered the wrong number\n");
            break;
        }
        printf("Finish working with this file? [78 -> N, 89 -> Y]\n"); 
		fflush(stdin);
        // Ловушка для клавиши enter
		scanf(" %c", &isexit);
	} while (isexit != 89);
    fclose(f); free(DataStore);
    return 0;
}
