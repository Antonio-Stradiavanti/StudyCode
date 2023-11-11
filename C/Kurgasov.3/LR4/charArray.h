#include<iostream>
#include<random>
using namespace std;
class charArray {
  int n;
  char* str;
  
  uniform_int_distribution<int> disInt;
  random_device gen;

public: 
  charArray() : n{0}, str{nullptr}, disInt{} {}
  // Создает случайную строку
  charArray(int n, ...) : n{n}, disInt(0, 51), str{new char[n+1]} {
    
    char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    for (i = 0; i < n; ++i) str[i] = abc[ disInt(gen) ]; 
    str[i] = '\0';
  }
  ~charArray() { delete[] str; }
  // Конструктор копирования
  charArray(const charArray& A1) : n{A1.n}, str{new char[A1.n+1]} {
    copy(A1.str, A1.str + A1.n + 1, this->str);
  }

  charArray& operator= (const charArray&);
  charArray operator+ (const char c);
  friend ostream& operator << (ostream& cout, const charArray& cA) ;
};