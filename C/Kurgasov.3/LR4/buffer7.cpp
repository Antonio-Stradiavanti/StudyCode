#include"Matrix.h"
#include"charArray.h"
#include"numArray.h"

template < typename In, typename Out >
/* Итераторы first и last определяют копируемую последовательность. */
Out copy (In first, In last, Out res) {
  while (first != last) {
    *res = *first;
    ++res; ++first;
  }
  // возвращает итератор, указывающий на последний элемент последовательности res.
  return res;
}

int main () {
  
  // srand(time(0));

  C::charArray c0{10}, c1{c0 + 'q'};
  cout << c0 << endl;
  //c0 = c1 + 'q';
  cout << c1 << endl;
  /* cout << "\n" << c1 << endl;
  c0 = c1 + 'q';
  
  cout << c0 << endl; */ 
  M::Matrix < C::charArray > Ms_o {2, 2, 5, "P"}, Ms_s ;

  M::Matrix < N::numArray <int> > Mi_o {2, 2, 5, "I", 0, 10}, Mi_s;
  
  //Ms_s = Ms_o + 'f';
  //cout << Ms_o << Ms_s << endl;

  Mi_s = Mi_o + 'q';
  cout << Mi_o << Mi_s << endl;

  return 0;
}