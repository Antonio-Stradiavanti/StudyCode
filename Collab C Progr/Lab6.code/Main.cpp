#include<iostream>
#include<deque>
#include<list>
#include<set>
#include<vector>
#include<string>
#include<random>
#include<algorithm>
#define MAX_NUM 1000
using namespace std;

random_device rd; // random engine ?
// С++ предоставляет engines -> генераторы случайных чисел и distributions -> распределение
/*
  На максимальную оценку «хорошо»: реализовать интерфейс для работы с данными, хранящимися в заданном контейнере. Интерфейс должен включать функции, которые реализует использованный контейнер. В том числе (или кроме того) необходимо предусмотреть следующие функции:
    1. Слияние двух контейнеров используемого типа в один с добавлением всех элементов 2 контейнера в начало или конец 1 контейнера.
    2. Сортировка элементов контейнера.
    3. Поиск элемента в контейнере.
    4. Добавление/удаление элемента (а также сразу нескольких элементов) в контейнер (в начало/конец, любую позицию перед/после заданного элемента – что возможно).
    5. Удаление по условию (remove_if).
    6. Ввод/вывод содержимого контейнера.
    7. Генерация заданного количества элементов контейнера.
  10 – multiset - это ассоциативный контейнер, содержащий отсортированный набор объектов типа Key. В отличие от set, допускается использование нескольких ключей с эквивалентными значениями. Сортировка выполняется с помощью функции сравнения ключей Compare. Операции поиска, вставки и удаления имеют логарифмическую сложность.
  На максимальную оценку «отлично»: реализовать программу отсюда:
*/
void GenMultiSet(multiset<int> &A)
{
    if (!A.empty())
    {
        cout << "[GenMultiSet->Отмена_операции] : Контейнер уже сформирован." << endl;
    }
    int elemCount, data;
    cout << "[GenMultiSet->Ввод_данных] : Введите количество элементов для контейнера : "; cin >> elemCount;
    for (int i = 0; i < elemCount; i++)
    {
        data = rand() % MAX_NUM;
        A.insert(data); // Добавляет элемент в множество
    }
}
void printMultiSet(multiset<int> &A)
{
  cout << "\t--- Начало Multiset ---" << endl << "[ ";
  for (int i : A)
    cout << i << " ";
  cout << " ]\n\t--- Конец Multiset ---" << endl;
}
int findInMultiSet(multiset<int> &A, int Data)
{
    auto it = A.find(Data); 
    if (it == A.end())
    {
        cout << "[findInMultiSet->Ошибка] : Переданный элемент не найден в контейнере." << endl; return -1;
    } 
    else
    {
        cout << "[findInMultiSet->Успех] : Переданный элемент найден в последовательности." << endl; return *it;
    }
}
void addToMultiSet(multiset<int> &A)
{
  int i, index = 0, nE, tmp = 0; 
  cout << "[addToMultiSet] : Сколько элементов добавить в комплект : "; cin >> nE;
  if (!nE)
  {                                  
      cout << "[addToMultiSet] : Отмена операции : Число элементов == 0" << endl; return;  
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
  cout << "[condDelFromMultiSet] : Выберите предикат:\n[\n\t1 -> Удалить все элементы больше некоторого числаn\n\t2 -> Удалить все элементы меньше некоторого числа\n\t3 -> Удалить все элементы равные какому-либо числу\n\t4 -> Удалить все элементы в некотором диапазоне.\n]\n---" << endl; cin >> mode;
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
void smartDraughtsperson()
{
    string str;
}
void help()
{
  cout << "=☆*: .｡. o(≧▽≦)o .｡.:*☆=❤️ Менюшка-> Обработка контейнера multiset ❤️=☆*: .｡. o(≧▽≦)o .｡.:*☆=" << endl;
  cout << "0 -> Завершение работы программы." << endl;
  cout << "1 -> Генерация заданного количества элементов контейнера." << endl;
  cout << "2 -> Поиск элемента в контейнере." << endl;
  cout << "3 -> Вывод содержимого контейнера" << endl;
  cout << "4 -> Добавление (а также сразу нескольких элементов) в контейнер )." << endl;
  cout << "5 -> Удаление (а также сразу нескольких элементов) из контейнера" << endl;
  cout << "6 -> Удаление по условию." << endl;
  cout << "7 -> Сортировка элементов контейнера." << endl;
  cout << "8 -> Слияние двух контейнеров используемого типа в один с добавлением всех элементов 2 контейнера в начало или конец 1 контейнера." << endl;
  cout << "9 -> Вызов программы \"Умный чертежник\"." << endl;
  cout << "10 -> Вывод справки." << endl;
}
void menu(multiset<int> &A)
{
  int c, nC, Data; help();
  multiset<int> B;
  while(1)
  {
    cout << "> "; cin >> c;
    switch (c)
    {
        case 0:
            exit(0);
        break;
        case 1:
            GenMultiSet(A);
        break;
        case 2:
            cout << "[menu->2->in] : Введите значение искомого элемента : "; cin >> Data;
            findInMultiSet(A, Data);
        break;
        case 3:
            printMultiSet(A);
        break;
        case 4:
            addToMultiSet(A);
        break;
        case 5:
            delFromMultiSet(A);
        break;
        case 6:
            condDelFromMultiSet(A);
        break;
        case 7:
            cout << "[menu->7->op_c] : Для ассоциативного контейнера не требуется ручной вызов алгоритма сортировки, такие контейнеры сортируются автоматически." << endl;
        break;
        case 8:
            cout << "[menu->8->in] : Введите число элементов во втором комплекте : "; cin >> nC;
            for (int i = 0; i < nC; i++)
            {
                cout << "[menu->8->in] : Введите " << i << " элемент комплекта : "; cin >> Data; 
                B.insert(Data);               
            }
            Merge(A, B);
        break;
        case 9:

        break;
        case 10:
            cout << "[menu->9->out] Вывод справки." << endl;
        break;
        default:
        break;
    }
  }
}