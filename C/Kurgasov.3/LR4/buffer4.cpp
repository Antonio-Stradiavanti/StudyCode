#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<ctime>
#include<exception>
#include<cstring>

using namespace std;
template <class T>
class numArray {
  int n;
  T* A; 

  uniform_int_distribution<int> disInt;
  uniform_real_distribution<float> disFloat;
  random_device gen;

public:
  numArray(int n, int a=0, int b=0) : n{n}, disInt(a, b), disFloat(0.0, 1.0), A{new T[n]} {

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
~numArray() { delete[] A; }
void print() {
int i;

    cout << "[ ";
    for (i = 0; i < n-1; ++i)
      cout << A[i] << ", ";
    cout << A[i] << " ]";
  }
  numArray<T>* operator= (const numArray<T>* A1) {
    this->n = A1->n;
    delete[] this->A;

    this->A = new T[n]{};

    for (int i = 0; i < n; ++i) {
      this->A[i] = A1->A[i];
    }

    return this;
  }
  template<class U> friend numArray<U>* operator+ (const numArray<U>& A1, const char c);

};

template<class U> numArray<U>* operator+ (const numArray<U>& A1, const char c) {
  int i, j;
  numArray<U>* A = new numArray<U>{A1.n};

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


class charArray {
  int n;
  char* str;
  
  uniform_int_distribution<int> disInt;
  random_device gen;

public: 
  charArray() : n{}, str{nullptr}, disInt{} {}
  // Создает случайную строку
  charArray(int n, ...) : n{n}, disInt(0, 51), str{new char[n+1]} {
    
    char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    for (i = 0; i < n; ++i) str[i] = abc[ disInt(gen) ]; 
    str[i] = '\0';
  }
  ~charArray() { delete[] str; }

  charArray* operator= (const charArray* const A1);

  void print() { cout << "\"" << str << "\""; }

  friend charArray* operator+ (const charArray& A1, const char c);


};

charArray* charArray::operator= (const charArray* const A1) {
  int i;
  //if (this->n != A1->n) {
  char* p = new char[A1->n+1];
  copy(A1->str, A1->str+A1->n+1, p);
  //p[A1->n] = '\0';

  delete[] str; 
  
  str = p; n = A1->n;
  //str = new char[A1->n+1]; n = A1->n; 
  //}
  
  return this;
}

charArray* operator+ (const charArray& A1, const char c) {
  const int& size = A1.n; int i;

  charArray* A = new charArray[size+2]{};

  for (i = 0; i < size; ++i) A->str[i] = A1.str[i]; 
  A->str[i] = c; A->str[i+1] = '\0';

  return A;
}

/* CharArray* operator+ (char* c, const CharArray& A1) {
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
} */


template <class T> 
class Matrix {
  int n, m;
  int size;

  string name = "A";
  vector< vector< T > > A;

public: 
  Matrix (const Matrix& M) : n{M.n}, m{M.m}, A( M.n, vector< T > (M.m) ) {
    
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        // Копируем
        this->A[i][j] = M.A[i][j];
      }
    }

  }

  Matrix (int n, int m, int size, string name = "A", int a=0, int b=0) : n{n}, m{m}, size{size}, name{name}, A( n, vector< T >(m, {size, a, b}) ) {
   /* for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
      }
    }
     */
  }
  /* ~Matrix() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        delete A[i][j];
      }
    }
  } */

  Matrix<T>& operator= (const Matrix<T>& M);

  template<class U> friend Matrix<U> operator+(const Matrix<U>& M1, const char c);
  template <class U> friend ostream& operator<< (ostream& cout, const Matrix<U>& M);
  //template <class U> friend Matrix& operator+ (const Matrix& M1, const Matrix& M2);
  void setName (string Name) { name = Name; }
};
struct MatrixSumException : public exception {
  // Переопределяем виртуальную ф-цию what
  // Возвращает изменяемый указатель на неизменяемый массив символов. 
  const char* what () {
    // Возвращает описание исключения
    return "<! Нельзя складывать матрицы с разным числом строк и столбцов.";
   }
};

template<class T> Matrix<T>& Matrix<T>::operator= (const Matrix<T>& M) {
  if (this->n != M.n || this->m != M.m){
    // Изменить размер вектора.
    
  }
    this->n = M.n; this->m = M.m;

  // Заново выделить память для вектора.
  // Понять что означает эта запись для вектора
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      this->A[i][j] = M.A[i][j];
    }
  }
  //this->A = M.A;

  return *this;
}

template<class U> Matrix<U> operator+(const Matrix<U>& M1, const char c) {
  // Если размер не совпадает, то генерируем исключение
  //if (M1.n != M2.n || M1.m != M2.m) throw MatrixSumException{};
  // Нужно вызвать соответствующий перегруженный оператор для элементов матрицы.
  Matrix<U> M(M1.n, M1.m, M1.size);

  for (int i = 0; i < M1.n; ++i) {
    for (int j = 0; j < M1.m; ++j) {
      // M[i][j] -> указатель на тип T.
      M.A[i][j] = *(M1.A[i][j]) + c;
    }
  }   

  return M;   
}

template <class U> ostream& operator<< (ostream& cout, const Matrix<U>& M) {
  cout << "<< Матрица " << M.name << endl;
  int i, j;

  for (i = 0; i < M.n; ++i) {
    cout << i+1 << ". ";
    for (j = 0; j < M.m - 1; ++j) {
      M.A[i][j]->print(); cout << ", ";
    }
    M.A[i][j]->print(); cout << ";" << endl;
  }
  
  cout << "<< ---" << endl;  
  return cout;  
}


int main() {
 
  /* Matrix< CharArray > M{5, 5, 5, "A"};
  Matrix< CharArray > M1{M};
  cout << M;
  cout << M1; */
  
  //vector< NumArray<float> > t0(10, {10, 0, 100});
  int n = 10 ; string name = "A";
  vector < vector < int > > t1 (n, vector(n, 5)) ;
  cout << name << " = {" << endl;
  int i, j;
  for (i = 0; i < n ; ++i) {
    cout << "\t[\n\t  №" << i+1 << ": ";
    for (j = 0 ; j < n ; ++j) {
      if (j == n-1 && i != n-1) { 
        cout << t1[i][j] << ";\n\t]," << endl ; 
      } else if (j == n-1 && i == n-1) {
        cout << t1[i][j] << ";\n\t].\n   }" << endl;
      } else { 
        cout << t1[i][j] << ", " ;
      }
    }
  }
  return 0;
}
