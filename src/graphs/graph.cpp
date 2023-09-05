#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <functional>

#include "edge.cpp"

using namespace std;

class Graph {
public:
	unordered_map<int, vector<int>> adjList;

	void dfs(int root, function<void(int)> processNode) {
		unordered_set<int> visited;

		function<void(int)> helper = [&](int v) {
			visited.insert(v);
			processNode(v);

			for (int adj: adjList[v]) {
				if (!visited.count(adj)) {
					helper(adj);
				}
			}
		};
		helper(root);
	}

	void bfs(int root, function<void(int, int)> processNode) {
		unordered_set<int> visited;
		queue<pair<int, int>> q;
		q.push({root, 0});

		while (!q.empty()) {
			pair<int, int> current = q.front(); q.pop();
			int v = current.first, level = current.second;
			visited.insert(v);
			processNode(v, level);

			for (int adj: adjList[v]) {
				if (!visited.count(adj)) {
					q.push({adj, level + 1});
				}
			}
		}
	}

	unordered_map<int, int> shortestPaths(int s) {
		unordered_map<int, int> dist;
		for (auto p: adjList) {
			int v = p.first;
			dist[v] = INT_MAX;
		}
		dist[s] = 0;

		unordered_set<int> visited;
		queue<pair<int, int>> q;
		q.push({s, 0});
		while (!q.empty()) {
			pair<int, int> p = q.front(); q.pop();
			int u = p.first, l = p.second;
			visited.insert(u);

			if (l < dist[u]) {
				dist[u] = l;
			}

			for (int v: adjList[u]) {
				if (!visited.count(v)) {
					q.push({v, l + 1});
				}
			}
		}
		return dist;
	}
};

class DirectedGraph: public Graph {
public:
	DirectedGraph() {}

	DirectedGraph(const vector<Edge> edges) {
		for (Edge edge: edges) {
			adjList[edge.u].push_back(edge.v);
			adjList[edge.v];
		}
	}

	void addEdge(Edge edge) {
		adjList[edge.u].push_back(edge.v);
		adjList[edge.v];
	}

	stack<int> topSort() {
		stack<int> sorted;
		unordered_set<int> visited;

		function<void(int)> topDfs = [&](int u) {
			visited.insert(u);
			for (int v: adjList[u]) {
				if (!visited.count(v)) {
					topDfs(v);
				}
			}
			sorted.push(u);
		};

		for (auto p: adjList) {
			int v = p.first;
			if (!visited.count(v)) {
				topDfs(v);
			}
		}
		return sorted;
	}

	vector<int> kahnTopSort() {
		unordered_map<int, int> inOrder;
		for (auto p: adjList) {
			int u = p.first;
			if (!inOrder.count(u)) {
				inOrder[u] = 0;
			}
			for (int v: adjList[u]) {
				inOrder[v]++;
			}
		}

		queue<int> q;
		for (auto p: inOrder) {
			if (p.second == 0) {
				q.push(p.first);
			}
		}

		int count = 0;
		vector<int> sorted;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			sorted.push_back(u);
			for (int v: adjList[u]) {
				if (--inOrder[v] == 0) {
					q.push(v);
				}
			}
			count++;
		}

		if (count != ((int) adjList.size())) {
			cout << "There exists a cycle in the graph";
			return {};
		}

		return sorted;
	}

	bool hasCycle() {
		unordered_set<int> visited;
		unordered_set<int> recStack;
		function<bool(int)> helper = [&](int u) -> bool {
			if (recStack.count(u)) return true;
			if (visited.count(u)) return false;
			visited.insert(u);
			recStack.insert(u);
			for (int v: adjList[u]) {
				if (helper(v)) return true;
			}
			recStack.erase(u);
			return false;
		};
		for (auto p: adjList) {
			int v = p.first;
			if (helper(v)) return true;
		}
		return false;
	}

	DirectedGraph getReverse() {
		DirectedGraph ret{};
		for (auto p: adjList) {
			int u = p.first;
			for (int v: adjList[u]) {
				ret.addEdge({v, u});
			}
		}
		return ret;
	}

	vector<vector<int>> getSCCs() {
		stack<int> st = topSort();

		// Perform reverse DFS
		DirectedGraph reverse = getReverse();
		unordered_set<int> visited;
		vector<vector<int>> sccs;

		function<void(int, vector<int>&)> reverseDfs = [&](int u, vector<int>& scc) {
			visited.insert(u);
			scc.push_back(u);
			for (int v: reverse.adjList[u]) {
				if (!visited.count(v)) {
					reverseDfs(v, scc);
				}
			}
		};

		while (!st.empty()) {
			int u = st.top(); st.pop();
			if (!visited.count(u)) {
				vector<int> scc;
				reverseDfs(u, scc);
				sccs.push_back(scc);
			}
		}
		return sccs;
	}
};

class UndirectedGraph: public Graph {
public:
	UndirectedGraph(const vector<Edge> edges) {
		for (const Edge edge: edges) {
			adjList[edge.u].push_back(edge.v);
			adjList[edge.v].push_back(edge.u);
		}
	}
};
