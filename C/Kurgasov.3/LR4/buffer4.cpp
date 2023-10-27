#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<ctime>
#include<exception>
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
  NumArray<T>* operator= (const NumArray<T>& A1) {
    this->n = A1.n;
    delete[] this->A;

    this->A = new T[n]{};

    for (int i = 0; i < n; ++i) {
      this->A[i] = A1.A[i];
    }

    return this;
  }
  template<class U> friend NumArray<U>* operator+ (const NumArray<U>& A1, const NumArray<U>& A2);
};

template<class U> NumArray<U>* operator+ (const NumArray<U>& A1, const NumArray<U>& A2) {
  int i, j;
  NumArray<U>* A;
  if (A1.n <= A2.n) {
    A = new NumArray<U>{A2.n};

    for (i = 0; i < A1.n; ++i) A->A[i] = A1.A[i] + A2.A[i];
    for (j = i; j < A2.n; ++j) A->A[j] = A2.A[j];
  } else {
    A = new NumArray<U>{A1.n};
    
    for (i = 0; i < A2.n; ++i) A->A[i] = A1.A[i] + A2.A[i];
    for (j = i; j < A1.n; ++j) A->A[j] = A1.A[j];
  }
  return A;
}

class CharArray {
  int n;
  char* A;
  uniform_int_distribution<int> disInt;
  random_device gen;
public: 
  CharArray(int n, ...) : n{n}, disInt(0, 51) {
    
    char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    A = new char[n+1]{};

    for (i = 0; i < n; ++i) A[i] = abc[ disInt(gen) ]; 
    A[i] = '\0';
  }
  ~CharArray() { delete[] A; }
  void print() { cout << "\"" << A << "\""; }
};

template <class T> 
class Matrix {
  int n, m;
  int size;
  vector< vector< T* > > A;

public: 
  Matrix (const Matrix& M) : n{M.n}, m{M.m} {this->A = M.A;}

  Matrix (int n, int m, int size, int a=0, int b=0) : n{n}, m{m}, size{size}, A( n, vector< T* >(m) ) {
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

  void print(const string& name) {
    cout << "<< Матрица " << name << endl;
    int i, j;

    for (i = 0; i < n; ++i) {
      cout << i+1 << ". ";
      for (j = 0; j < m-1; ++j) {
        A[i][j]->print(); cout << ", ";
      }
      A[i][j]->print(); cout << ";" << endl;
    }
    cout << "<< ---" << endl;   
  }

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

/* template<class T> Matrix<T> operator+(const Matrix<T>& M1, const Matrix<T>& M2) {
  // Если размер не совпадает, то генерируем исключение
  if (M1.n != M2.n || M1.m != M2.m) throw MatrixSumException{};
  // Нужно вызвать соответствующий перегруженный оператор для элементов матрицы.
  Matrix<U> M(M1.n, M1.m, M1.size);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      // M[i][j] -> указатель на тип T.
      M[i][j] = M1[i][j] + M2[i][j]
    }
  }      
} */

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
 
  //Matrix< NumArray<int> > tst{5, 5, 10};
  //tst.print("A");
  
  NumArray<int> *t0 = new NumArray<int>{10, 0, 100}, *t1 = new NumArray<int>{5, 0, 100}, *t2 = new NumArray<int>{5, 0, 100};
  t0->print();
  t1->print();
  
  t2 = *t0+*t1;
  t2->print();

  
  //tstMatrix< NumArray<int> > tst{5};
  //tstMatrix< CharArray > tst{5};
  //tst.print();

  return 0;
}