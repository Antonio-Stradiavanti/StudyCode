#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;
template <class U>
class NumArray {
  /* Продумать структуру класса
   * В этом классе должен присутствовать массив определенного типа
   * Нужно иметь возможность изменять количество элементов массива и их тип
   */
  // Массив заданного пользователем размера
  int n;
  U* A; 
public:
  NumArray(int n, int a, int b) : n{n} {
    random_device gen; uniform_int_distribution<int> disInt(a, b);
    uniform_real_distribution<float> disFloat(0.0, 1.0);

    A = new U[n]{};
    
    for (int i = 0; i < n; ++i) {
      A[i] = disInt(gen) + disFloat(gen);
    }
  }
  ~NumArray() { delete[] A; }
  void print() {
    cout << "[ ";
    for (int i = 0; i < n-1; ++i)
      cout << A[i] << ", ";
    cout << A[i] << " ]" << endl;
  }   
};
class CharArray {
  int n;
  char* A;
public: 
  CharArray(int n) : n{n} {
    mt19937 rd(time(NULL));

    char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    A = new char[n+1]{};

    for (i = 0; i < n; ++i) A[i] = abc[ rd()%52 ]; 
    A[i] = '\0';
  }
  void print() { cout << "\"" << A << "\"" << endl; }
  ~CharArray() { delete[] A; }
};

template <class U> 
class Matrix {
  int n, m;
  vector< vector<U*> > A;

public: 
  /*
   * Перегрузить конструктор копирования
   * Перегрузить бинарные операторы + и - 
   * 
   */
  
  // Переопределим конструктор копирования
  Matrix (const Matrix& M) : n{M.n}, m{M.m} {this->A = M.A;}

  Matrix (int n, int m, int size, int num, int a=0, int b=0) : n{n}, m{m}, A(n, vector<U*>(m)) {
    // TODO разобраться с тем как сформировать матрицу сл. зн любого из элементарных типов.
    // Матрица может хранить либо массив символов, либо массив некоторых чисел.
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        // Вызываю конструктор по умолчанию для каждого из элементов.
        A[i][j] = new U{size, a, b};
      }
    }
  }

  ~Matrix() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        delete A[i][j];
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

template<class U> void Matrix<U>::print(const string& name) {
    cout << "<< Матрица " << name << endl;
    for (int i = 0; i < this->n; ++i) {
      printf("%d. ", i);
      for (int j = 0; i < this->m-1; ++j) {
        
      }
    }
    cout << "<< ---" << endl;
}

void menu() {
  
}

int main() {
  return 0;
}