#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;
template <class T>
class numArray {
  int n;
  T* arr; 

  uniform_int_distribution<int> disInt;
  uniform_real_distribution<float> disFloat;
  random_device gen;

public:
  numArray() : n{}, arr{nullptr} {}
  numArray(int n, int a=0, int b=0) : n{n}, disInt(a, b), disFloat(0.0, 1.0), arr{new T[n]} {

    if (!a && !b) {
      for (int i = 0; i < n; ++i) {
        arr[i] = 0;
      }
    } else {
      for (int i = 0; i < n; ++i) {
        arr[i] = disInt(gen) + disFloat(gen);
      }
    }
  }
  numArray(const numArray<T>& A1) : n{A1.n}, arr{new T[A1.n]} { 
    copy(A1.arr, A1.arr+A1.n, arr); 
  }
  ~numArray() { delete[] arr; }
  
  numArray<T>& operator= (const numArray<T>&) ;
  numArray<T> operator+ (const char c) ;
  template <class U> friend ostream& operator<< (ostream& cout, const numArray<U>& nA) ;
};