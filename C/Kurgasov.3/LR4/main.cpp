#include<iostream>
#include<string>
#include<vector>
using namespace std;
template <class T>
class NumArray {
  /* Продумать структуру класса
   * В этом классе должен присутствовать массив определенного типа
   * Нужно иметь возможность изменять количество элементов массива и их тип
   */
  // Массив заданного пользователем размера
  T* A; 
public:
  NumArray(int N) : A(N) {
    // Вызываю генератор случайных чисел    
  }
};
class CharArray {
  int N;
  char* A;
public: 
  CharArray(int N) : N{N} {
    // Создаем случайную строку длиной N
  }
};

template <class T> 
class Matrix {
  int n, m;
  vector< vector<T*> > A;

public: 
  /*
   * Перегрузить конструктор копирования
   * Перегрузить бинарные операторы + и - 
   * 
   */
  
  // Переопределим конструктор копирования
  Matrix (const Matrix& M) : n{M.n}, m{M.m} {this->A = M.A;}

  // Сформируем вектор случайных элементов определенного типа.
  Matrix (int n, int m, int N) : n{n}, m{m}, A(n, vector<T*>(m)) {
    // TODO разобраться с тем как сформировать матрицу сл. зн любого из элементарных типов.
    // Матрица может хранить либо массив символов, либо массив некоторых чисел.
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        A[i][j] = new T()[N];
      }
    }
  }
  ~Matrix() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        delete[] A[i][j];
      }
    }
  }
  void print(const string& name); 

  Matrix& oprator= (const Matrix& M) {
    if (this==&M) return *this;
    
    // Просто выполним поэлементное копирование
    this->n = M.n; this->m = M.m;
    this->A = M.A;

    return *this;
  }

  friend Matrix operator+ (Matrix, Matrix);
  friend Matrix operator- (Matrix, Matrix);

  friend Matrix operator+ (Matrix, char);
  friend Matrix operator+ (char, Matrix);  
};

template<class T> void Matrix<T>::print(const string& name) {
    cout << "<< Матрица " << name << endl;
    for (const auto& rows : this->A) {
      for (const auto& cols : rows) {
        cout << cols << " ";
      }
      cout << endl;
    }
    cout << "<< ---" << endl;
}

int main() {
  return 0;
}