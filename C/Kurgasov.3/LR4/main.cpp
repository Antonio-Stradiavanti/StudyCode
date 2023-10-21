#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Collection {
  int n;
public: 
  Collection(int n) : n{n} {
  }

  virtual ~Collection() {} 
};
template <class T>
class NumArray : public Collection {
  /* Продумать структуру класса
   * В этом классе должен присутствовать массив определенного типа
   * Нужно иметь возможность изменять количество элементов массива и их тип
   */
  // Массив заданного пользователем размера
  vector<T> A; 
public:
};
class CharArray : public Collection {
  char* cA;
};

template <class T> 
class Matrix {
  int n, m;
  vector< vector<T> > A;

public: 
  /*
   * Перегрузить конструктор копирования
   * Перегрузить бинарные операторы + и - 
   * 
   */
  
  // Переопределим конструктор копирования
  Matrix (const Matrix& M) {
    this->n = M->n; this->m = M->m;

    // Нужно инициализировать вектор нулями
    A(n, vector<T>(m));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        this->A[i][j] = M.A[i][j];
      }
    }
  }

  // Сформируем вектор случайных элементов определенного типа.
  Matrix (int n, int m, int maxVal) : n{n}, m{m} {
    // TODO разобраться с тем как сформировать матрицу сл. зн любого из элементарных типов.
  }
  // Вывод
  void print(const string& name) {
    cout << "<< Матрица " << name << endl;
    for (const auto& rows : this->A) {
      for (const auto& cols : rows) {
        cout << cols << " ";
      }
      cout << endl;
    }
    cout << "<< ---" << endl;
  }

  friend Matrxi operator+ (Matrix, Matrix);
  friend Matrxi operator- (Matrix, Matrix);

  friend Matrix operator+ (Matrix, char);
  friend Matrix operator+ (char, Matrix);  
};

int main() {
  return 0;
}