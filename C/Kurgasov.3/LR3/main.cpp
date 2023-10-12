#include <iostream>
#include <math.h>
#include <exception>
#include <regex>
using namespace std;
// Вектор-ф-ция, вектор, компоненты которого - ф-ции
class AbstrComp
{
protected:
  int pres;
  double actParams[3];
  double res;

public:
  void setInpt(int pres, double *inpt)
  {
    this->pres = pres;
    for (int i = 0; i < 3; ++i)
    {
      this->actParams[i] = inpt[i];
    }
  }
  virtual void printRes(int i) = 0;
  virtual void Compute(double *inpt) = 0;
  virtual ~AbstrComp() {}
};
class SinComp : public AbstrComp
{
public:
  void printRes(int i)
  {
    printf("\n<< i=%d : %.*f*sin(%.*f*%.*f) = %.*f\n", i, pres, actParams[0], pres, actParams[1], pres, actParams[2], pres, res);
  }
  void Compute(double *actParams)
  {
    this->res = actParams[0] * sin(actParams[1] * actParams[2]);
  }
};
class ArctanComp : public AbstrComp
{
public:
  void printRes(int i)
  {
    printf("<< i=%d : %.*f*arctg(%.*f*%.*f) = %.*f\n", i, pres, actParams[0], pres, actParams[1], pres, actParams[2], pres, res);
  }
  void Compute(double *actParams)
  {
    this->res = actParams[0] * atan(actParams[1] * actParams[2]);
  }
};
void menu()
{
  try
  {
    string tst;

    int N;
    cout << "<< Введите размерность векторной ф-ции :\n>> N = ";
    cin >> tst;
    N = stoi(tst);
    if (N < 0)
      throw out_of_range("");

    AbstrComp **vec = new AbstrComp *[N];
    char c;
    int pres;
    double inpt[3];
    const string spc = string(3, ' ');
    const string div = "<< ---\n";

    cout << "<< Для корректной работы программы ввести :\n   0. Число цифр после запятой (точность)\n   1. Номер ф-ции n из множества : {\n\t1 -> a*sin(b*x)\n\t2 -> a*atan(b*x)\n   2. Вещественные параметры а и b\n   3. Аргумент ф-ции x}\n>> точность = ";

    cin >> tst;
    pres = stod(tst);

    for (int i = 0; i < N; ++i)
    {
    here2:
      cout << ">> Сформируем " << i << "-й компонент вектора :\n"
           << spc << "1. Введите номер ф-ции из множества :\n"
           << spc << ">> n = ";
      cin >> c;
      switch (c - '0')
      {
      case 1:
        vec[i] = new SinComp;
        break;
      case 2:
        vec[i] = new ArctanComp;
        break;
      default:
        cout << "<! Нет такой функции." << endl;
        goto here2;
        break;
      }
      // Тут нужно обработать ввод
      cout << div << spc << "2. Введите значение параметров :\n"
           << spc << ">> a = ";
      cin >> tst;
      inpt[0] = stod(tst);
      cout << spc << ">> b = ";
      cin >> tst;
      inpt[1] = stod(tst);

      cout << div << spc << "3. Введите значение аргумента :\n"
           << spc << ">> x = ";
      cin >> tst;
      inpt[2] = stod(tst);

      // Фиксируем входные данные
      vec[i]->setInpt(pres, inpt);
      // Вызов абстрактного метода
      vec[i]->Compute(inpt);
    }
    // Выводим вектор ф-ций
    for (int i = 0; i < N; ++i)
    {
      vec[i]->printRes(i);
    }
    cout << endl;
    // Очистка памяти
    for (int i = 0; i < N; ++i)
    {
      delete vec[i];
    }
    delete[] vec;
    //---
  }
  catch (out_of_range &e0)
  {
    cout << "<! Число компонентов вектора не может быть меньше нуля.\n"
         << endl;
  }
  catch (std::bad_alloc &e1)
  {
    cout << "<! Невозможно выделить память.\n"
         << endl;
  }
  catch (invalid_argument &e2)
  {
    cout << "<! Введите число, а не последовательность символов.\n"
         << endl;
  }
}
int main()
{
  // меню.
  bool isExit = false;
  char c;
  while (!isExit)
  {
    cout << "__ Решение ЛР №3 - \"Наследование и полиморфизм\"\nМеню : {\n\t1 -> Сформировать вектор ф-ций,\n\t2 -> Завершить работу программы\n}\n>> Введите команду : ";
    cin >> c;
    switch (c - '0')
    {
    case 1:
      menu();
      break;
    case 2:
      isExit = true;
      break;
    default:
      cout << "<! Нет такой команды.\n"
           << endl;
      continue;
      break;
    }
  }
}
