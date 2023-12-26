#include"Matrix.h"

Matrix& Matrix::operator=(const Matrix& m1) {
  this->rows = m1.rows;
  this->cols = m1.cols;
  this->maxVal = m1.maxVal;

  // Очистить память и заново выделить.
  if (this->matrix != nullptr) {
    for (int i = 0; i < rows; ++i) {
      delete[] this->matrix[i];
    }
    delete[] this->matrix;
  }
  try {
    this->matrix = new int* [this->rows];
    for (int i = 0; i < this->rows; i++) {
      this->matrix[i] = new int[this->cols];
    }

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        this->matrix[i][j] = m1.matrix[i][j];
      }
    }
  } catch (bad_alloc& e) {
    cout << "[ ! ] В копирующем операторе присваивания произвошла фатальная ошибка при попытке выделить память" << e.what() << endl;
  }
  return *this;
}

// Ввод матрицы руками
istream& operator>>(istream& cin, Matrix& M) {
  label:
  try {
    cout << "\n***\n\n1. Введите размерность матрицы :" << endl;
    cout << "> n = "; cin >> M.rows; if (cin.fail()) throw Matrix::notNumberException();
    cout << "> m = "; cin >> M.cols; if (cin.fail()) throw Matrix::notNumberException();
    
    int c;
    label1:
    cout << "2. Выберите режим ввода значений : {\n  1 -> буду вводить значения вручную,\n  2 -> сформировать матрицу случайных чисел\n}" << endl;
    cout << "> "; cin >> c; if (cin.fail()) throw Matrix::notNumberException();
    switch (c) {
    case 1:
      cout << "3. Сформируем матрицу :" << endl;
      for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
          cout << "> m[" << i << "][" << j << "] : "; cin >> M.matrix[i][j];
        }
      }
      break;
    case 2:
      cout << "< Введите максимальное значение в матрице :" << endl;
      cout << "> maxVal = "; cin >> M.maxVal; if (cin.fail()) throw Matrix::notNumberException();
      M.genMatrix();
      break;
    default:
      cout << "Такого режима нет, выберите подходящий режим." << endl;
      goto label1;
    }

    cout << "\n\n***\n" << endl;
  } catch (Matrix::notNumberException& e) {
    cout << e.what() << "\n Попробуйте еще раз." << endl;
    goto label;
  }
  return cin;
}
template < class T >
int numDigits(T num) {
  int dig = 0;

  if (num < 0) dig = 1;
  while (num) {
    num /= 10; dig++;
  }

  return dig;
}
ostream& operator<<(ostream& cout, Matrix& A) {
  // Перед печатью нужно определить максимальное значение.
  int i, j; //int maxVal = -1;
  /*for (i = 0; i < A.rows; i++) {
    for (j = 0; j < A.cols; j++) {
      if (A.matrix[i][j] > maxVal) maxVal = A.matrix[i][j];
    }
  }
  A.maxVal = maxVal;*/
  int maxValueLen = numDigits(A.maxVal) + 1;
  for (i = 0; i < A.rows; i++) {
    cout << "| " ;
    for (j = 0; j < A.cols; j++) {
      cout << left << setw(maxValueLen) << A.matrix[i][j] << " ";
    }
    cout << "|\n";
  }
  cout << endl; 
  return cout;
}

Matrix operator+(const Matrix& A, const Matrix& B) {
  if (A.rows != B.rows && A.cols != B.cols) {
    throw Matrix::MatrixSumException();
  }

  Matrix C(A.rows, A.cols);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }

  return C;
}

Matrix operator- (const Matrix& A, const Matrix& B) {
  if (A.rows != B.rows && A.cols != B.cols) {
    throw Matrix::MatrixSumException();
  }
  Matrix C(A.rows, B.cols);
  for (int i = 0; i < C.rows; ++i) {
    for (int j = 0; j < C.cols; ++j) {
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }

  return C;
}

Matrix operator* (const Matrix& A, const Matrix& B) {
  if (A.cols != B.rows) {
    throw Matrix::MatrixMultiplicationException(A.cols, B.rows);
  }
  Matrix C(A.rows, A.cols);

  for (int i = 0; i < C.rows; ++i) {
    for (int j = 0; j < C.cols; ++j) {
      C.matrix[i][j] = 0;
      // Либо A.cols, либо B.rows, то есть то что у них совпадает.
      for (int k = 0; k < B.rows; ++k) {
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }

  return C;
}

Matrix operator* (const Matrix& A, const double d){
  Matrix C(A.rows, A.cols);

  for (int i = 0; i < C.rows; ++i) {
    for (int j = 0; j < C.cols; ++j) {
      C.matrix[i][j] = A.matrix[i][j] * /*static_cast<int>(d)*/d;
    }
  }

  return C;
}

void menu() {
  cout << "\n*** Операции над матрицами ***\n" << endl;
  int c;
  cout << "< Введите команду :" << endl; 
  
  string help = "\n### меню\n  1 -> Сумма 2х матриц,\n  2 -> Разность 2х матриц\n  3 -> Произведение 2х матриц\n  4 -> Произвдение матрицы и вещественного числа\n  5 -> Вывести меню программы\n  6 -> Завершить работу программы.\nменю ###\n";

  cout << help << endl;
  try {
    cout << " > "; cin >> c; if (cin.fail()) throw Matrix::notNumberException();
    Matrix A, B, C; 

    switch(c) {
    case 1:
      cin >> A; cin >> B;

      C = A + B;

      cout << "Слагаемое 1 :\n\n" << A;
      cout << "Слагаемое 2 :\n\n" << B;
      cout << "Сумма :\n\n" << C;
      cout << endl;

      break;
    case 2:
      cin >> A; cin >> B;

      C = A - B;

      cout << "Уменьшаемое :\n\n" << A;
      cout << "Вычитаемое :\n\n" << B;
      cout << "Разность :\n\n" << C;
      cout << endl;


      break;
    case 3:
      cin >> A; cin >> B;

      C = A * B;

      cout << "Множитель 1 :\n\n" << A;
      cout << "Множитель 2 :\n\n" << B;
      cout << "Произведение :\n\n" << C;
      cout << endl;


    case 4:
      cin >> A;

      double d;
      cout << "< Введите вещественное число :\n";
      cout << "> d = ";  cin >> d; if (cin.fail()) throw Matrix::notNumberException();

      C = A * d;

      cout << "Множитель 1 :\n\n" << A;
      cout << "Множитель 2 :\n\n" << d << "\n" << endl;
      cout << "Произведение :\n\n" << C;
      cout << endl;

      break;
    case 5:
      cout << help << endl;
      break;
    case 6:
      cout << "< Завершение работы..." << endl;
      return;
    }
  } catch (Matrix::MatrixSumException& e) {
    cout << e.what() << endl;
  } catch (Matrix::MatrixMultiplicationException& e) {
    cout << e.what() << endl;
  }
  catch (Matrix::notNumberException& e) {
    cout << e.what() << endl;
  }
  catch (exception& e) {
    cout << "Что-то пошло не так, см. детали :\n" << e.what() << endl;
  }
}
int main() {
  
  menu();

  return 0;
}