#pragma once
#include <vector>

using namespace std;

struct UnionFind {
	vector<int> parent;
	vector<int> rank;
	int connectedComponents;

	UnionFind(int size) {
		parent.resize(size);
		rank.resize(size);
		for (int i = 0; i < size; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
		connectedComponents = size;
	}

	int find(int v) {
		if (v != parent[v]) {
			parent[v] = find(parent[v]);
		}
		return parent[v];
	}

	bool makeUnion(int u, int v) {
		int parentU = find(u);
		int parentV = find(v);

		if (parentU == parentV) return false;
		if (rank[parentU] > rank[parentV]) {
			parent[parentV] = parentU;
		}
		else if (rank[parentU] < rank[parentV]) {
			parent[parentU] = parentV;
		}
		else {
			parent[parentV] = parentU;
			rank[parentU]++;
		}
		connectedComponents--;
		return true;
	}

	bool isConnected(int u, int v) {
		return find(u) == find(v);
	}
};
