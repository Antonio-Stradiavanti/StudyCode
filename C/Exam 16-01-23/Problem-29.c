#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// strtok, strlen, strchr

int largest_word(char *s)
{
    int len = strlen(s); // длина строки
    int count = 0, max = -1;
    // символы которые не являются словами:
    char nonwords[] = " .,;\n\t\r";
    
    int i = 0;
    while (i < len)
    {
        count = 0; // длина слова
        // циклы проходят по словам и считают длину каждого    
        while (i < len)
        {
            // проверка на наличие в строке запрещенных символов
            if (strchr(nonwords, s[i]) != NULL)
            {
                break;
            }
            i++;
            count++;
        } 

        if (count > max) max = count;

        while (i < len)
        {
            if (strchr(nonwords, s[i]) == NULL) break;
            i++;
        } // скипаю эти символы, чтобы найти ноовое слово
    }
    return max;
}

void main()
{  
    char str[100];

    printf("Enter the string: ");
    gets(str);
    printf("You string: %s\n", str);
    printf("Answer: %d", largest_word(str));

}

