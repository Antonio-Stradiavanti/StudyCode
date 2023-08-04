#include <stdio.h>
#include <string.h>
#define ARR_SIZE 100
#define FILE_NAME 20
#define HOUSE_FORMAT_OUT "[\n\t\"street\": \"%s\", \n\t\"number\": %d,\n\t\"apartament number\": %d\n]"
// В строке форматов можно использовать регулярные выражения
#define HOUSE_FORMAT_IN "[\n\t\"street\": \"%[^\"]\", \n\t\"number\": %d,\n\t\"apartament number\": %d\n]"

typedef struct house_id {
    char street[ARR_SIZE];
    int num;
    int apart_num;
} house_id;

int main()
{
    /* char name[20];
    printf("name of file: ");
    scanf("%s, note: file name must be <= 20 characters\n", name);
    // Создание файла, имя задается пользователем
    if (strlen(name) > 20)
    {
        printf("File can't be created\n");
    }
    else
    {
        FILE* f = fopen(name, "w");
        printf("\nFile succesefully created\n");
        fclose(f);
    } */

    house_id h1 = {
        .street = "Moskovskaya",
        .num = 23,
        .apart_num = 45
    };
    house_id h2;

    FILE* f1 = fopen("test1.txt", "w+");
    // обработка ошибок
    if (f1 == NULL)
    {
        return 1;
    }
    
    fprintf(f1, HOUSE_FORMAT_OUT, h1.street, h1.num, h1.apart_num);
    // После записи нужно сместить позицию курсора на 0
    fseek(f1, 0, SEEK_SET);
    // Для считывания структуры из файла используем fscanf
    fscanf( f1, HOUSE_FORMAT_IN, h2.street, &h2.num, &h2.apart_num);

    printf("h2:\nstreet: %s\nnum: %d\nnumber of apartanents: %d\n", h2.street, h2.num, h2.apart_num);

    fclose(f1);
    return 0;
}