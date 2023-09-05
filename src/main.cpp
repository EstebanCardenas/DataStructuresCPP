//============================================================================
// Name        : HelloWorld.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>

#include "utils/vector_extension.cpp"
#include "graphs/graph.cpp"
#include "graphs/weighted_graph.cpp"
#include "graphs/edge.cpp"
#include "utils/graph_printer.cpp"

using namespace std;

int main() {
	vector<Edge> edges = {
			{1,0},
			{1,2},
			{0,3},
			{3,7},
			{3,4},
			{4,7},
			{4,6},
			{4,5},
			{6,5},
			{7,6},
	};
	GraphPrinter printer;
	UndirectedGraph g{edges};
	int s = 0;
	unordered_map<int, int> dist = g.shortestPaths(s);
	printer.shortestPaths(s, dist);
}
