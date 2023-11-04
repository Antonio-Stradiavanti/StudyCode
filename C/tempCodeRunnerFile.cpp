#include<iostream>
using namespace std;

struct U {
  int a, b, c;
  double x;
  void print() {
    printf("\n---\nцелые : %d, %d, %d\nвещественные : %lf\n---\n", a, b, c, x);
  }  
};
int main() {
  U tmp0{10, 10, 12, 12.45};
  U tmp{tmp0}; tmp.print();
  return 0;
}