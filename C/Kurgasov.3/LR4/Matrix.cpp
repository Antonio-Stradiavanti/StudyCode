#include"Matrix.h"
template <class U> 
ostream& operator<< (ostream& cout, const Matrix<U>& M) {  
  int i, j;
  const int &n = M.n, &m = M.m;

  cout << M.name << " = {" << endl;
  for (i = 0; i < n ; ++i) {
    cout << "\t[\n\t  №" << i+1 << ": ";
    for (j = 0 ; j < n ; ++j) {
      if (j == n-1) { 
        (i == n-1) ? cout << M.mA[i][j] << ";\n\t]." << endl : cout << M.mA[i][j] << ";\n\t]," << endl ; 
      } else { 
        cout << M.mA[i][j] << ", " ;
      }
    }
  }
  cout << "\n    }" << endl;

  return cout;
}
template <class T>
Matrix<T> Matrix<T>::operator+ (const char c) {
  Matrix<T> M{this->n, this->m, this->size};
  for (int i = 0 ; i < M.n; ++i ) {
    for (int j = 0; j < M.m ; ++j) {
      M.mA[i][j] = this->mA[i][j] + c;
    }
  }

  return M;
}
/* Копирующий оператор присваивания */
template <class T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& M) {
  this->mA = M.mA;

  this->n = M.n; this->m = M.m; 
  this->name = M.name; this->size = M.size;

  return *this;
}