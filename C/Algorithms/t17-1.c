/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include<string.h>
char ** letterCombinations(char * digits, int* returnSize){
  // Первая проверка : длина строки, если первый символ - \0, то это - пустая строка.
  char alf[26] = "abcdefghijklmnopqrstuvwxyz";
  char* curComb = NULL;
  char **forComb = NULL, **res = NULL;
  if (*digits = '\0') {
    returnSize = 0; return NULL;
  } else {
    // Нужно перебрать переданную строку и посмотреть из каких чисел она состоит

    // Все равно нужен двумерный массив символов, так как его наличие позволит записать материал для перестановок в конкретный массив.

    char *a1 = NULL, *a2 = NULL, *a3 = NULL, *a4 = NULL, *it = digits;
    int len = 0, alfShift = 0;
    while (*(it++) != '\0'){
      len++;
      switch ( *it ){
        case '2' :
          a1 = (char*)malloc(3);
          for (int j = 0; j < 3; ++j){
            a1[j] = alf[alfShift + j];
          }
        break;
        case '3':

      }
    }
  }
}