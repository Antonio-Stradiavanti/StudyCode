#include <map>
#include <string>
#include <iostream>
#include <exception>
using namespace std;

int main() {

  int a;
  try {
    cin >> a;
    if (std::cin.fail()) throw 1;
    cout << "a = " << a << endl;
  } catch(int e) {
    cout << "! Некорректныые входные данные" << endl;
  }

  

  return 0;
}