#pragma once

#include <iostream>
#include <unordered_map>

using namespace std;

struct GraphPrinter {
	void shortestPaths(int s, unordered_map<int, int> dist) {
		for (auto p: dist) {
			int v = p.first, d = p.second;
			cout << s << "->" << v << ": " << d << endl;
		}
	}
};
