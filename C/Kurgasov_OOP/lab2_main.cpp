#include<iostream>
#include<vector>
using namespace std;
class Matrix{
private:
  vector< vector<int> > matrix;
public:
  // Конструктор
  Matrix(){

  } // Деструктор
  ~Matrix(){

  }
  Matrix operator + (Matrix m2);
  void printMatrix();
};
int main(){

  return 0;
}