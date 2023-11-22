#include<iostream>
#include<fstream>
// Работа с файлами.
using namespace std;
int main() {

  cout << "Введите имя файла : " ; 
  string n0;
  cin >> n0;
  
  ofstream fo{n0};

  //ifstream fi{n0}; 
  // Значение fi, fo -> 0, если файл нельзя корректно открыть.
  if (!fo) cout << "Невозможно открыть файл с именем : " + n0 << endl;

  fo << "[ ";
  for (int i = 0; i < 10; ++i) {
    if (i == 9) fo << rand() % 100 << ". ]";
    else fo << rand() % 100 << ", ";
  }
  fo << endl;

  return 0;
}