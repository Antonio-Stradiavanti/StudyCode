#include<iostream>
#include<string>
#include<regex>
#include<chrono>
using namespace std;

int main()
{
  string abc = "abcdefghijklmnopqrstuvwxyz", tst = "O e2";
  auto start = chrono::system_clock::now();
  cout << abc.find(tst[2]) << endl; 
  //cout << (regex_match("F a1", regex("(^[OFM] [a-z][0-9]$)")) ? "1" : "0") << endl;
  auto end = chrono::system_clock::now();
  cout << chrono::duration<double, milli> (end-start).count() << "ms" << endl;
  return 0;
}
