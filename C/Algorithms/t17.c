#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
  char alf[26] = "abcdefghijklmnopqrstuvwxyz";
  char** a = (char**)malloc(3 * sizeof(char*));
  int i, j, subarrLen[3] = {3, 4, 5};
  int lenSum = 0;

  for (i = 0; i < 3; ++i){
    // Используется накопительная сумма размеров под-массивов от 1 до n; 
    a[i] = (char*)malloc( subarrLen[i] );
    for (j = 0; j < subarrLen[i]; ++j){
      printf("here\n");
      // Выхожу за границы выделенной памяти.
      **(a) = *(alf+ lenSum + j);
    }
    printf("here2\n");
    lenSum+=subarrLen[i];
  }

  /* printf("\n");
  for (i = 0; i < 3; ++i){
    for (j = 0; j < subarrLen[i]; ++j){
      printf("%c ", a[i][j]);
    }
    printf("\n");
  } */

  return 0;
}