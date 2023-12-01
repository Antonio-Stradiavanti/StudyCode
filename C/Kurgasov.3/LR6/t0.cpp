#include<iostream>
using namespace std;

enum MapSymbolType {
  None, Relief, VegCover, Water, HumanSettlement, Road, LocalObject
};

int main () {
  
  int t = 1;

  MapSymbolType st = static_cast<MapSymbolType>(t);

  if (st == Relief) {
    cout << "Имба !" << endl;
  }

  return 0;
}