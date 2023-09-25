#include<iostream>
using namespace std;
class Counter{
  unsigned int count;
public:
  Counter() : count(0) {}
  unsigned int getCount() { return count; }
  void operator++ () { ++count; }
};
int main()
{
  
  return 0;
}
