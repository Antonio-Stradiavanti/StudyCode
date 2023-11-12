#include"Matrix.h"
#include"charArray.h"
#include"numArray.h"

int main () {

  char in0{'c'}, in1, in2, in3{'p'}; 

  int n, m;
  int size{0}, a{0}, b{0};
  string name;

  char c;

  M::Matrix < N::numArray <float> > Mi_o{4, 4, 3, "Контрольный пример - множество вещественных чисел", 0, 100}; ; M::Matrix < N::numArray <float> > Mi_s;

  Mi_s = Mi_o + 'a';

  cout << Mi_o << Mi_s << endl;

  //M::Matrix < N::numArray <float> > Mf_o; M::Matrix < N::numArray <float> > Mf_s;

  //M::Matrix < C::charArray > Ms_o{2, 2, 5, "Контрольный пример - строки"}; 
  //M::Matrix < C::charArray > Ms_s;

  //Ms_s = Ms_o + 'q';

  //cout << Ms_o << Ms_s << endl;

  //cout << "\n* Решение лабораторной работы \"Параметризованные классы\"\n\n" << "! Примечание, в данной программе используются следующие условные обозначения :\n  Символ >> означает \"введите команду\",\n  Символ % означает \"пример\".\n  Пара символов [ ] указывает на опциональность параметра.\n\n" << " - c -> Сформировать матрицу, сост. из :\n" << "    + n -> Массивов чисел,\n      * i -> Массивов целых чисел,\n      * f -> Массивов вещественных чисел" << "\n    + s -> Строк (массивов символов)." << "\n  - e -> Завершить работу программы.\n\n% Команда : cni -s=10 --min=0 --max=20, означает : сформировать матрицу из массивов целых чисел, каждый из которых содержит 10 элементов, принимающих случайные значения из интервала от 0 до 20 ;\n\n>> ";

  /* string help = "  * Справка\n\n    * Функционал\n\n      Программа позволяет создать матрицу, состоящую из массивов чисел или символов, определена операция \"Сложение поэлементное сложение с символом\"\n\n    * Условные обозначения\n\n      - Символ % означает \"пример\",\n      - Символ >> означает \"введите команду\".\n\n";
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
          Mi_o = M::Matrix< N::numArray< int > > {n, m, size, name, a, b};
          break;
        case 'f':
          Mf_o = M::Matrix< N::numArray< float > > {n, m, size, name, a, b};
          break;
        default:
          goto here;
          break;
        }
        break;
      case 's':
        cout << create_string_matrix; 
        cout << "    >> --size="; cin >> size;
        Ms_o = M::Matrix< C::charArray > {n, m, size, name};
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
      return 0;  
      break;  
    default:
      here:
      cout << "  << Нет такой команды" << endl;
      break;
    }
  } */
  return 0;
}