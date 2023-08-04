#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
int main()
{
    //FILE *f1; int i;
    
    char variant[64];
    int i=0; FILE* f;

    snprintf(variant, 64, "Вариант %d.txt", i + 1);
    if ((f = fopen(variant, "w")) == NULL)
    {
        printf("[makeTasks->err] : Ошибка при создании %dго файла.\n", i + 1); return -1;
    }
    fprintf(f, "Аниме");
    if (fclose(f)==EOF)
    {
        printf("[makeTasks->err] : Ошибка при закрытии %dго файла.\n", i + 1); return -2;
    }
    return 0;
}