#include <iostream>
#include <exception>
using namespace std;
struct myException : public exception {
public:  
  const char* what () {
    return "Мое исключение.";
  }
}; 
int main() {

  return 0;
}