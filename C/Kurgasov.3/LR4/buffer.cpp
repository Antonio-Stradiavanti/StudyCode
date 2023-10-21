#include<iostream>
#include<vector>

using namespace std;
int main() {
  char a = 'a';
  vector<double> v{1.23, 34.543, 56.7654, 98.65};
  printf("char a = %d\n", a);
  for (const auto& i : v) {
    cout << i << " ";
  }
  cout << endl;

  for (auto& i : v) {
    i+=a;
  }

  for (const auto& i : v) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}