#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;
namespace N {

  template <class T> 
  class numArray;

  template <class U> 
  ostream& operator<< (ostream& os, const numArray<U>& N) ;

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
      std::copy(A1.arr, A1.arr+A1.n, arr); 
    }
    ~numArray() { delete[] arr; }

    numArray<T>& operator= (const numArray<T>& N) {
      T* p = new T[N.n];
      n = N.n;

      std::copy(N.arr, N.arr+N.n, p);
      
      if (arr != nullptr)
        delete[] arr;

      arr = p;

      return *this;
    }
    
    numArray<T> operator+ (const char c) {
      int i, j;
      numArray<T> N{n};  
      for(int i = 0; i < n; ++i) {
        N.arr[i] = this->arr[i] + c;
      }
      return N;
    }

    /* Вывод содержимого множества в стандартный поток */
    template <class U> 
    friend ostream& operator<< (ostream& os, const numArray<U>& N) ; 
  };

  template <class U>
  ostream& operator<< (ostream& os, const numArray<U>& N) {
    int i;

    if (N.arr != nullptr) {
      os << "[ ";
      for (i = 0; i < N.n-1; ++i)
        os << N.arr[i] << ", ";
      os << N.arr[i] << " ]";
    } else {
      os << "[ - ]";
    }

    return os;
  }
}

