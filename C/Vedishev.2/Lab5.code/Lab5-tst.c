#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int main()
{
    int i = 0; char *N, buf[1024+1] = "";
    printf("Введите строку : ");
    //fgets(buf, 1024, stdin); 
    scanf("%1024s", buf);
    N = strdup(buf);
    FILE* f; f = fopen(buf, "r");
    printf("%d\n", fscanf(f, "%d ", &i));
	fclose(f); free(N);
    return 0;
}