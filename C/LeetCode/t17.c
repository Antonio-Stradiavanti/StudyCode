#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// Вывожу массив указателей.
int main(){
  char alf[26] = "abcdefghijklmnopqrstuvwxyz";
  char** a = (char**)malloc(3 * sizeof(char*));
  int i, j, subarrLen[3] = {3, 4, 5};
  int lenSum = 0;

  for (i = 0; i < 3; ++i){
    // Используется накопительная сумма размеров под-массивов от 1 до n; 
    a[i] = (char*)malloc( subarrLen[i] );
    for (j = 0; j < subarrLen[i]; ++j){
      // Выхожу за границы выделенной памяти.
      *( *(a+i) + j) = *(alf+ lenSum + j);
    }
    lenSum+=subarrLen[i];
  }

  printf("\n");
  for (i = 0; i < 3; ++i){
    for (j = 0; j < subarrLen[i]; ++j){
      printf("%c ", a[i][j]);
    }
    printf("\n");
  }
  // Очистить выделенную память !!!
  return 0;
}