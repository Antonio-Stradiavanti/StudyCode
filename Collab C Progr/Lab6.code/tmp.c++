#include<iostream>
#include<deque>
#include<list>
#include<set>
#include<vector>
#include<algorithm>

#define MAX_COUNT 1000

using namespace std;

/*
  На максимальную оценку «хорошо»: реализовать интерфейс для работы с данными, хранящимися в заданном контейнере. Интерфейс должен включать функции, которые реализует использованный контейнер. В том числе (или кроме того) необходимо предусмотреть следующие функции:
    1. Слияние двух контейнеров используемого типа в один с добавлением всех элементов 2 контейнера в начало или конец 1 контейнера.
    2. Сортировка элементов контейнера.
    3. Поиск элемента в контейнере.
    4. Добавление/удаление элемента (а также сразу нескольких элементов) в контейнер (в начало/конец, любую позицию перед/после заданного элемента – что возможно).
    5. Удаление по условию (remove_if).
    6. Ввод/вывод содержимого контейнера.
    7. Генерация заданного количества элементов контейнера.

  for (int i = -infinity; i < infinity; i++)
    cout << "Все ошибки в программе должны обрабатываться!" << endl;

  2 – deque - структура данных, представляющая из себя список элементов, в которой добавление новых элементов и удаление существующих производится с обоих концов. Эта структура поддерживает как FIFO, так и LIFO, поэтому на ней можно реализовать как стек, так и очередь. (двусторонняя очередь)
  
  5 – list - структура данных, состоящая из элементов, содержащих помимо собственных данных ссылки на следующий и/или предыдущий элемент списка. С помощью списков можно реализовать такие структуры данных как стек и очередь.

  10 – multiset - это ассоциативный контейнер, содержащий отсортированный набор объектов типа Key. В отличие от set, допускается использование нескольких ключей с эквивалентными значениями. Сортировка выполняется с помощью функции сравнения ключей Compare. Операции поиска, вставки и удаления имеют логарифмическую сложность.
*/

// Двусвязный список. Контейнер последовательностей, которые допускают связанное хранение.
void GenList(list<int> &S)
{
  int elemCount, data;
  cout << "Введите количество элементов для контейнера" << endl;
  cin >> elemCount;
  for (int i = 0; i < elemCount; i++)
  {
    data = rand() % MAX_COUNT;
    S.push_back(data); // Добавляет элемент в конец списка
  }
}

void GenDeque(deque<int> &M)
{
  int elemCount, data;
  cout << "Введите количество элементов для контейнера" << endl;
  cin >> elemCount;
  for (int i = 0; i < elemCount; i++)
  {
    data = rand() % MAX_COUNT;
    M.push_back(data); // Добавляет элемент в конец дека
  }
}

void GenMultiSet(multiset<int> &A)
{
  int elemCount, data;
  cout << "Введите количество элементов для контейнера" << endl;
  cin >> elemCount;
  for (int i = 0; i < elemCount; i++)
  {
    data = rand() % MAX_COUNT;
    A.insert(data); // Добавляет элемент в множество
  }
}

int findInMultiSet(multiset<int> &A, int Data)
{
  if (A.find(Data)!=A.end()) return *A.find(Data);
  else return -1;
}

int findDeque(deque<int>&M, int Data)
{
  deque<int>::iterator it = find(M.begin(), M.end(), Data);
  if (it != M.end()) return *it;
  else return -1;
}

void printDeque(deque<int> &M)
{
  cout << "\t--Deque--" << endl << "[ ";
   for(int i : M)
     cout << i << " ";
  cout << " ]"<< endl;
}

void printMultiSet(multiset<int> &A)
{
  cout << "\t--- Начало Multiset ---" << endl << "[ ";
  for (int i : A)
    cout << i << " ";
  cout << " ]" << endl;
  cout << "\t--- Конец Multiset ---" << endl;
}

void printList(list<int> &S)
{
  cout << "\t--List--" << endl << "[ ";
  for (int i : S)
    cout << i << " ";
  cout << " ]" << endl;
}

int findList(list<int>&S, int Data)
{
  list<int>::iterator it = find(S.begin(), S.end(), Data);
  if (it != S.end()) return *it;
  else return -1;
}

void addToDeque(deque<int> &M)
{
  int i, index, nE, tmp = 0, mode; cout << "[addToDeque] : Сколько изволите добавить в дек : "; cin >> nE;
  if (!nE)
  {                                  //☆*: .｡. o(≧▽≦)o .｡.:*☆
      cout << "[addToDeque] : Отмена операции : (*/ω＼*)" << endl; return;  
  }
  // Создаем вектор добавляемых значений и последовательно заполняем его.
  vector<int> Els;
  for (i = 0; i < nE; i++)
  {
     cout << "[addToDeque] : Введите " << i+1 << "й добавляемый элемент : "; cin >> tmp; 
    Els.push_back(tmp);
  }
  cout << "Введите режим добавления : [1 -> в начало, 2 -> в конец, 3 -> по позиции]." << endl;
  cin >> mode;
  switch(mode)
    
    {
      case 1:
        // Добавляем каждый из элементов в начало двухсторонней очереди.
        for (auto it = Els.begin(); it != Els.end(); it++)
            M.push_front(*it);
      break;
      case 2:
        // Добавляем каждый из элементов в конец двухсторонней очереди.
        for (auto it = Els.begin(); it != Els.end(); it++)
           M.push_back(*it);     
      break;
      case 3:
        // Добавляю элмент туда куда хочет юзер.
        for (auto it = Els.begin(); it != Els.end(); it++)
        {
          cout << "Введите номер позиции в двусторонней очереди : "; cin >> index;
          M.insert(M.begin() + index, *it);
        }
      break;
      defaut:
        cout << "" << endl;
      break;
    }
  Els.clear();
}

void addToList(list<int> &S)
{
  int i, index = 0, nE, tmp = 0, mode; cout << "[addToList] : Сколько изволите добавить в список : "; cin >> nE;
  if (!nE)
  {                                  //☆*: .｡. o(≧▽≦)o .｡.:*☆
      cout << "[addToList] : Отмена операции : .｡. o(≧▽≦)o" << endl; return;  
  }
  // Создаем вектор добавляемых значений и последовательно заполняем его.
  vector<int> Els;
  for (i = 0; i < nE; i++)
  {
     cout << "[addToList] : Введите " << i+1 << "й добавляемый элемент : "; cin >> tmp; 
    Els.push_back(tmp);
  }
  cout << "[addToList] : Введите режим добавления : [1 -> в начало, 2 -> в конец, 3 -> по позиции]." << endl;
  cin >> mode;
  switch(mode)
    
    {
      case 1:
        // Добавляем каждый из элементов в начало двухсторонней списка.
        for (auto it = Els.begin(); it != Els.end(); it++)
            S.push_front(*it);
      break;
      case 2:
        // Добавляем каждый из элементов в конец двухсторонней списка.
        for (auto it = Els.begin(); it != Els.end(); it++)
          S.push_back(*it);     
      break;
      case 3:
         //Добавляю элмент туда куда хочет юзер.
        list<int>::iterator it1 = S.begin();
        for (auto it = Els.begin(); it != Els.end(); it++)
        {
          cout << "Введите номер позиции в списке : "; cin >> index;
          if (index < S.size())
          {
            // advance -> накопительно увеличивает значение переданного итератора.
            it1 = S.begin();
            advance(it1, index);
            S.insert(it1, *it);
          }
        }
      break;
      defaut:
        cout << "" << endl;
      break;
    }
  Els.clear();
}

void addToMultiSet(multiset<int> &A)
{
  int i, index = 0, nE, tmp = 0; 
  cout << "[addToMultiSet] : Сколько элементов добавить в комплект : "; cin >> nE;
  if (!nE)
  {                                  
      cout << "[addToMultiSet] : Отмена операции : Число элементов == 0.｡. o(≧▽≦)o" << endl; return;  
  }
  // Создаем вектор добавляемых значений и последовательно заполняем его.
  vector<int> Els;
  for (i = 0; i < nE; i++)
  {
    cout << "[addToMultiSet] : Введите значение " << i+1 << "го добавляемого элемента : "; cin >> tmp; 
    Els.push_back(tmp);
  }
  for (unsigned i : Els)
    A.insert(i);  
  Els.clear();
}

void delFromMultiSet(multiset<int> &A)
{
  if (A.empty())
  {
    cout << "[delFromMultiSet] : Отмена операции : Комплект пуст." << endl; return;
  }
  int i, index = 0, nE, tmp = 0; cout << "[delFromMultiSet] : Сколько элементов удалить из комплекта : "; cin >> nE;
  if (!nE)
  {
    cout << "[delFromMultiSet] : Отмена операции : Число элементов == 0.｡. o(≧▽≦)o" << endl; return;  
  }
  if (nE > A.size())
  {
    cout << "[delFromMultiSet] : Отмена операции : Введенное число элементов превышает размер комплекта." << endl; return; 
  }
  vector<int> Els;
  for (i = 0; i < nE; i++)
  {
    cout << "[delFromMultiSet] : Введите значение " << i+1 << " удаляемого элемента : "; cin >> tmp; 
    Els.push_back(tmp);
  }
  for (unsigned i : Els)
    // Для удаления элемента из комплекта используется метод erase, который принимает итератор и значение.
    A.erase(i);
  Els.clear(); cout << "[delFromMultiSet] : Все указанные элементы, за исключением отсутствующих в комплекте, успешно удалены." << endl;
}

void condDelFromMultiSet(multiset<int> &A)
{
  // Условное удаление remove_if(first, last, p) -> удаляет все элементы удовлетворяющие определенным критериям из диапазона [first, last), определен в заголовочном файле algorithm.
  // Удаляет элементы для которых предикат p возвращает истину.
  // p -> унарный предикат, возвращает true если элемент должен быть удален
  int mode = 0, tmp = 0; 
  vector<int> V;
  for (auto it = A.begin(); it != A.end(); it++)
    V.push_back(*it);
  cout << "[condDelFromMultiSet] : Выберите предикат:\n[\n\t1 -> Удалить все элементы больше некоторого числаn\n\t2 -> Удалить все элементы меньше некоторого числа\n\t3 -> Удалить все элементы равные какому-либо числу\n\t4 -> Удалить все элементы в некотором диапазоне.\n]" << endl; cin >> mode;
  switch (mode)
  {
    // Обработать случай когда ничего не удаляется.
    // Удалить все элементы больше некоторого числа
    case 1:
      cout << "[condDelFromMultiSet] : Введите число, элементы контейнера больше которого удаляем : "; cin >> tmp;
      A.clear();
      V.erase(remove_if(V.begin(), V.end(), [tmp](int &V)
      {
        return V > tmp;
      }), V.end());
      for (auto it = V.begin(); it != V.end(); it++)
        A.insert(*it);
    break;
    case 2:
      cout << "[condDelFromMultiSet] : Введите число, элементы контейнера меньше которого удаляем : "; cin >> tmp;
      A.clear();
      V.erase(remove_if(V.begin(), V.end(), [tmp](int &V)
      {
        return V < tmp;
      }), V.end());
      for (auto it = V.begin(); it != V.end(); it++)
        A.insert(*it);
    break;
    case 3:
      cout << "[condDelFromMultiSet] : Введите число, равные которому удаляем : ";
      cin >> tmp;
      A.clear();
      V.erase(remove_if(V.begin(), V.end(), [tmp](int &V)
      {
        return V == tmp;
      }), V.end());
      for (auto it = V.begin(); it != V.end(); it++)
        A.insert(*it);
    break;
    case 4:
      int st, end;
      cout << "[condDelFromMultiSet] : Введите начальную и конечную границы диапазона : "; cin >> st >> end;
      A.clear();
      V.erase(remove_if(V.begin(), V.end(), [st, end](int &V)
      {
        return V >= st && V < end;
      }), V.end());
      for (auto it = V.begin(); it != V.end(); it++)
        A.insert(*it);
    break;
    default:
      cout << "[condDelFromMultiSet] : Отмена операции : Введенный режим не найден." << endl;
    break;    
  }
  cout << "[condDelFromMultiSet] : Указнные элементы успешно удалены." << endl;
}

void Merge(multiset<int> &M1, multiset<int> &M2)
{
  // Пользователь должен выбрать куда добавлять : 1 -> в начало, 2 -> в конец.
  cout << "[Merge] : Добавим элементы из второго контейнера в первый.\n[Merge->Примечание] : для ассоциативного контейнера, которым является комплект, не имеет значения куда добавлять в начало или в конец, так как все его элементы автоматически сортируются по возрастанию." << endl;
  M1.insert(M2.begin(), M2.end());
}

void help()
{
  cout << "=☆*: .｡. o(≧▽≦)o .｡.:*☆=❤️ Менюшка-> Обработка контейнера multiset ❤️=☆*: .｡. o(≧▽≦)o .｡.:*☆=" << endl;
  cout << "1 -> Генерация заданного количества элементов контейнера." << endl;
  cout << "2 -> Поиск элемента в контейнере." << endl;
  cout << "3 -> Вывод содержимого контейнера" << endl;
  cout << "4 -> Добавление (а также сразу нескольких элементов) в контейнер )." << endl;
  cout << "5 -> Удаление (а также сразу нескольких элементов) из контейнера" << endl;
  cout << "6 -> Удаление по условию." << endl;
  cout << "7 -> Сортировка элементов контейнера." << endl;
  cout << "8 -> Слияние двух контейнеров используемого типа в один с добавлением всех элементов 2 контейнера в начало или конец 1 контейнера." << endl;
}
// На вход подаем контейнер
void menu()
{
  int Choice;
}

int main() {
  multiset<int> A, B;
  setlocale(LC_ALL, "ru");
  /*
  GenMultiSet(A);
  for (int i : A)
    cout << i << " ";  
  cout << endl;
  cout << findInMultiSet(A, 660) << endl;
  */
  // цикл -> for each
  // Пока указанный итератор не дойдет до конца контейнера. 
  // Основанный на диапазоне цикл for, используется для перебора каждого из элементов контейнера.
  
  //GenList(Sergey);
  //printList(Sergey);
  //addToList(Sergey);
  //printList(Sergey);

  GenMultiSet(A);
  GenMultiSet(B);
  printMultiSet(A);
  printMultiSet(B);
  //addToMultiSet(A);
  //condDelFromMultiSet(A);
  Merge(A, B);
  printMultiSet(A);
  
  return 0;
}