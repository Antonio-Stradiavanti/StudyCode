#include<iostream>
#include<vector>
#include<queue>
#include<stdlib.h>
#include<time.h>
#define M 5
using namespace std;
vector< vector<int> > initGraph(int vC)
{
  vector< vector<int> > AdjMatrix;
  vector<int> tmp;
  
  int i, j;
  for (i = 0; i < vC; i++)
  {
    for (j = 0; j < vC; j++)
      tmp.push_back(0);
    AdjMatrix.push_back(tmp);
    tmp.clear();
  }
  cout << "[initGraph] : Успех : Граф инициализирован, и является пустым" << endl; return AdjMatrix;
}
vector<int> genGraph(vector< vector<int> > &AdjMatrix, int vC, int Ac)
{
  vector<int> vData; int i, j;
  // Полезные данные вершин
  for (i = 0; i < vC; i++)
  {
    vData.push_back(1 + rand() % 999);      
  }
  // Из каждой вершины должно исходить макс 4 дуги
  int p = 0;
  for (i = 0; i < vC; i++)
  {
    // Минимум 1, максимум 4
    for (j = 0; j < 1 + rand()%(M+1); j++)
    {
      p = 1 + rand()%(vC-1);
      if (p == i) AdjMatrix[i][p] = 2; 
      else AdjMatrix[i][p] = 1;  
    }
  }
  cout <<"[genGraph] : Успех : Граф сформирован"<< endl; return vData;
}
void printGraph(vector< vector<int> > &AdjMatrix, vector<int> &vData)
{
  int i;
  if (AdjMatrix.empty())
  {
    cout << "[printGraph] : Операция отменена : Граф пуст" << endl; return;
  }
  cout << "     | ";
  for (i = 0; i < vData.size(); i++)
    printf("%3d ", vData[i]);
  cout <<"|" << endl; i = 0;
  for (auto a=AdjMatrix.begin();a!=AdjMatrix.end(); a++)
  {
    printf(" %3d | ", vData[i++]);
    for (auto b=a->begin();b!=a->end(); b++)
    {
      printf(" %d  ", *b);
    }
    printf("|\n");
  }
  printf("\n");
}
void addToGraph(vector< vector<int> > &AdjMatrix, vector<int> &vData, int Data)
{
  int i, nAc, tmp; vector<int> vTmp;
  cout << "\n[addToGraph] : Входные данные : Введите количество ребер, иходящих из нового узла [NOTE] : Это количество не должно превышать 4х" << endl;
  cin >> nAc;
  if (nAc > 4)
  {
    cout << "[addToGraph] : Отмена операции : Введенное Количество дуг превышает степень графа" << endl;
    return;
  }
  // Ввели количество дуг, теперь запрашиваем у пользователя смежные ребра.
  cout << "[addToGraph] : Примечание : Связывать узлы будем по индексам в матрице смежности. Индекс нового узла : " << vData.size() << endl;
  vData.push_back(Data);
  // Нужно увеличить размер вектора
  for (i = 0; i < AdjMatrix.size(); i++) 
    AdjMatrix[i].push_back(0);
  for (i = 0; i < vData.size(); i++)  
    vTmp.push_back(0);
  AdjMatrix.push_back(vTmp); vTmp.clear();
  // мы добавили новый элемент, должны ли входить в него дуги из других вершин?
  for (i = 0; i < nAc; i++)
  {
    cout << "[addToGraph] : Добавление узла : Введите индекс узла, смежного с данным : ";
    cin >> tmp;
    if (AdjMatrix.size()-1 != tmp ) AdjMatrix[AdjMatrix.size()-1][tmp] = 1;
    else AdjMatrix[AdjMatrix.size()-1][tmp] = 2;
  }
  cout << "[addToGraph] : Успех : Вершина успешно добавлена в граф" << endl;
}
// Удаление по индексу, исключение соответствующей строки и соответствующего столбца из матрицы
void delFromGraph(vector< vector<int> > &AdjMatrix, vector<int> &vData, int Data)
{
  int i, ffound = 0;
  for (i = 0; i < vData.size(); i++)
  {
    if (vData[i] == Data)
    {
      ffound = 1; break;
    }
  }
  if (!ffound) 
  {
    cout << "[delFromGraph] : Отмена операции : Указанные данные не найдены в графе" << endl; return;
  }
  // Удаляет соответствующую строку
  for (int j = 0; j < AdjMatrix.size(); j++)
    AdjMatrix[j].erase(AdjMatrix[j].begin() + i);
  AdjMatrix.erase(AdjMatrix.begin() + i);
  vData.erase(vData.begin() + i);
  cout << "[delFromGraph] : Успех : вершина " << Data << " удалена из графа" << endl;
}

/*
  - <u>Поиск в ширину</u>
	- <u>Описание:</u> 
		- Посещаются все вершины, смежные с данной перед дальнейшим обходом графа (удобно выполнять по спискам смежности).
	- <u>Алгоритм:</u>
		- Выбирается начальная вершина и помещается в очередь.
		- Для каждой вершины из очереди (for each...) : мы считываем вершину в начале очереди (ближе к кассе) и исследуем каждую смежную с ней вершину. Вершины, чьи списки смежности просмотрены окрашиваются в черный и удаляются из очереди начала.
		- Обнаруженные вершины красим серым и помещаем (enqueue) в конец очереди. Если цвет вершины не белый, то она еще не была обнаружена и обход продолжается до следующей смежной вершины
		- Процесс продолжается пока очередь не станет пустой. Тогда все вершины, достижимые из начальной вершины становятся черными.

  Возвращаем : ничего, в ходе работы программы печатаем обход  
*/

vector<int> BFS(vector< vector<int> > &AdjMatrix, vector<int> &vData, int sV)
{
    // sV -> начальное значение поиска в ширину.
    // Помечаем все вершины как не посещенные V
    vector<int> visited(AdjMatrix.size(), 0), trav; 
    int i, j, flag = 0; // V
    // Создаем очередь для BFS V
    queue<int> q;
    // Нужно найти в векторе vData переданное начальное значение
    for (i = 0; i < vData.size(); i++)
    {
      // V
      if (vData[i] == sV) 
      {
        flag = 1; break;
      } 
    } 
    if (!flag)
    {
      cout << "[BFS] : Операция прервана : Переданная начальная вершина не найдена в графе." << endl;
      return trav;
    }
    // i -> теперь хранит индекс вектора в матрице смежности V
    // Изначально очередь пуста
    visited[i] = 1; q.push(i); 
    // i соответствующий элементу sV индекс в матрице смежности
    // В очередь добавляем идексы, в вектор traversal -> значения вершин

    // Поиск кратчайшего пути до каждой из достижимых вершин графа. 

    while (!q.empty()) 
    {
        // Возвращает указатель на первый элемент в очереди
        i = q.front(); // sV -> индекс в матрице смежности
        // Удаление первого элемента из очереди
        trav.push_back(vData[i]);
        q.pop();
        for (j = 0; j < AdjMatrix[i].size(); j++)
        {
          // Рассматриваем смежные с данной вершиной вершины и помещаем их в очередь по индексу
          if (AdjMatrix[i][j] && !visited[j]) 
          {
            q.push(j);  
            visited[j] = 1;
          }
        }
    }
  return trav;
}
void help()
{
  printf(
    "***<^_^>*** Меню ***<^_^>***\n"
    "0 -> Завершение работы\n"
    "1 -> Сгенерировать граф\n"
    "2 -> Привести граф в начальное состояние\n"
    "3 -> Добавить вершину\n"
    "4 -> Удалить вершину\n"
    "5 -> Вывести матрицу смежности\n"
    "6 -> Вывести результат обхода графа по уровням\n"
    "7 -> Вывести справку\n"
  );
}
void Menu(vector< vector<int> > &AdjMatrix, vector<int> &vData)
{
  int choice, Data, vC, vA;
  vector<int> trav;
  help();
  while (1)
  {
    cout << "<\\-^_^-/> " ; cin >> choice;
    switch(choice) 
    {
      case 0:
        cout << "Пока)" << endl; exit(0);
      break;
      case 1:
        cout << "Введите количество вершин и ребер" << endl;
        cin >> vC >> vA;
        // Для предотвращения копирования возвращаемого вектора
        initGraph(vC).swap(AdjMatrix);
        genGraph(AdjMatrix, vC, vA).swap(vData);
      break;
      case 2:
        AdjMatrix.clear(); vData.clear();
      break;
      case 3:
        cout << "\nВведите узел : "; cin >> Data;
        addToGraph(AdjMatrix, vData, Data);
      break;
      case 4:
        cout << "\nВведите удаляемый узел : "; cin >> Data;
        delFromGraph(AdjMatrix, vData, Data);
      break;
      case 5:
        printGraph(AdjMatrix, vData);
      break;
      case 6:
        cout << "\nВведите начальный узел : "; cin >> Data;
        BFS(AdjMatrix, vData, Data).swap(trav);
        if (!trav.empty())
        {
          cout << "[ ";
          for (int i = 0; i < trav.size()-1; i++)
              cout << trav[i] << ", ";
          cout << trav[trav.size()-1] << " ]"<< endl;
        }
      break;
      case 7:
        help();
      break;
      default:
        cout << "Переданная команда не найдена." << endl;
        break;
    }
  }
}
int main() 
{
  srand(time(NULL));
  setlocale(LC_ALL, "RUS");
  vector< vector<int> > AdjMatrix; vector<int> vData, trav;
  Menu(AdjMatrix, vData);
  vData.clear(); AdjMatrix.clear();
  return 0;
}