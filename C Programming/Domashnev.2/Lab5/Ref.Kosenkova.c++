#include <iostream>
#include <vector>

using namespace std;

struct Edge {//ребро начало, конец, вес
    int v, u, w;
};

void sortEdges(vector <Edge>& v) {//сортировка рёбер
    for (int s = v.size() / 2; s > 0; s /= 2) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + s; j < v.size(); j += s) {
                if (v[i].w > v[j].w) {
                    swap(v[i], v[j]);
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int E, V;
    int total_weight = 0;

    vector <Edge> g;
    vector <Edge> res;
    vector <int> Vertex;

    cout << "Введите количество рёбер: ";
    cin >> E;
    cout << "Введите количество вершин: ";
    cin >> V;

    g.resize(E);
    Vertex.resize(V);

    for (int i = 0; i < V; ++i) {
        Vertex[i] = i;
    }

    cout << "Введите начальную и конечную вершину ребра, его вес : " << endl;
    for (int i = 0; i < E; ++i) {
        cin >> g[i].v >> g[i].u >> g[i].w;
    }

    sortEdges(g);

    for (int i = 0; i < E; ++i) {
        int v = Vertex[g[i].v];
        int u = Vertex[g[i].u];

        if (v != u) {
            total_weight += g[i].w;
            res.push_back(g[i]);
            int oldVertex = u, newVertex = v;
            for (int j = 0; j < V; ++j) {
                if (Vertex[j] == oldVertex) Vertex[j] = newVertex;
            }
        }
    }
    cout << endl << "Таблица веса рёбер(без циклов)" << endl;
    cout << "Начало\tКонец\tВес" << endl;

    for (int i = 0; i < res.size(); ++i) {
        cout << res[i].v << '\t' << res[i].u << '\t' << res[i].w <<
            endl;
    }
    cout << "Вес: " << total_weight;
}