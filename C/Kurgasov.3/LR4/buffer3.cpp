#include<iostream>
#include<string>
#include<vector>
#include<array>
using namespace std;

class tmp {
  int n, m;
  vector< vector<string*> > A;
public: 
  tmp() : n{0}, m{0} {}
  tmp(int n, int m) : n{n}, m{m}, A(n, vector<string*>(m)) {
    for(int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        A[i][j] = new string(i, 'f');
      }
    } 
  } 
  tmp(const tmp& T) : n{T.n}, m{T.m} {
    this->A = T.A;
    /* for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        this->A[i][j] = T.A[i][j];
      }
    } */
  }
  void display() {
    for(int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << *A[i][j] << " ";
      }
      cout << endl;
    } 
  } 
};
int main() {
  array<int, 10> a{1, 2, 3};
  tmp A(5, 5); tmp B{A};
  A.display();
  B.display();
  int* pa = a.data();
  cout << ++(*pa) << " " << a[0] << endl;;
  return 0;
}