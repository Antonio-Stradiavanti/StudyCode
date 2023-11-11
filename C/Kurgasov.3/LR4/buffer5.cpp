#include<iostream>
#include<vector>
#include<string>
#include<ctime>
using namespace std;

class T {
  int* elem;
  int size;
  string name;
public :
  T() : elem{nullptr}, size{}, name{"A"} {}
  T(int size, string name = "t") : size{size}, elem{new int[size]}, name{name} {
  for (int i = 0; i < size; ++i) {
      elem[i] = rand() % 100;
    }
  }
  ~T() { delete[] elem; }
  T& operator= (const T&) ;
  friend ostream& operator << (ostream&, const T&) ; 
  void setName(string name) ;
};
ostream& operator << (ostream& cout, const T& t) {
  cout << t.name << " = {\n\t";
  for (int i = 0; i < t.size; ++i) {
    if (i != t.size-1) cout << t.elem[i] << ", ";
    else cout << t.elem[i] << ".";
  }
  cout << "\n" << string(t.name.size(), ' ') << "   };" << endl;
  return cout ;   
}

T& T::operator= (const T& t) {
  int* p = new int[t.size];
  copy(t.elem, t.elem + t.size, p);

  delete[] elem; elem = p; size = t.size;

  return *this;
}

void T::setName(string name) {
  this->name = name; 
}

template <class U>
class cont {
  vector < U > vec;
  int size;
  string name_e;
public: 
  cont(int size_v, int size_e, string name_e) : size{size_v}, name_e{name_e} {
    vec.reserve(size_v);
    for (int i = 0; i < size_v; ++i) {
      vec.emplace_back(size_e);
    }
  }
  
  cont<U>& operator= (const cont<U>&) ;

  template <class Q> friend ostream& operator << (ostream&, cont< Q >&) ; 

};
template <class U>
cont<U>& cont<U>::operator= (const cont<U>& C) {
  this->vec = C.vec;
  this->size = C.size;
  this->name_e = C.name_e;
  return *this;
}
template <class U>
ostream& operator << (ostream& cout, cont<U>& C) {
  for (int i = 0; i < C.size; ++i) {
    C.vec[i].setName(C.name_e + to_string(i));
    cout << C.vec[i];
  }
  return cout;
}
int main () {
  srand(time(0));
  //T t0(10, "t0"), t1(10, "t1"); cout << t0 << t1;
  //cout << (t0 = t1);

  //cont< T > C{10, 5, "c"}, D{5, 2, "d"};
  //cout << C << D;
  //C = D;
  //cout << "---\n" << C << endl;
  int* a = nullptr;
  delete[] a;
  int size; cin >> size;
  cout << size << endl;
  return 0;
}