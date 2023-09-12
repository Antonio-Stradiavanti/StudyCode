#include<iostream>
#include<string>
#include<regex>
using namespace std;

int main()
{
  string abc = "abcdefghijklmnopqrstuvwxyz", tst = "O e2";

  cout << abc.find(tst[2]) << endl; 
  //cout << (regex_match("F a1", regex("(^[OFM] [a-z][0-9]$)")) ? "1" : "0") << endl;
  return 0;
}
