#include "main.h"
#include <numeric>
#include <iomanip>
#include <exception>
template < class T >
int numDigits(T num) {
  int dig = 0;

  if (num < 0) dig = 1;
  while (num) {
	num /= 10; dig++;
  }

  return dig;
}
/* Реализация алгоритма */
Graph Graph::findMinSpannigTree() {

  Graph t;
  t.num_v = this->num_v;
  t.max_w = this->max_w;
  t.name = this->name + "_T";

  t.V = this->V;
  t.adjMatrix = vector < vector < double > >(
    this->num_v, vector< double >(this->num_v, -1)
  );
  // В векторе dist для каждой, еще не добавленной к дереву вершины храним указатель ближашей к ней вершины. 
  vector< pair<int, double> > arr;
  arr.reserve(this->num_v);
  // Создадим вектор в котором будем отмечать посещенные вершины
  vector<bool> visited(this->num_v, false); 
  vector<double> weights;

  // Добавим нулевую вершину в основное дерево
	uniform_int_distribution<int> disIntV(0, this->num_v - 1);
	random_device gen;
  // В ходе выполнения алгоритма уменьшаем число ребер до num_v-1, они должны иметь наименьший вес
  
  int i, j;

  int v0, v, cur_v = 0; double cur_w; pair<int, int> new_e;
  // Выбрали произвольную вершину
  //v0 = 2;
  v0 = disIntV(gen);
  visited[v0] = true;
  // Формируем храним для каждой, еще не добавленной к дереву вершины индекс ближайшей к ней в матрице смежности.
  for (v = 0; v < t.num_v; ++v) {
    arr.emplace_back(v0, this->adjMatrix[v0][v]);
  }
  // Заходим в цикл и выбираем минимальную вершину из arr
  while(t.num_e != this->num_v-1) {
    cur_w = t.max_w;
    for (i = 0; i < num_v; ++i) {
      if (!visited[i] && arr[i].second < cur_w && arr[i].second != -1) {
        cur_v = i; cur_w = arr[i].second;
      }
    }
    // Добавим соотв ребро
    new_e = pair<int, int>(cur_v, arr[cur_v].first);
    t.E.push_back(new_e);
    t.num_e++;

    weights.push_back(cur_w);
    visited[cur_v] = true;

    // Обновляем arr
    for (v = 0; v < t.num_v; ++v) {
      // Если вершина еще не посещена
      if (
        !visited[v] && 
        ((arr[v].second > adjMatrix[cur_v][v] && adjMatrix[cur_v][v] != -1) || 
          (arr[v].second == -1 && adjMatrix[cur_v][v] != -1)
        )
      ) 
      {
        //cout << "cur_v = " << cur_v << " v = " << v;
        arr[v].first = cur_v;
        arr[v].second = adjMatrix[cur_v][v];
        //cout << "; arr[v].first = " << arr[v].first << "; arr[v].second = " << arr[v].second << endl;
      }
    }
  }

  t.w_t = accumulate(weights.begin(), weights.end(), 0.0);
  for (i = 0; i < t.num_e; ++i) {
    cout << weights[i] << " ";
  }
  cout << endl;


  int f, s;
  for (i = 0; i < t.num_e; ++i) {
    f = t.E[i].first; s = t.E[i].second;
    t.adjMatrix[ f ][ s ] = weights[i];
    t.adjMatrix[ s ][ f ] = weights[i];
  }

  return t;
}
/* TODO Реализовать ввод с клавиатуры */
struct notNumberException : public exception {
  const char* what() const noexcept {return "[ ! ] Некорректные входные данные, вместо числа вы ввели строку.";}
};
istream& operator>> (istream& cin, Graph& g) {
  try {
    cout << "1. Введите число вершин :\n> num_v = ";
    cin >> g.num_v; if (cin.fail()) throw notNumberException{};

    cout << "2. Введите число ребер :\n> num_e = ";
    cin >> g.num_e; if (cin.fail()) throw notNumberException{};

    cout << "3. Введите максимальный вес ребра графа :\n> max_w = ";
    cin >> g.max_w; if (cin.fail()) throw notNumberException{};

    cout << "4. Введите имя графа :\n> name = "; 
    cin >> g.name;

    g.genGraph();
    g.compTotalWeight();

  } catch(notNumberException& e) {
    cout << e.what() << endl;
  }
  return cin;
}
ostream& operator<< (ostream& cout, const Graph& g) {

  cout << "---\n\nОбщий вес : " << g.w_t << ";\n\nМатрица смежности " << g.name << "\n" << endl;
  
  // Как выровнять поле в потоке вывода С++

  cout << setprecision(2) << fixed;
  
  for (int i = 0; i < g.num_v; ++i) {
	cout << "| " << left << setw(g.maxVertexNameLen) << g.V[i] << " : ";
	for (int j = 0; j < g.num_v; ++j) {
	  cout << left << setw(g.maxWeightLen) << g.adjMatrix[i][j] << " ";
	}
	cout << "|" << endl;
  }
  cout << "\n---" << endl;

  cout << setprecision(6);
  cout.unsetf(ios::fixed);

  return cout;

}
int main() {

  //Graph g(7, 12, 100, "Super G");
  //g.compTotalWeight();
  //cout << g << "\n\n" << g.findMinSpannigTree() << endl;
  Graph g;
  //cin >> g;
  g.genSample(); 
  cout << g << "\n\n*** --- ***\n\n" << g.findMinSpannigTree();

}