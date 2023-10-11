#include<iostream>
#include<math.h>
using namespace std;
// Вектор-ф-ция, вектор, компоненты которого - ф-ции
class AbstrComp {
public:
  virtual void printRes(int i, int pres, double* inpt, double res) = 0;
  virtual double Compute(double* inpt) = 0;
};
class SinComp : public AbstrComp {
public:
  void printRes(int i, int pres, double* inpt, double res){
    printf("<< i=%d : %.*f*sin(%.*f*%.*f) = %.*f\n", i, pres, inpt[0], pres, inpt[1], pres, inpt[2], pres, res);
  }
  double Compute(double* inpt){
    return inpt[0]*sin(inpt[1]*inpt[2]);
  }
};
class ArctanComp : public AbstrComp {
public:
  void printRes(int i, int pres, double* inpt, double res){
    printf("<< i=%d : %.*f*sin(%.*f*%.*f) = %.*f\n", i, pres, inpt[0], pres, inpt[1], pres, inpt[2], pres, res);
  }
  double Compute(double* inpt){
    return inpt[0]*atan(inpt[1]*inpt[2]);
  }
};
void menu() {
  try {
    int N = 0;
    cout << "<< Введите размерность векторной ф-ции :\n>> N = "; cin >> N;
    if (N < 0) throw -1;

    AbstrComp** vec = new AbstrComp*[N]; int chs, pres; double inpt[3]; 
    const string spc = string(3, ' '); const string div = "<< ---\n";

    cout << "<< Для корректной работы программы ввести :\n   0. Число цифр после запятой (точность)\n   1. Номер ф-ции n из множества : {\n\t1 -> a*sin(b*x)\n\t2 -> a*atan(b*x)\n   2. Вещественные параметры а и b\n   3. Аргумент ф-ции x}\n>> точность = ";
    cin >> pres;
    for (int i = 0; i < N; ++i){
      here2 :
      cout << ">> Сформируем " << i << "-й компонент вектора :\n" << spc << "1. Введите номер ф-ции из множества :\n" << spc << ">> n = ";
      cin >> chs;
      switch (chs) {
        case 1 :
          vec[i] = new SinComp;
        break;
        case 2:
          vec[i] = new ArctanComp;
        break;
        default :
          cout << "<! Нет такой функции." << endl;
          goto here2;
          break;
      }

      cout << div << spc << "2. Введите значение параметров :\n" << spc << ">> a = "; 
      cin >> inpt[0]; cout << spc << ">> b = "; cin >> inpt[1];

      cout << div << spc << "3. Введите значение аргумента :\n" << spc << ">> x = "; cin >> inpt[2];

      // Вызов абстрактного метода
      const double& res = vec[i]->Compute(inpt);
      vec[i]->printRes(i, pres, inpt, res);
    }
    // Очистка памяти
    for (int i = 0; i < N; ++i){
      delete vec[i];
    }
    delete[] vec;
    //---
  } catch (int e) {
    cout << "<! Число компонентов вектора не может быть меньше нуля." << endl; 
  } catch (std::bad_alloc& e){
    cout << "<! Невозможно выделить память" << endl;
  }
}
int main() {
  // меню.
  bool isExit = false; char c;
  while (!isExit){
    cout << "__ Решение ЛР №3 - \"Наследование и полиморфизм\"\nМеню : {\n\t1 -> Сформировать вектор ф-ций,\n\t2 -> Завершить работу программы\n}\n>> Введите команду : "; cin >> c;
    switch (c)
    {
    case 1:
      menu();
    break;
    case 2:
      isExit = true;
    break;    
    default:
      cout << "<! Нет такой команды.\n" << endl; continue;
    break;
    }
  }
  
}
