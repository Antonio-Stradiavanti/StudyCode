#include<iostream>
#include<random>
#include<algorithm>
using namespace std;
namespace C {

  class charArray;
  ostream& operator << (ostream& os, const charArray& С) ;

  class charArray {
    int size;
    char* str;
    
    uniform_int_distribution<int> disInt;
    random_device gen;

  public: 
    charArray() : size{}, str{nullptr}, disInt{} {}
    // Создает случайную строку
    charArray(int n, int a=0, int b=0) : size{n}, disInt(0, 51), str{new char[size+1]} {
      
      char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
      int i;

      for (i = 0; i < size; ++i) 
        str[i] = abc[ disInt(gen) ]; 
      
      str[i] = '\0';
    }
    // Конструктор копирования
    charArray(const charArray& C) : size{C.size}, str{new char[C.size+1]} {
      std::copy(C.str, C.str + C.size + 1, str);
    }
    ~charArray() { delete[] str; }

    charArray& operator= (const charArray& C) {
      int i;
      size = C.size;

      char* p = new char[C.size+1];
      
      std::copy(C.str, C.str + C.size, p);
      p[C.size] = '\0';

      if (str != nullptr)
        delete[] str; 
      
      str = p;
      
      return *this;
    }

    charArray operator+ (const char c) {
      // Пустой массив символов
      charArray C; 
      
      C.size = size + 1;
      C.str = new char[size + 2];

      int i;

      std::copy(str, str+size, C.str);       
      C.str[size] = c; C.str[size+1] = '\0';

      return C;
    }

    friend ostream& operator << (ostream& os, const charArray& С) ;
  };

  ostream& operator<< (ostream& os, const charArray& С) {
    if (С.str != nullptr) 
      os << "\"" << С.str << "\"";
    else os << "\"\"";
    return os ;
  }

}
