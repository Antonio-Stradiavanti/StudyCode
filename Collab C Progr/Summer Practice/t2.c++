#include<iostream>
namespace Test
{
  int sum(int a, int b)
  {
    return a + b;
  }
}
int main()
{
  int* p = nullptr;
  int*& rp = p;
  std::cout << (rp == nullptr ? "ноль" : "не ноль") << std::endl;
  // Конструктор типа intc
  std::cout << int(12) << std::endl;
  std::cout << Test::sum(1, 2) << std::endl;
  return 0;
}