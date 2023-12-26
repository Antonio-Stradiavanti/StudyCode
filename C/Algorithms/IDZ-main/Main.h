#pragma once
#pragma once
#include <vector>
#include <map>
#include <random>
#include <iostream>
#include <string>
using namespace std;
template < class T >
int numDigits(T num);
class Graph {
public:

  Graph() : num_v{ 0 }, num_e{ 0 }, w_t{ 0.0 }, E(), V(), adjMatrix(), maxVertexNameLen{}, maxWeightLen{}, name{}
  {}

  /* Graph(Graph&& g) : E{ move(g.E) }, V{ move(g.V) }, adjMatrix{ move(g.adjMatrix) }, num_v{ g.num_v }, num_e{ g.num_e }, w_t{ g.w_t }, maxVertexNameLen{ g.maxVertexNameLen }, maxWeightLen{ g.maxWeightLen }, name{ g.name }
  {
	g.num_e = 0; g.num_v = 0; g.w_t = 0;

	g.name.clear();
  } */
  Graph(int num_v, int num_e, int max_w, string name) : max_w{ max_w }, w_t{ 0 }, name{ name }, maxVertexNameLen{ numDigits(num_v) }, maxWeightLen{ numDigits(max_w) + 5 }
  {

	if (num_e > (num_v * (num_v - 1)) / 2) num_e = (num_v * (num_v - 1)) / 2;

	this->num_v = num_v;
	this->num_e = num_e;

	genGraph();
	compTotalWeight();

  }

  void genSample() {
	num_v = 6;
	name = "G";
	max_w = 100;

	adjMatrix = vector< vector < double > >(num_v, vector< double >(num_v, -1));

	V = vector<string>{ "0", "1", "2", "3", "4", "5" };

	adjMatrix[0][1] = 8.9; adjMatrix[0][5] = 7.0;
	adjMatrix[1][0] = 8.9; adjMatrix[1][2] = 5.5; adjMatrix[1][3] = 9.0;
	adjMatrix[2][1] = 5.5; adjMatrix[2][4] = 24.9; adjMatrix[2][5] = 15.5;
	adjMatrix[3][1] = 9.0; adjMatrix[3][4] = 10.0; adjMatrix[3][5] = 67.0;
	adjMatrix[4][2] = 24.9; adjMatrix[4][3] = 10.0;
	adjMatrix[5][0] = 7.0; adjMatrix[5][2] = 15.5; adjMatrix[5][3] = 67.0;

	for (int i = 0; i < 6; ++i) {
	  for (int j = 0; j < 6; ++j) {
		w_t += adjMatrix[i][j];
	  }
	}
  }

  Graph(const Graph& g) : num_e{ g.num_e }, num_v{ g.num_v }, w_t{ g.w_t }, name{ g.name }, maxVertexNameLen{ g.maxVertexNameLen }, maxWeightLen{ g.maxWeightLen }
  {
	V = g.V;
	E = g.E;
	adjMatrix = g.adjMatrix;
  }

  Graph& operator= (const Graph& g) {
	if (this == &g)
	  return *this;

	this->num_e = g.num_e;
	this->num_v = g.num_v;
	this->w_t = g.w_t;
	this->max_w = g.max_w;

	this->name = g.name;

	this->maxVertexNameLen = g.maxVertexNameLen;
	this->maxWeightLen = g.maxWeightLen;

	this->V = g.V;
	this->E = g.E;
	this->adjMatrix = g.adjMatrix;

	return *this;
  }


  Graph findMinSpannigTree();
  // Пользователь заполняет граф
  friend istream& operator>> (istream&, Graph&);
  friend ostream& operator<< (ostream&, const Graph&);

private:

  void compTotalWeight() {
	for (int i = 0; i < num_e; ++i) {
	  w_t += adjMatrix[E[i].first][E[i].second];
	}
  }

  void genGraph() {

	E.reserve(num_e);
	V.reserve(num_v);

	adjMatrix = vector< vector < double > >(num_v, vector< double >(num_v, -1));

	uniform_int_distribution<int> disIntW(0, max_w - 1);
	uniform_real_distribution<double> disDoubleW(0, 1);


	uniform_int_distribution<int> disIntE(0, num_v - 1);

	random_device gen;
	int f = 0, s = 0;
	for (int i = 0; i < num_e; ++i) {
	  f = disIntE(gen);
	  s = disIntE(gen);
	  if (f != s)
		E.emplace_back(f, s);
	}

	for (int i = 0; i < num_v; ++i) {
	  V.emplace_back(to_string(i));
	}

	for (int i = 0; i < num_e; ++i) {
	  double tmp_w = disIntW(gen) + disDoubleW(gen);
	  f = E[i].first; s = E[i].second;
	  if (f != s) {
		adjMatrix[f][s] = tmp_w;
		adjMatrix[s][f] = tmp_w;
	  }
	}

  }

  int num_v, num_e;
  double w_t;
  int max_w;

  int maxVertexNameLen, maxWeightLen;

  string name;

  vector < pair < int, int > > E;
  // должен быть map
  vector<string> V;

  vector < vector < double > > adjMatrix;

};

