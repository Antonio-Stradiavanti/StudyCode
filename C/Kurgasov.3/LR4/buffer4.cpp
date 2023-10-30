#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<ctime>
#include<exception>
#include<cstring>
using namespace std;
template <class T>
class NumArray {
  int n;
  T* A; 
  uniform_int_distribution<int> disInt;
  uniform_real_distribution<float> disFloat;
  random_device gen;
public:
  NumArray(int n, int a=0, int b=0) : n{n}, disInt(a, b), disFloat(0.0, 1.0) {
    A = new T[n]{};

    if (!a && !b) {
      for (int i = 0; i < n; ++i) {
        A[i] = 0;
      }
    } else {
      for (int i = 0; i < n; ++i) {
        A[i] = disInt(gen) + disFloat(gen);
      }
    }
  }
  ~NumArray() { delete[] A; }
  void print() {
    int i;
    
    cout << "[ ";
    for (i = 0; i < n-1; ++i)
      cout << A[i] << ", ";
    cout << A[i] << " ]";
  }
  NumArray<T>* operator= (const NumArray<T>* A1) {
    this->n = A1->n;
    delete[] this->A;

    this->A = new T[n]{};

    for (int i = 0; i < n; ++i) {
      this->A[i] = A1->A[i];
    }

    return this;
  }
  template<class U> friend NumArray<U>* operator+ (const NumArray<U>& A1, const char c);

};

template<class U> NumArray<U>* operator+ (const NumArray<U>& A1, const char c) {
  int i, j;
  NumArray<U>* A = new NumArray<U>{A1.n};

  for(int i = 0; i < A->n; ++i) {
    A->A[i] = A1.A[i] + c;
  }
  /* if (A1.n <= A2.n) {

    for (i = 0; i < A1.n; ++i) A->A[i] = A1.A[i] + A2.A[i];
    for (j = i; j < A2.n; ++j) A->A[j] = A2.A[j];
  } else {
    A = new NumArray<U>{A1.n};
    
    for (i = 0; i < A2.n; ++i) A->A[i] = A1.A[i] + A2.A[i];
    for (j = i; j < A1.n; ++j) A->A[j] = A1.A[j];
  } */
  return A;
}


class CharArray {
  int n;
  char* A;
  uniform_int_distribution<int> disInt;
  random_device gen;
public: 
  CharArray() : n{}, A{nullptr} {}
  CharArray(int n, ...) : n{n}, disInt(0, 51) {
    
    char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    A = new char[n+1]{};

    for (i = 0; i < n; ++i) A[i] = abc[ disInt(gen) ]; 
    A[i] = '\0';
  }
  ~CharArray() { delete[] A; }
  void print() { cout << "\"" << A << "\""; }
  friend CharArray* operator+ (const CharArray& A1, const char* c);
  friend CharArray* operator+ (char* c, const CharArray& A1);


};
CharArray* operator+ (const CharArray& A1, const char* c) {
  CharArray* A = new CharArray{};

  A->A = strcat(A1.A, c);

  return A;
}
CharArray* operator+ (char* c, const CharArray& A1) {
  int lc = strlen(c);
  CharArray* A = new CharArray{};
  A->n = A1.n + lc + 1;
  A->A = new char[A->n]{};

  //A->A = strcat(c, A1.A);
  // c -> 2байта

  int i, j = 0;

  for (i = 0 ; i < lc; ++i) A->A[i] = c[i];
  for (i = lc; i < A->n; ++i) A->A[i] = A1.A[j++];
 
 A->A[i] = '\0';

  return A;
}


template <class T> 
class Matrix {
  int n, m;
  int size;

  string name;
  vector< vector< T* > > A;

public: 
  Matrix (const Matrix& M) : n{M.n}, m{M.m} {this->A = M.A;}

  Matrix (int n, int m, int size, name = "A", int a=0, int b=0) : n{n}, m{m}, size{size}, name{name}, A( n, vector< T* >(m) ) {
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        // Вызываю конструктор по умолчанию для каждого из элементов.
        A[i][j] = new T{size, a, b};
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

  template<class U> friend Matrix<U> operator+(const Matrix<U>& M1, const char* c)
  template <class U> friend ostream& operator<< (ostream& cout, const Matrix<U>& M);
  //template <class U> friend Matrix& operator+ (const Matrix& M1, const Matrix& M2);

};
struct MatrixSumException : public exception {
  // Переопределяем виртуальную ф-цию what
  // Возвращает изменяемый указатель на неизменяемый массив символов. 
  const char* what () {
    // Возвращает описание исключения
    return "<! Нельзя складывать матрицы с разным числом строк и столбцов.";
   }
};
template <class U> ostream& operator<< (ostream& cout, const Matrix<U>& M) {
  cout << "<< Матрица " << M.name << endl;
  int i, j;

  for (i = 0; i < M.n; ++i) {
    cout << i+1 << ". ";
    for (j = 0; j < M.m - 1; ++j) {
      A[i][j]->print(); cout << ", ";
    }
    A[i][j]->print(); cout << ";" << endl;
  }
  cout << "<< ---" << endl;  
  return cout;  
}

template<class U> Matrix<U> operator+(const Matrix<U>& M1, const char* c) {
  // Если размер не совпадает, то генерируем исключение
  if (M1.n != M2.n || M1.m != M2.m) throw MatrixSumException{};
  // Нужно вызвать соответствующий перегруженный оператор для элементов матрицы.
  Matrix<U> M(M1.n, M1.m, M1.size);

  for (int i = 0; i < M.n; ++i) {
    for (int j = 0; j < M.m; ++j) {
      // M[i][j] -> указатель на тип T.
      M[i][j] = *M1[i][j] + c;
    }
  }   

  return M;   
}

/* template <class T>
class tstMatrix {
  int n, m;
  vector< T* > A;
public: 
  tstMatrix(int n) : n{n}, m{}, A(n) {
    for (int i = 0; i < n; ++i) A[i] = new T(10, 10, 100);
  }
  void print() {
    int i;
    for (i = 0; i < n-1; ++i) {
      A[i]->print(); cout << ", ";
    }
    A[i]->print(); cout << ";" << endl;
  }
  ~tstMatrix() {
    for (int i = 0; i < n; ++i) delete A[i];
  }
}; */

int main() {
 
  Matrix< NumArray<int> > M{5, 5, 3};

  cout << M;
  
  //tstMatrix< NumArray<int> > tst{5};
  //tstMatrix< CharArray > tst{5};
  //tst.print();

  return 0;
}