#include<iostream>
#include<string>
#include<vector>
using namespace std;
namespace M {

  template <class T>
  class Matrix;

  template <class U>
  ostream& operator<< (ostream& cout, const Matrix<U>& M) ;

  template <class T>
  class Matrix {
    int n, m;
    int size;

    string name;

    vector < vector < T > > mA;

  public: 
    // Конструктор по умолчанию
    Matrix () : n{}, m{}, size{}, name{"A"}, mA() /*Просто пустой*/ {}
    // Конструктор копирования
    Matrix (const Matrix& M) : n{M.n}, m{M.m}, size{M.size}, name{M.name} {
      mA.reserve(M.n);
      for (int i = 0; i < M.n; ++i) {
        mA[i].reserve(M.m);
        for (int j = 0; j < M.m; ++j) {
          // Копируем
          mA[i].emplace_back(M.mA[i][j]);
        }
      }
    }
    // Нормальный конструктор
    Matrix (int n, int m, int size, string name="A", int a=0, int b=0) : n{n}, m{m}, size{size}, name{name} {
      mA.reserve(n);
      for (int i = 0; i < n; ++i) {
        mA[i].reserve(m);
        for (int j = 0; j < m; ++j)
          mA[i].emplace_back(size, a, b);
      }
    }
    void setName(const string name) { this->name = name; }
    bool empty () const { 
      if (mA.empty()) return 1;
      else return 0; 
    }

    Matrix<T>& operator= (const Matrix<T>& M) {
      n = M.n; m = M.m; 
      name = M.name; size = M.size;

      if (!mA.empty()) {
        vector < vector < T > >().swap(mA);
      }

      /* mA.reserve(M.n);
      for (int i = 0; i < M.n; ++i) {
        mA.emplace_back(M.mA[i].begin(), M.mA[i].end());
      } */
      mA.reserve(M.n);
      for (int i = 0; i < M.n; ++i) {
        mA[i].reserve(M.m);
        for (int j = 0; j < M.m; ++j) {
          // Копируем
          mA[i].emplace_back(M.mA[i][j]);
        }
      }


      return *this;
    }

    Matrix<T> operator+ (const char c) {
      Matrix<T> M {*this};
 
      for (int i = 0 ; i < n; ++i ) {
        for (int j = 0; j < m ; ++j) {
          M.mA[i][j] = mA[i][j] + c;
        }  
      }  
      /* M.mA.reserve(n);
      for (int i = 0 ; i < n; ++i ) {

        M.mA[i].reserve(m);

        for (int j = 0; j < m ; ++j) {
          tmp = mA[i][j] + c;
          M.mA[i].emplace_back(tmp);
        }
      }
      */

      return M;
    }

    template <class U>
    friend ostream& operator<< (ostream& cout, const Matrix<U>& M) ;

  };

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

}
