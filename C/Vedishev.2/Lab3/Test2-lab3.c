#include <stdio.h>
#include <stdbool.h>

#define FILEMANE_SIZE 1024
#define MAX_LINE 2048

int main()
{
    FILE* f;
    char filename[FILEMANE_SIZE];
    char buffer[MAX_LINE];

    int readLine = 0, curLine = 1;
    bool keepReading = true;

    printf("File : ");
    scanf("%s", filename);

    printf("Read line : ");
    scanf("%d", &readLine);

    f = fopen(filename, "r");
    if (f == NULL) 
    {
        printf("Error opening file.\n"); return 1;
    }
    do
    {
        fgets(buffer, MAX_LINE, f);

        if (feof(f))
        {
            keepReading = false;
            printf("File %d lines.\nCouldn't find line %d.\n", curLine-1, readLine);
        }
        else if (curLine == readLine) 
        {
            keepReading = false;
            printf("Line:\n%s", buffer);
        }
        curLine++;
    } while (keepReading == true);

    fclose(f);

    return 0;
}