#include<iostream>
#include<string>
#include<vector>
using namespace std;
/* class Collection {
  int n;
  virtual ~Collection() {}
};
template <typename T>
class NumArray : public Collection {
  vector<T> A;
};
class CharArray : public Collection {
  char* cA;
};
template <class T> 
class Matrix {
  int n, m;
  // Типы элементов матрицы : Множество, массив символов.
  vector< vector<T> > A;
  char* cA;
public:   
}; */
int main() {
  int* a = new int(5);
  // *a = 5
  int* b = a; (*b)++; b++;
  printf("%d %d\n", *a, *b);
  return 0;
}