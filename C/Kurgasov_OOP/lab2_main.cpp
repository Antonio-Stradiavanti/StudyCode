#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<ctime>
#include<exception>
using namespace std;
mt19937 mt;
class Matrix{
private:
  int** matrix;
  int Rows, Cols, MaxVal;
public:
  // Конструктор
  Matrix(int rows, int cols) : Rows(rows), Cols(cols), MaxVal(0) {
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++){
      matrix[i] = new int[cols];
    }
  }
  // Копирующий конструктор, вызывает конструктор по-умолчанию.
  Matrix(const Matrix& m2){
    //Просто обычный констурктор, который используется при инициализации копированием.    
    this->Rows = m2.Rows;
    this->Cols = m2.Cols;
    this->MaxVal = m2.MaxVal;

    this->matrix = new int*[this->Rows];
    for (int i = 0; i < this->Rows; i++){
      this->matrix[i] = new int[this->Cols];
    }

    for (int i = 0; i < Rows; i++){
      for (int j = 0; j < Cols; j++){
        this->matrix[i][j] = m2.matrix[i][j];
      }
    }
  }
  Matrix(int rows, int cols, int maxVal) : Rows(rows), Cols(cols), MaxVal(maxVal) {
    mt.seed(time(nullptr));
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++){
      matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        matrix[i][j] = mt() % maxVal;
      }
    }
  }  
  ~Matrix(){
    for (int i = 0; i < Rows; i++){
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  friend Matrix operator+(const Matrix& m1, const Matrix& m2);
  friend istream& operator>>(istream& cin, Matrix& m);
  friend ostream& operator<<(ostream& cout, Matrix& m);
};
struct MatrixSumException : public exception {
  // Переопределяем виртуальную ф-цию what
  // Возвращает изменяемый указатель на неизменяемый массив символов. 
  const char* what () {
    // Возвращает описание исключения
    return "Возникло исключение! Нельзя складывать матрицы с разным числом строк и столбцов.";
   }
};
struct UnrecComException : public exception {
  const char* what () {
    return "Возникло исключение! Команда не распознана.";
  }
};
Matrix operator+(const Matrix& m1, const Matrix& m2){
    if (m1.Rows != m2.Rows && m1.Cols != m2.Cols){
      throw MatrixSumException(); 
    }
    Matrix m3(m1.Rows, m1.Cols);
    for (int i = 0; i < m1.Rows; i++){
      for (int j = 0; j < m1.Cols; j++){
        m3.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j]; 
      }
    }
    return m3;
}
// Ввод матрицы руками
istream& operator>>(istream& cin, Matrix& m){
  cout << "< Сформируем матрицу :" << endl;
  for (int i = 0; i < m.Rows; i++){
    for (int j = 0; j < m.Cols; j++){
      cout << "m[" << i << "][" << j << "] : ";  
      cin >> m.matrix[i][j];
    }
  }
  return cin;
}
ostream& operator<<(ostream& cout, Matrix& m){
  // Перед печатью нужно определить максимальное значение.
  int i, j, maxVal = -1;
  for (i = 0; i < m.Rows; i++){
    for (j = 0; j < m.Cols; j++){
      if (m.matrix[i][j] > maxVal) maxVal = m.matrix[i][j];
    }
  }
  m.MaxVal = maxVal;
  for (i = 0; i < m.Rows; i++){
    cout << "| ";
    for (j = 0; j < m.Cols; j++){
      cout << string(to_string(m.MaxVal).size() - to_string(m.matrix[i][j]).size(), ' ') << m.matrix[i][j] << " ";
    }
    cout << "|\n";
  }
  cout << endl; return cout;
}
Matrix getInput(int num){
  int r, n, m, maxVal;
  cout << "< Введите размерность " << num << "й матрицы :" << endl;
  cin >> n; cin >> m;
  cout << "< Выберите режим ввода значений " << num << "й матрицы : {\n\t1 -> буду вводить значения вручную,\n\t2 -> сформировать матрицу случайных чисел\n}" << endl << "> ";
  cin >> r;
  if (r == 1){
    // Ошибка вызвана деструктором, нужно переписать логику копирующего конструктора
    Matrix m1(n, m); cin >> m1; return m1;
  } else if (r == 2){
    cout << "< Введите максимальное число в формируемой матрице." << endl << "> "; cin >> maxVal; 
    // Возвращаю копию исходного объекта, в ходе трансляции этой инструкции может быть опущен вызов конструктора копировния, в нем вся загвоздка
    return Matrix(n, m, maxVal);
  } else {
    throw UnrecComException();
  }
}
void menu(bool& cont){
  cout << "\n*** Сумма Матриц ***" << endl;
  int com;
  cout << "< Введите команду из множества команд : {\n\t1 -> Выполнить сумму 2х матриц,\n\t2 -> Завершить работу программы.\n}" << endl << "> "; cin >> com;
  try{
    if (com == 1){
      Matrix m1 = getInput(1), m2 = getInput(2);
      // Эта инструкция приведет к вызову копирующего конструктора 
      Matrix m3 = m1 + m2;
      cout << "Слагаемое 1" << endl << m1;
      cout << "Слагаемое 2" << endl << m2;
      cout << "Сумма" << endl << m3;    
    } else if (com == 2){
      cout << "< Завершение работы..." << endl;
      cont = false;
    } else {
      throw UnrecComException();
    }  
  } catch (UnrecComException& e) {
    cout << e.what() << endl;
  } catch (MatrixSumException& mse) {
    cout << "! Невозможно выполнить операцию, т.к :\n" << mse.what() << endl;
  }
}
int main(){
  bool cont = true;  
  while(cont){
    menu(cont);
  }
  return 0;
}