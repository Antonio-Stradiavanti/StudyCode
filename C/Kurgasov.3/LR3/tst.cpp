#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main() {
  string tst;
  cin >> tst;
  const string& rtst = tst;
  // Хранит Результат регулярного выражения
  smatch match;
  regex rgx("([0-9]+\\.[0-9]+)");
  cout << tst << " " << (regex_search(rtst.begin(), rtst.end(), match, rgx) ? "Победа" : "Не найдено") << " " << match[1] << " " << stod("gjjgjfghhfg") << endl;
  
  cin >> tst;
  cout << tst << " " << (regex_search(rtst.begin(), rtst.end(), match, rgx) ? "Победа" : "Не найдено") << " " << match[1] << " " << stod("65.56gjjgjfghhfg") << endl;

  return 0;
}