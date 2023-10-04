#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char* allocp = allocbuf; // первый байт незанятой памяти.
// НЕ эффективно
static char aname[][15] = { "Illegal month", "Jan", "Feb", "Mar" };

char* alloc(int n){
  // i in [0, ALLOCSIZE) ИЛИ i in [0, ALLOCSIZE-1]
  if (allocbuf + ALLOCSIZE - allocp >= n) /* в правой и левой части число число свободных ячеек, а не индексы */ {
    allocp+=n; // И возвращаем адрес первого байта выделенной области
    // Можно сразу вернуть указатель allocp, но тогда я несмогу его увеличить
    return allocp-n;
  } else return 0;
}
void afree(char* p){
  // Выполним обработку ошибок в теле ф-ции
  if (p >= allocbuf && p /*Поскольку p -> адрес, то*/ < allocbuf + ALLOCSIZE) {
    allocp=p;
  }
}
 void mystrcpy(char* s1, char* s2){
  while ((*s1++ = *s2++) != '\0') ;
}
/* mystrcmp (сравниваются коды первых различных символов в переданных строках) : возвр. целое < 0 при s1 < s2, 0 при равенстве и >0 при s1 > s2 */
int mystrcmp(char* s1, char* s2){
  for (; *s1 == *s2; s1++, s2++){
    // дошли до последнего символа строки, то строки действительно равны
    if (*s1 == '\0') return 0;
  }
  // Смотрим какая из строк больше (по алфавиту)
  return *s1 - *s2;
}
/* readlines : ф-ция считывает строки из стандартного потока ввода, возвращает количество поступивших строк */
#define N 4
#define MAXLEN 10
int sreadlines(char (*lines)[MAXLEN], int n){
  int nlines = 0; char line[MAXLEN];
  // Должна накапливать и сохранять символы каждой строки
  while (nlines != N) {
    printf("Введите %d строку : ", nlines);
    fgets(line, MAXLEN, stdin);
    //line[MAXLEN-1] = '\0';
    mystrcpy(lines[nlines++] , line);
    mystrcpy(line, "");
  }
  printf("\n"); return nlines;
}
int dreadlines(char** lines, int n){
  int nlines = 0; char line[MAXLEN];
  // Должна накапливать и сохранять символы каждой строки
  while (nlines != N) {
    printf("Введите %d строку : ", nlines);
    // Всегда записывает нуль терминатор в переданный буфер.
    fgets(line, MAXLEN, stdin); fflush(stdin); printf("\n");
    printf("%d-я строка : %s\n", nlines, line);
    mystrcpy(lines[nlines++], line);
    mystrcpy(line, "");
  }
  printf("\n"); return nlines;
}
/* writelines : процедура выполняет вывод строк в стандартный поток вывода */
void swritelines(char (*lines)[MAXLEN], int nlines){
  for (int i = 0; i < nlines; ++i) {
    printf("%d-я строка : %s\n", i, lines[i]);
  }  
}
void dwritelines(char** lines, int ndlines){
  int i = 0;
  while (ndlines-- > 0) {
    printf("%d-я строка : %s", i++, *lines++);
  }  
}
int main(){
  int n = 10, nslines, ndlines;
  // Такой массив всегда представляется в памяти как одномерный
  /* char lines[N][MAXLEN];
  char** dlines = (char**) malloc(n * sizeof(char*));
  for (int i = 0; i < n; ++i){
    *(dlines+i) = (char*) calloc(MAXLEN, sizeof(char));
  }
  ndlines = dreadlines(dlines, n);
  dwritelines(dlines, ndlines); */
  printf("len(\"\") = %lu\n", strlen("fdfdfd"));
  //nslines = sreadlines(lines, n);
  //swritelines(lines, nslines);

  //printf("%d\n", sizeof(size_t));
}