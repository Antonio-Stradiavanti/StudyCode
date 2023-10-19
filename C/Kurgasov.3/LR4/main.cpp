#include<iostream>
#include<string>
#include<vector>
using namespace std;
template <typename T>
class Array {

};
class CharArray {
  int size;
  char* cA;
};
template <class T> 
class Matrix {
  int n, m;
  // Типы элементов матрицы : Множество, массив символов.
  vector< vector<T> > A;
  char* cA;
};
int main() {
  return 0;
}