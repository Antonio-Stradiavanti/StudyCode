#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;

template <class T>
class numArray {
  int n;
  T* arr; 

  uniform_int_distribution<int> disInt;
  uniform_real_distribution<float> disFloat;
  random_device gen;

public:
  numArray() : n{}, arr{nullptr} {}
  numArray(int n, int a=0, int b=0) : n{n}, disInt(a, b), disFloat(0.0, 1.0), arr{new T[n]} {

    if (!a && !b) {
      for (int i = 0; i < n; ++i) {
        arr[i] = 0;
      }
    } else {
      for (int i = 0; i < n; ++i) {
        arr[i] = disInt(gen) + disFloat(gen);
      }
    }
  }
  numArray(const numArray<T>& A1) : n{A1.n}, arr{new T[A1.n]} { 
    copy(A1.arr, A1.arr+A1.n, arr); 
  }
  ~numArray() { delete[] arr; }
  
  numArray<T>& operator= (const numArray<T>& A1) {
    T* p = new T[A1.n];
    copy(A1.arr, A1.arr+A1.n, p);
    
    delete[] arr;

    arr = p; n = A1.n;

    return *this;
  }
  numArray<T> operator+ (const char c) {
    int i, j;
    numArray<T> A{n};  
    for(int i = 0; i < n; ++i) {
      A.arr[i] = this->arr[i] + c;
    }
    return A;
  }
  template <class U> friend ostream& operator<< (ostream& cout, const numArray<U>& nA) ;
};
/* 
  NumArray : Реализации методов класса.
*/
template <class U> ostream& operator << (ostream& cout, const numArray<U>& nA) {
  int i; const int& n = nA.n ;
  if (!n) {
    cout << "[ - ]";
  } else {
    cout << "[ ";
    for (i = 0; i < n-1; ++i)
      cout << nA.arr[i] << ", ";
    cout << nA.arr[i] << " ]";
  }

  return cout;
}
/* 
  CharArray : Описание класса .
  
  TODO Должны быть определены : 1. конструктор копирования, 2. конструктор по-умолчанию, 3. оператор присваивания 

*/
class charArray {
  int n;
  char* str;
  
  uniform_int_distribution<int> disInt;
  random_device gen;

public: 
  charArray() : n{0}, str{nullptr}, disInt{} {}
  // Создает случайную строку
  charArray(int n, int a, int b) : n{n}, disInt(0, 51), str{new char[n+1]} {
    
    char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    for (i = 0; i < n; ++i) str[i] = abc[ disInt(gen) ]; 
    str[i] = '\0';
  }
  ~charArray() { delete[] str; }
  // Конструктор копирования
  charArray(const charArray& A1) : n{A1.n}, str{new char[A1.n+1]} {
    copy(A1.str, A1.str + A1.n + 1, this->str);
  }
  // Оператор присваивания
  charArray& operator= (const charArray& A1);
  charArray operator+ (const char c);
  friend ostream& operator << (ostream& cout, const charArray& cA) ;
};
/* 
  CharArray : Реализации методов класса.
*/
ostream& operator << (ostream& cout, const charArray& cA) {
  cout << "\"" << cA.str << "\"";
  return cout ;
}
charArray& charArray::operator= (const charArray& A1) {
  int i;
  char* p = new char[A1.n+1];
  copy(A1.str, A1.str+A1.n+1, p);

  delete[] str; 
  
  str = p; n = A1.n;
  
  return *this;
}

charArray charArray::operator+ (const char c) {
  charArray cA; 

  cA.n = this->n + 1;
  cA.str = new char[cA.n + 1];

  int i;
  for (i = 0; i < n; ++i) cA.str[i] = this->str[i]; 
  cA.str[i] = c; cA.str[i+1] = '\0';

  return cA;
}
/* 
  Основной класс : 
  Должны быть определены : 
    1. конструктор копирования, 
    2. конструктор по-умолчанию, 
    3. оператор присваивания.
*/
template <class T>
class Matrix {
  int n, m;
  int size;
  string name;

  vector < vector < T > > mA;

public: 
  // Конструктор по умолчанию
  Matrix () : n{0}, m{0}, size{0}, name{"A"}, mA() {}
  // Конструктор копирования
  Matrix (const Matrix& M) : n{M.n}, m{M.m}, size{M.size}, name{M.name}, mA(M.n, vector<T> (M.m)) {
    for (int i = 0; i < M.n; ++i) {
      for (int j = 0; j < M.m; ++j) {
        // Копируем
        this->mA[i][j] = M.mA[i][j];
      }
    }
  }
  // Нормальный конструктор
  Matrix (int n, int m, int size, string name="A", int a=0, int b=0) : n{n}, m{m}, size{size}, name{name} {
    mA.reserve(n);
    for (int i = 0; i < n; ++i) {
      mA[i].reserve(m);
      for (int j = 0; j < m; ++j)
        mA[i].emplace_back(size, a, b);
    }
  }
  Matrix<T>& operator= (const Matrix<T>& M) ;
  Matrix<T> operator+ (const char c) ;

  void setName(const string name) { this->name = name; } ;
  bool empty () const { 
    if (mA.empty()) return 1;
    else return 0; 
  }

  template <class U> friend ostream& operator<< (ostream& cout, const Matrix<U>& M) ;

};
/* 
  Matrix : Реализации методов класса.
*/
// Передаем глобальный объект в операторную ф-цию только для того чтобы показать какого типа должен быть левый операнд. Никакого копирования не выполняется так как передаем по ссылке.
template <class U> ostream& operator<< (ostream& cout, const Matrix<U>& M) {
  
  int i, j;
  const int &n = M.n, &m = M.m;

  cout << M.name << " = {" << endl;
  for (i = 0; i < n ; ++i) {
    cout << "\t[\n\t  №" << i+1 << ": ";
    for (j = 0 ; j < n ; ++j) {
      if (j == n-1) { 
        (i == n-1) ? cout << M.mA[i][j] << ";\n\t]." << endl : cout << M.mA[i][j] << ";\n\t]," << endl ; 
      } else { 
        cout << M.mA[i][j] << ", " ;
      }
    }
  }
  cout << "\n    }" << endl;

  return cout;
}
template <class T>
Matrix<T> Matrix<T>::operator+ (const char c) {
  Matrix<T> M{this->n, this->m, this->size};
  for (int i = 0 ; i < M.n; ++i ) {
    for (int j = 0; j < M.m ; ++j) {
      M.mA[i][j] = this->mA[i][j] + c;
    }
  }

  return M;
}
template <class T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& M) {
  this->mA = M.mA;

  this->n = M.n; this->m = M.m; 
  this->name = M.name; this->size = M.size;

  return *this;
}
/* Ф-ция high : Находит наибольшее значение в массиве, элементы которого принадлежат интервалу адресов [first, last) ; T должен быть базовым типом */
template <class T> T* high(T* first, T* last) {
  T h = -1 ; T* high ;
  // first == last
  // или хотя бы один из переданных указателей - 0.
  for (T* p = first; p != last; ++p) {
    if (h < *p) {
      high = p ; h = *p ;
    }
  }
  return high;

}
/* Ф-ция menu :: предоставляет пользователю текстовый интерфейс */
void menu() {
  char in0{'c'}, in1, in2, in3{'p'}; 

  int n, m;
  int size{0}, a{0}, b{0};
  string name;

  char c;

  Matrix < numArray <int> > Mi_o; Matrix < numArray <int> > Mi_s;

  Matrix < numArray <float> > Mf_o; Matrix < numArray <float> > Mf_s;

  Matrix < charArray > Ms_o; Matrix < charArray > Ms_s;

  //cout << "\n* Решение лабораторной работы \"Параметризованные классы\"\n\n" << "! Примечание, в данной программе используются следующие условные обозначения :\n  Символ >> означает \"введите команду\",\n  Символ % означает \"пример\".\n  Пара символов [ ] указывает на опциональность параметра.\n\n" << " - c -> Сформировать матрицу, сост. из :\n" << "    + n -> Массивов чисел,\n      * i -> Массивов целых чисел,\n      * f -> Массивов вещественных чисел" << "\n    + s -> Строк (массивов символов)." << "\n  - e -> Завершить работу программы.\n\n% Команда : cni -s=10 --min=0 --max=20, означает : сформировать матрицу из массивов целых чисел, каждый из которых содержит 10 элементов, принимающих случайные значения из интервала от 0 до 20 ;\n\n>> ";

  string help = "  * Справка\n\n    * Функционал\n\n      Программа позволяет создать матрицу, состоящую из массивов чисел или символов, определена операция \"Сложение поэлементное сложение с символом\"\n\n    * Условные обозначения\n\n      - Символ % означает \"пример\",\n      - Символ >> означает \"введите команду\".\n\n";
  string hat = "\n* Решение лабораторной работы \"Параметризованные классы\"\n\n";
  string main_menu = "  * Главное меню\n\n    - c -> Сформировать матрицу\n    - h -> Вывести справку\n    - e -> Завершить работу программы.\n\n  >> ";
  string create_matrix = "  * Создадим матрицу\n\n    - n -> Создать матрицу массивов чисел\n    - s -> Создать матрицу строк (массивов символов)\n\n  >> ";
  string create_num_matrix1 = "    1. Задайте параметры массивов чисел\n      - --size -> число элементов массива\n      - -a -> Левая граница интервала, опр. НВС,\n      - -b -> Правая граница интервала, опр. НВС (не включается в интервал).\n\n";
  string create_string_matrix = "    1. Задайте длину каждой из строк\n      - --size -> длина строки.\n\n";
  string create_num_matrix2 = "\n    2. Задайте параметр шаблона :\n      - i -> Создать матрицу целых чисел\n      - f -> Создать матрицу вещественных чисел\n\n" ;
  while (in0 != 'e') {
    cout << hat << main_menu;
    cin >> in0;
    switch (in0) {
    case 'c':
      cout << "  * Задайте имя матрицы\n\n  >> ";
      cin >> name;

      cout << endl << "  * Задайте размеры матрицы\n\n    - -n -> Число строк,\n    - -m -> Число столбцов.\n\n";
      cout << "  >> -n="; cin >> n;
      cout << "  >> -m="; cin >> m;

      cout << endl << create_matrix;
      cin >> in1;
      switch (in1) {
      case 'n':
      // Обработка исключений
        cout << create_num_matrix1; 
        cout << "    >> --size="; cin >> size;
        cout << "    >> -a="; cin >> a;
        cout << "    >> -b="; cin >> b;

        cout << create_num_matrix2;
        cout << "    >> "; cin >> in2;
        switch (in2) {
        case 'i':
          Mi_o = Matrix< numArray< int > > {n, m, size, name, a, b};
          break;
        case 'f':
          Mf_o = Matrix< numArray< float > > {n, m, size, name, a, b};
          break;
        default:
          goto here;
          break;
        }
        break;
      case 's':
        cout << create_string_matrix; 
        cout << "    >> --size="; cin >> size;
        Ms_o = Matrix< charArray > {n, m, size, name};
        break;
      default:
        goto here;
        break;
      }

      while (in3 != 'e') {
        cout << "  * Выберите операцию\n\n    - p -> Вывести матрицу в стандартный поток вывода\n    - s -> Выполнить поэлементное сложение матрицы с символом\n    - e -> Вернуться в главное меню\n\n  >> " ;
        cin >> in3;

        switch (in3) {
        case 'p':
          if (!Ms_o.empty()) cout << Ms_o;
          else if (!Mi_o.empty()) cout << Mi_o;
          else if (!Mf_o.empty()) cout << Mf_o;
          break;
        case 's':
          cout << "    * Введите символ\n\n    >> -c=";
          cin >> c;
          if (!Ms_o.empty()) { 
            Ms_s = Ms_o + c; cout << Ms_s;
          } else if (!Mi_o.empty()) {
            Mi_s = Mi_o + c; cout << Mi_s;
          } else if (!Mf_o.empty()) {
            Mf_s = Mf_o + c; cout << Mf_s;
          }
          break;  
        default:
          break;
        }
      }

    break;
    case 'h':
      cout << help;
      break;  
    case 'e':
      return;  
      break;  
    default:
      here:
      cout << "  << Нет такой команды" << endl;
      break;
    }
  }

}
int main() {
  //menu();
  
  return 0;
}