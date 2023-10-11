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
  regex rgx(".*[1-9]\\.[1-9].*");
  cout << tst << " " << (regex_search(rtst.begin(), rtst.end(), match, rgx) ? "Победа" : "Не найдено") << endl;
  return 0;
}