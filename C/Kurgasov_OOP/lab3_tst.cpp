#include<iostream>
using namespace std;
int a;
class Tmp {
public:
  Tmp() : var{}, bar{9} {}
  int var;
  int bar;
};
class Der : public Tmp {
public:
  int locvar;
};
int main() {
  static int b;
  
  Der tmp{};
  cout << sizeof(long) << " " << tmp.bar << endl;
  return 0;
}