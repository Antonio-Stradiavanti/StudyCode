#include"numArray.h"
/*  Копирующий оператор присваивания */
template <class T>
numArray<T>& numArray<T>::operator=(const numArray<T>& N) {
  T* p = new T[N.n];
  copy(N.arr, N.arr+N.n, p);
  
  delete[] arr;

  arr = p; n = N.n;

  return *this;
}
template <class T>
numArray<T> numArray<T>::operator+(const char c) {
  int i, j;
  numArray<T> N{n};  
  for(int i = 0; i < n; ++i) {
    N.arr[i] = this->arr[i] + c;
  }
  return N;
}