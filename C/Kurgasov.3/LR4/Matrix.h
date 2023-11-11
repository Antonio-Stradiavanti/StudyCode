#include<iostream>
#include<string>
#include<vector>
using namespace std;
template <class T>
class Matrix;

template <class T>
ostream& operator<< (ostream& cout, const Matrix<T>&) ;

template <class T>
class Matrix {
  int n, m;
  int size;
  string name;

  vector < vector < T > > mA;

public: 
  // Конструктор по умолчанию
  Matrix () : n{0}, m{0}, size{0}, name{"A"}, mA() {}
  // Конструктор копирования
  Matrix (const Matrix& M) : n{M.n}, m{M.m}, size{M.size}, name{M.name}, mA(M.n, vector<T> (M.m)) {
    for (int i = 0; i < M.n; ++i) {
      for (int j = 0; j < M.m; ++j) {
        // Копируем
        this->mA[i][j] = M.mA[i][j];
      }
    }
  }
  // Нормальный конструктор
  Matrix (int n, int m, int size, string name="A", int a=0, int b=0) : n{n}, m{m}, size{size}, name{name} {
    mA.reserve(n);
    for (int i = 0; i < n; ++i) {
      mA[i].reserve(m);
      for (int j = 0; j < m; ++j)
        mA[i].emplace_back(size, a, b);
    }
  }
  void setName(const string name) { this->name = name; } ;
  
  Matrix<T>& operator= (const Matrix<T>& M) ;
  Matrix<T> operator+ (const char c) ;

  //template <class U>
  friend ostream& operator<< (ostream& cout, const Matrix<T>&) ;

};