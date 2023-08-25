#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){

  //srand(time(NULL));
  int a1[100];
  int a2[100];
  for (int i = 0; i < 100; i++){
    a1[i] = 999; a2[i] = 999;
  }
  for (int i = 0; i < rand()%100; i++){
    a1[i] = rand() % 999;
  }
  for (int i = 0; i < rand()%100; i++){
    a2[i] = rand() % 999;
  }
  
  int lenF = 0, lenS = 0;
  
  while (a1[++lenF] != 999);
  while (a2[++lenS] != 999);

  printf("a1 : [ ");
  for (int i = 0; i < 100; i++){
    printf("%d, ", a1[i]);
  }
  printf(" ];\n");
  int p = 10;
  printf("a1 = %-*d, a2 = %d\n", p, lenF, lenS);

}