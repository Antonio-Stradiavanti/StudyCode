#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<ctime>
#include<exception>
using namespace std;
class Matrix{
private:
  mt19937 mt;
  int** matrix;
  int n, m, maxVal;
public:
  // Конструктор
  Matrix(int n, int m) : n(n), m(m){
    maxVal=0;
    matrix = new int*[n];
    for (int i = 0; i < n; i++){
      matrix[i] = new int[m];
    }
  }
  Matrix(int n, int m, int maxVal) : n(n), m(m), maxVal(maxVal) {
    mt.seed(time(nullptr));
    matrix = new int*[n];
    for (int i = 0; i < n; i++){
      matrix[i] = new int[m];
    }
    for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
        matrix[i][j] = mt() % maxVal;
      }
    }
  } // Деструктор
  ~Matrix(){
    for (int i = 0; i < n; i++){
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  Matrix operator + (Matrix m2);
  void operator = (Matrix m2);
  void print();
};
struct MatrixSumException : public exception {
  // Переопределяем виртуальную ф-цию what
  // Возвращает изменяемый указатель на неизменяемый массив символов. 
  const char* what () {
    // Возвращает описание исключения
    return "Возникло исключение! Нельзя складывать матрицы с разным числом строк и столбцов.";
   }
};
void Matrix::print(){
  string out;
  for (int i = 0; i < n; i++){
    out += "| ";
    for (int j = 0; j < m; j++){
      out = out + string(floor(log10(maxVal) + 1) - floor(log10(!matrix[i][j] ? 1 : matrix[i][j]) + 1), ' ') + to_string(matrix[i][j]) + " ";
    }
    out += "|\n";
  }
  cout << out << endl;
}
void Matrix::operator=(Matrix m2){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      matrix[i][j] = m2.matrix[i][j];
    }
  }
}
Matrix Matrix::operator+(Matrix m2){
  // Можно складывать только одинаковые по размеру матрицы
  //if (m2.n != n && m2.m != m){
    // cout << "! Нельзя складывать матрицы разных размеров.";
    // Нужно вызвать исключение c перегруженным конструктором.
    //throw MatrixSumException();
  //} else {
    //cout << "Пока все спокойно" ;
    //return new Matrix(10, 10, 100);
  //}
  // Нужно наверное его создать в динамической памяти ?
  Matrix res(n, m);
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      res.matrix[i][j] = this->matrix[i][j] + m2.matrix[i][j]; 
    }
  }
  return res;
}
int main(){

  Matrix m1(5, 5, 99), m2(5, 5, 99), m3(5, 5);
  try {
    // нужно переопределить копирующий конструктор
    cout << "Слагаемое 1" << endl;
    m1.print();
    cout << "Слагаемое 2" << endl;
    m2.print();
    cout << "Сумма" << endl;
    m3 = m1 + m2;
    m3.print();
  } catch (MatrixSumException mse) {
    cout << "! Невозможно выполнить операцию, т.к : " << endl;
    cout << mse.what();
  }
  return 0;
}