#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<ctime>
#include<exception>
#include<iomanip>
using namespace std;
class Matrix {
private:
  int** matrix;
  int rows, cols, maxVal;

  void genMatrix() {
    random_device gen;
    uniform_int_distribution<int> intDistr(0, maxVal);

    if (matrix == nullptr) {
      matrix = new int* [rows];
      for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
      }
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        matrix[i][j] = intDistr(gen);
      }
    }
  }

public:
  Matrix() : rows{}, cols{}, maxVal{} {
    matrix = nullptr;
  }
  // Конструктор
  Matrix(int rows, int cols) : rows(rows), cols(cols), maxVal(0) {
    try {
      matrix = new int* [rows];
      for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
      }
    } catch(bad_alloc& e) {
      cout << "[ ! ] В конструкторе с 2-мя параметрами произошла фатальная ошибка при попытке выделить память см. детали :\n" << e.what() << endl;
    }
  }
  // Копирующий конструктор, вызывает конструктор по-умолчанию.
  Matrix(const Matrix& m2) {
    //Просто обычный констурктор, который используется при инициализации копированием.    
    this->rows = m2.rows;
    this->cols = m2.cols;
    this->maxVal = m2.maxVal;

    try {
      this->matrix = new int* [this->rows];
      for (int i = 0; i < this->rows; i++) {
        this->matrix[i] = new int[this->cols];
      }

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          this->matrix[i][j] = m2.matrix[i][j];
        }
      }
    } catch(bad_alloc& e) {
      cout << "[ ! ] В копирующем конструкторе произошла фатальная ошибка при попытке выделить память см. детали :\n" << e.what() << endl;
    }
  }
  Matrix(int rows, int cols, int maxVal) : rows(rows), cols(cols), maxVal(maxVal) {
    //uniform_real_distribution<double> realDistr(0, 1);
    try {
      
      genMatrix();

    } catch (bad_alloc& e) {
      cout << "[ ! ] В конструкторе c 3-мя параметрами произошла фатальная ошибка при попытке выделить память см. детали :\n" << e.what() << endl;
    }
  }
  ~Matrix() {
    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  Matrix& operator=(const Matrix& m1);

  struct MatrixMultiplicationException : public exception {
    int cols, rows;

    MatrixMultiplicationException(int cols, int rows) : cols{ cols }, rows{ rows } { }

    const char* what() noexcept {
      return "[ Возникло исключение! ] Невозможно выполнить произведение матриц, так как : количество столбцов первой матрицы не совпадает с количеством строк второй.\n";
    }
  };
  struct MatrixSumException : public exception {
    // Переопределяем виртуальную ф-цию what
    // Возвращает изменяемый указатель на неизменяемый массив символов. 
    
    const char* what() noexcept {
      // Возвращает описание исключения
      return "[ Возникло исключение! ] Нельзя складывать/вычитать матрицы с разным числом строк и столбцов.\n";
    }
  };
  struct notNumberException : public exception {
    const char* what() const noexcept { return "[ Возникло исключение! ] Вы ввели некорректные входные данные, строку нельзя преобразовать в число.\n"; }
  };


  friend Matrix operator* (const Matrix&, const Matrix&);
  friend Matrix operator* (const Matrix&, const double);

  friend Matrix operator- (const Matrix&, const Matrix&);

  friend Matrix operator+ (const Matrix& m1, const Matrix& m2);
  friend istream& operator>>(istream& cin, Matrix& m);
  friend ostream& operator<<(ostream& cout, Matrix& m);
};

