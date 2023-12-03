#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <string>
using namespace std;

class Graph {
public:

  Graph() : num_v{}, num_e{}, w_t{}, E(), V(), adjMatrix() {}

  Graph(int num_v, int num_e, int max_w, string name) : w_t{}, name{ name }, maxVerexNameLen{ static_cast<int>(to_string(num_v).length()) }, maxWeightLen{ static_cast<int>(to_string(max_w).length()) } {

	if (num_e > (num_v * (num_v - 1)) / 2) num_e = (num_v * (num_v - 1)) / 2;

	this->num_v = num_v;
	this->num_e = num_e;

	E.reserve(num_e);
	V.reserve(num_v);

	adjMatrix = vector< vector < double > >(num_v, vector< double >(num_v, -1));

	uniform_int_distribution<int> disIntW(0, max_w);
	uniform_int_distribution<int> disIntE(0, num_v - 1);

	random_device gen;

	for (int i = 0; i < num_e; ++i) {
	  E.emplace_back(disIntE(gen), disIntE(gen));
	}

	for (int i = 0; i < num_v; ++i) {
	  V.emplace_back(to_string(i));
	}

	for (int i = 0; i < num_e; ++i) {
	  adjMatrix[E[i].first][E[i].second] = disIntW(gen);
	  adjMatrix[E[i].second][E[i].first] = disIntW(gen);
	}

  }


  Graph* findMinSpannigTree();

  // Пользователь заполняет граф
  friend istream& operator>> (istream&, Graph&);
  friend ostream& operator<< (ostream&, const Graph&);

private:
  int num_v, num_e;
  int w_t;

  int maxVerexNameLen, maxWeightLen;

  string name;

  vector < pair < int, int > > E;
  vector < string > V;

  vector < vector < double > > adjMatrix;

};

