#include "main.h"
#include <iomanip>
/* 

  Программу будем тестировать на конкретном примере, занимаюсь порциями.

  Нужно сгененрировать граф и построить на его основе миинимальное остовное дерево. 

  Реализуем алгоритм ближайшего соседа.
  
  
  W - Матрица весов
  V - Множество вершин
  E - Множество ребер


  Алгоритм для каждой, еще не принадлежащей дереву вершины v_i хранит указатель на ближайшую к ней вершину.
	Первая вершина дерева выбирается произвольно


	dist - массив весов еще не добавленных вершин, near - массив их названий.
	  Размеры этих массивов : |V| - i

  W_T - Общий вес минимального остовного дерева.

  Веса несуществующих ребер равны -1
  Выводить будем как матрицу

  Сначала попробую пойти через матрицу, потом через список

  */
// Число ребер должно быть не больше числа вершин в квадрате.
// C-T :: Поиск по коду
//Graph* Graph::findMinSpannigTree() {
//  
//
//}
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



}
istream& operator>> (istream& cin, Graph& g) {
  return cin;
}
ostream& operator<< (ostream& cout, const Graph& g) {


  cout << "---\n\nМатрица смежности " << g.name << "\n" << endl;
  
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

  Graph g(20, 200, 10, "G");
  cout << g;
}