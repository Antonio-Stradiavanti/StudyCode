#include <stdio.h>
#include <string.h>

int main()
{
    char file_name[1024];
    printf("File: ");
    scanf("%s", file_name);

    FILE* f = fopen(strcat(file_name, ".txt"), "r");
    
    if (f == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Определеим количество строк в файле. В любом существующем файле есть хотябы одна строка
    int line_c = 0;
    // Для того чтобы пройтись по файлу нужно последовательно считать из него все символы.
    char c; 
    do 
    {
        // Строки в файле в Unix-подобных операционных системах заканчиваются пробельным символом \n
        c = fgetc(f);
        if (c == '\n') line_c++;

    } while( c != EOF );

    fclose(f);
    printf("lines: %d\n", line_c);
    return 0;
}