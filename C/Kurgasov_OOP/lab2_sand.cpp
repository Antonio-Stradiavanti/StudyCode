#include<iostream>
#include<string>
using namespace std;
struct yt{
  // Открыты по умолчанию
  string Name;
  int SbCoutn;
  yt(string name, int sbCoutn) : Name(name), SbCoutn(sbCoutn){}
};
ostream& operator << (ostream& cout, yt& yt1) {
  // тот же идентификатор может быть переопределен в другом лексическом контексте
  cout << "Имя : " << yt1.Name << "; Падпищеки : " << yt1.SbCoutn << endl;
  return cout; // Принимаем псевдоним и возвращаем его.
}
int main()
{
  int a;
  // Как построчно ввести матрицу.
  for (int i = 0; i < 10; i++){
    cin>>a; cout << " ";
  }
  //cout << 45 << endl;
  return 0;
}
