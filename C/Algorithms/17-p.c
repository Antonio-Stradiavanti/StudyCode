#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
char** caertesianProduct(char* A, char* B){
  char** ret = NULL;
  if (*A == '\0' || *B == '\0') return ret;
  int len1 = strlen(A), len2 = strlen(B);
  ret = (char**) malloc(len1 * len2 * sizeof(char*));
}
int main(){
  // Сначала разберемся с цифрами, потом с буквами.
  // Дано исходное множество
  char A[] = "abc", B[] = "efg", C = "hijk", D = "tuv";

  return 0;
}