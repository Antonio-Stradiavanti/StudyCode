#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char** LetterCombinations(char* digits, int* returnSize) {
  // Сколько дали цифр, столько и будет элементов в подмассивах результирующем массива  
  // Первая проверка : длина строки, если первый символ - \0, то это - пустая строка.
  char alf[26] = "abcdefghijklmnopqrstuvwxyz";
  // VVV Обработка ошибокъ
  size_t len = strlen(digits);
  if (!len || !digits) {
    *returnSize = 0; return NULL;
  }  
  // Нужно перебрать переданную строку и посмотреть из каких чисел она состоит
  char* data[9] = { "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
  int size = 1;
  // Вернем размер результирующего декартова произведения
  for (int i = 0; i < len; ++i) {
    size *= strlen(data[ digits[i] - '1' ]);
  } 
  *returnSize = size;
  // Сформируем массив выходных данных
  char** ret = (char**) malloc(size * sizeof(char*));
  // Выделим память для строк
  for (int i = 0; i < size; ++i){
    ret[i] = (char*) malloc( len+1 );
  }
  for (int i = 0; i < len+1; ++i){
    
  }
  
}
int main() {
  int sz = 0;
  /* char*** tst = LetterCombinations("23", &sz);
   printf("\n");
  for (int i = 0; i < 2; ++i){
    for (int j = 0; j < 3; ++j){
      printf("%s ", tst[i][j]);
    }
    printf("\n");
  } */
  return 0;
}