#include <stdio.h>
#include <math.h>
#include <string.h>
#include <math.h>
#define size 50

char Remove( char *src, char *substring, char *dest)
{
	// заметим, что * и ++ - унарные операции над переменными - имеют один и тот же приоритет.
	int i, j=0, k=0, n=0;
	int flag = 0;

	for (i=0; src[i] != '\0'; i++)
	{
		k=i; // количество итераций - длина массива src
		while (src[i] == substring[i])
		//while (*src == *substring)
		{
			i++, j++;
			// если превышаю размер массива-подстроки, которую нужно удалить, то выхожу из цикла.
			if( j = strlen(substring) )
			{
				flag = 1;
				break;
			}
		}
		j = 0; // зануляю размер подстроки, которую нужно удалить для следующей итерации.

		// если вышел 
		if (flag == 0)
		{
			i=k; // <- просто завершаю цикл 
		}
		else
		{
			flag = 0; // <- перехожу на следующую итерацию, ищу вторую такую же подстроку.
		}
		dest[n++] = src[i]; // <- записываю в новую строчку только не те значения, которых нет в параметре 2 (массив символов substring).
	}
	dest[n] = '\0';
	return *dest;
}

void slice(const char *str, char *dest, size_t start, size_t ssl)
{
    strncpy(dest, str + start, ssl);
}

void main()
{
	char S[size] = "", S1[size]="", S2[size]="", S3[size]="", stick[size] = "";
	int i, j;

	// 1. ввести и считать строку
	printf("\nEnter a string S1 : ");
	gets(S);
	strcpy(stick, S);
	size_t sl = strlen(S); 
	// 2. вычислить длину строки и подстрок
	size_t ssl = floor(sl/3);

	printf("\nYou entered: %s; S length = %u, S max_size = %zd bytes; substring length: S1, S2, S3 = %u.\n", S, sl, sizeof S, ssl);
	
	slice(stick, S1, 0, ssl);
	Remove(stick, S1, stick);
	printf("\nS1 = %s, stick1 = %s", S1, stick);

	slice(stick, S2, 0, ssl);
	Remove(stick, S2, stick);
	printf("\nS2 = %s, stick2 = %s", S2, stick);

	slice(stick, S3, 0, ssl);
	Remove(stick, S3, stick);
	printf("\nS3 = %s, stick3 = %s", S3, stick);

	printf("\nRest = %s", stick);
}