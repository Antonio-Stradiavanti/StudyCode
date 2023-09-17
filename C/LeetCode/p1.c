#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
typedef struct ListNode {
  int val;
  struct ListNode* next;
} ListNode ;
// VVV
void printVec(int* vec, int vecSize, char* vecName){
  printf("%s[%d] : [ ", vecName, vecSize);
  int i;
  for (i = 0; i < vecSize-1; i++){
    printf("%d, ", vec[i]);
  }
  printf("%d ]\n", vec[i]);
}
// T
char* makeStrFromVec(int* vec, int vecSize){
  char* str = (char*)malloc(vecSize+1);
  int j, k = 0;
  // Строку нужно запонить с конца.
  for (j = vecSize-1; j >= 0; j--) {
    *(str+k) = vec[j] + 48;
    k++;
  }
  *(str+k) = '\0';
  return str;
}

int main(){

  // Реализовать простой односвязный список, воспользоваться примерами решения задач в течение семестра, решаю задачи с leet code сначала в vs code, потом непосредственно выкладываю и при необходимости корректирую решение на сайте. 

  srand(time(NULL));
  int vecF[] = {2, 4, 3};
  int vecS[] = {5, 6, 4};
  
  
  int lenF = 3, lenS = 3;
  
  //while (vecF[++lenF] != 999);
  //while (vecS[++lenS] != 999);
  
  printVec(vecF, lenF, "vecF");
  printVec(vecS, lenS, "vecS");
  
  // Сформируем массивы символов из массивов чисел
  char* ptr = NULL;
  char *strF = makeStrFromVec(vecF, lenF), *strS = makeStrFromVec(vecS, lenS);

  // Преобразуем оба массива символов в числа
  long int resF = strtol(strF, &ptr, 10), resS = strtol(strS, &ptr, 10);
  // Вычислим сумму
  long int res = resF + resS;
  
  printf("полученное число 1 : %ld;\nполученное число 2 : %ld;\nСумма : %ld;\n", resF, resS, res);
  

  // Преобразуем сумму в строку

  // Размер строки, содержащей число, которое нужно поразрядно записать в массив.
  char* resStr = (char*)malloc( (int)(ceil(log10(res))+1));
  sprintf(resStr, "%ld", res);
  fprintf(stdout, "Строка : %s\n", resStr);
  // Теперь из строки получим массив
  int resVSize = strlen(resStr);
  int j = 0, *resV = (int*)malloc(resVSize * sizeof(int));
  for (int i = resVSize-1; i >= 0; i--) {
    // strlen -> возвращает ровное фактическое число символов в массиве символов.
    *(resV+j++) = *(resStr+i) - 48;
  }
  printVec(resV, resVSize, "resV");
  free(strF); free(strS); free(resStr); free(resV);

}