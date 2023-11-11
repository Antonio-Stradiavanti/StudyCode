#include"charArray.h"
/* 
  CharArray : Реализации методов класса.
*/
ostream& operator << (ostream& cout, const charArray& cA) {
  cout << "\"" << cA.str << "\"";
  return cout ;
}
/* Копирующий оператор присваивания */
charArray& charArray::operator= (const charArray& A1) {
  int i;
  char* p = new char[A1.n+1];
  copy(A1.str, A1.str+A1.n+1, p);

  delete[] str; 
  
  str = p; n = A1.n;
  
  return *this;
}

charArray charArray::operator+ (const char c) {
  charArray cA; 

  cA.n = this->n + 1;
  cA.str = new char[cA.n + 1];

  int i;
  for (i = 0; i < n; ++i) cA.str[i] = this->str[i]; 
  cA.str[i] = c; cA.str[i+1] = '\0';

  return cA;
}