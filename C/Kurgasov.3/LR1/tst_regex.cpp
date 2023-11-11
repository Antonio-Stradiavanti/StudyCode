#include<iostream>
#include<string>
#include<regex>
#include<chrono>
using namespace std;

int main()
{
  string abc = "abcdefghijklmnopqrstuvwxyz", tst = "Oe2", inpt;
  //string localPrompt = "Для выхода из игры введите E, для вывода справки -> H\n[Введите команду : <Функ.><?xy>]$ ";
  bool isExit = true;
  //auto start = chrono::system_clock::now();
  //cout << abc.find(tst[2]) << endl;
  //cout << (isExit && "*" == "*" ? "*" : "+") << endl; 
  //cout << localPrompt; cin >> inpt;
  cin >> inpt;
  cout << (regex_match(inpt, regex("([a-zA-Z!@]+)")) ? "1" : "0") << endl;
  //auto end = chrono::system_clock::now();
  //cout << chrono::duration<double, milli> (end-start).count() << "ms" << endl;
  /* for (int i = -1; i <= 1; i+=1){
    cout << i << "\n\t";
    for (int j = -1; j <= 1; (!i ? j+=2 : j+=1)){
      cout << j << " ";
    }

    cout << "\n" << (1 - -1) << endl;
  } */
  return 0;
}
