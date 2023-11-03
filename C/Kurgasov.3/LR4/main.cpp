#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;

template <class T>
class NumArray {
  int n;
  T* arr; 

  uniform_int_distribution<int> disInt;
  uniform_real_distribution<float> disFloat;
  random_device gen;

public:
  NumArray() : n{}, arr{nullptr} {}
  NumArray(int n, int a=0, int b=0) : n{n}, disInt(a, b), disFloat(0.0, 1.0), arr{new T[n]} {

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
  NumArray(const NumArray<T>& A1) : n{A1.n}, arr{new T[A1.n]} { 
    copy(A1.arr, A1.arr+A1.n, arr); 
  }
  ~NumArray() { delete[] arr; }
  void print() {
    int i;
    if (!n) {
      cout << "[ ]";
    } else {
      cout << "[ ";
      for (i = 0; i < n-1; ++i)
        cout << arr[i] << ", ";
      cout << arr[i] << " ]";
    }
  }
  NumArray<T>& operator= (const NumArray<T>& A1) {
    T* p = new T[A1.n];
    copy(A1.arr, A1.arr+A1.n, p);
    
    delete[] arr;

    arr = p; n = A1.n;

    return *this;
  }
  NumArray<T> operator+ (const char c) {
    int i, j;
    NumArray<T> A{n};  
    for(int i = 0; i < n; ++i) {
      A.arr[i] = this->arr[i] + c;
    }
    return A;
  }
};

class Matrix {

};
/* Ф-ция high : Находит наибольшее значение в массиве, элементы которого принадлежат интервалу адресов [first, last) ; T должен быть базовым типом */
template <class T> T* high(T* first, T* last) {
  T h = -1 ; T* high ;
  // first == last
  // или хотя бы один из переданных указателей - 0.
  for (T* p = first; p != last; ++p) {
    if (h < *p) {
      high = p ; h = *p ;
    }
  }
  return high;

}

int main() {

  int n = 10;
  
  /* vector< NumArray<float> >  tst ;
  // Выделяем неинециализированную область памяти.
  tst.reserve(n);
  for (int i = 0; i < n; ++i) {
    tst.emplace_back(10, 0, 10);
  } */
  
  /* vector< NumArray<float> >  tst(n, NumArray<float>{10, 0, 10}) ;

  for (int i = 0; i < n; ++i) { 
    tst.at(i).print(); cout << endl; 
  }

  for (int i = 0; i < n; ++i) { 
    tst.at(i) = tst.at(i) + 'c';
  }

  cout << "\n---" << endl;
  
  for (int i = 0; i < n; ++i) { 
    tst.at(i).print(); cout << endl; 
  } */
  
  vector <int> t0 {10, 15, 14, 13} ;
  vector <int> tc (t0.begin(), t0.begin() + 3);

  for (const auto& it : tc ) {
    cout << it << " ";
  } 
  cout << "\n" << endl;

  vector < vector < NumArray< float > > > tst(n, vector< NumArray< float > >( n, NumArray< float >{10, 0, 10} ) ) ;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      tst[i][j].print(); cout << ", ";
    }
    cout << endl;
  }

  //NumArray <float> ** tst = new NumArray <float> *;


  //NumArray<float> t0{10, 0, 100}, t1{};
  //t0.print();
  //t1 = t0;
  //cout << "\n---" << endl;
  //t1.print();

  return 0;
}