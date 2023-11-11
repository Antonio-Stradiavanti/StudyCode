#include<iostream>
using namespace std;
template <class T>
class vec {
  int sz; // Число элементов, elem + sz -> Ячейка памяти, следующая за последним элементом вектора
  T* elem; // Адрес нулевого элемента вектора
  int space; // Количество элементов + зарезервированная, но не инициализированная, область памяти для новых элементов типа T. Число байт памяти, выделенных под вектор.
public :
  // => Память не меняется, пока количество элементов не меняется.
  vec() : sz{0}, elem{nullptr}, space{0} {}
  vec(int s) : sz{s}, elem{new T[s]}, space{s} {
    for (int i=0; i<s; ++i) elem[i]=0.0;
    // Если нет свободной памяти то выделяем в 2 раза больше чем требует пользователь.
  }

  vec(const vec&);

  vec(initializer_list<T> lst) : sz{lst.size()}, elem{new T[sz]} {
    copy (lst.begin(), lst.end(), elem);
  }

  ~vec() {
    delete[] elem;
  }
  // reserve(int число_новых_элементов) -> добавляет память для новых элементов. 
  void reserve(int newalloc) {
    if (newalloc <= space) return ;
    double* p = new double[newalloc] ;

    for (int i=0; i<sz; ++i) {
      p[i] = elem[i];
    }

    delete[] elem;

    elem = p; space = newalloc;
    // p Выбросит из стрека после выполнения следующей инструкции
  }
  void resize(int newsize) {
    // Больше можно, меньше ни-ни !
    // Увеличиваем размер выделенной области памяти и переносим туда значения из старой.
    reserve(newsize);
    // Инициализируем новые элементы (если они есть)
    for (int i = sz; i < newsize; ++i) {
      this->elem[i] = 0.0;
    }
    this->sz = newsize;
  }
  void push_back(const T& el) {
    if (space = 0) {
      reserve(8);
    } else if (sz == space) {
      reserve(2*space);
    }
    // Вызывается оператор =, копирует по ссылке.
    elem[sz++] = el; 
  }
  // Размер доступной памяти в объекте класса вектор, константный метод, не может изменять значение полей класса.
  //int getSize() const { return sz; }
  int size() const { return sz; } 
  int capacity() const { return space; }
  
  vec<T>& operator= (const vec<T>&);

  T& operator[] (int n) {
    return elem[n];
  }
};

template <class T>
vec<T>::vec(const vec<T>& arg) : sz{arg.sz}, elem{new T[arg.sz]} {
  copy(arg, arg+sz, elem);
}

template <class T> 
vec<T>& vec<T>::operator=(const vec<T>& arg) {
  // Просто Заново создаем внутренний динамический массив. 
  if (this != &arg) {
    T* p = new T[arg.sz];

    copy(arg.elem, arg.elem+arg.sz, p);
    // Лучше не стирать информацию пока ее нечем заменить
    delete[] elem;

    elem = p; sz = arg.sz;
  }
  return *this;
}

int main() {
  vec<int> A;
  A.push_back(10);

  return 0;
}
