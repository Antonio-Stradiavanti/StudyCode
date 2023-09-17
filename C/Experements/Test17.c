#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Разберемся с ф-цией realloc() и исследуем то как она работает
    int i;
    int* a = malloc(sizeof(int) * 5);

    for (i = 0; i < 5; i++) a[i] = i;
    for (i = 0; i < 5; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    } 

    // realloc получает на вход выделенную область памяти и делает ее в этом случае больше
    // Выведем указатель до и после 
    printf("\nadress before realloc: %d\n", a);
    // Ф-ция не всегда возвращает тот же адрес младшего байта выделенной области, 
    // Доступ к предшествующему блоку памяти теряется.
    a = realloc(a, sizeof(int) * 1000);
    printf("\nadress after realloc: %d\n", a);

    // Все тоже самое.

    printf("\nreallocated:\n");
    for (i = 0; i < 10; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    } 

    free(a);
    return 0;
}