#pragma once

#include <vector>
#include <queue>
#include <functional>

#include "graph.cpp"
#include "edge.cpp"
#include "unordered_map"

#include "../utils/custom_hash.cpp"
#include "union_find.cpp"

using namespace std;

class WeightedDirectedGraph: public Graph {
public:
	vector<WeightedEdge> edges;
	unordered_map<Edge, int, EdgeHash> weights;

	WeightedDirectedGraph(const vector<WeightedEdge> edges) {
		for (WeightedEdge edge: edges) {
			adjList[edge.u].push_back(edge.v);
			adjList[edge.v];
			weights[edge] = edge.w;
		}
		this->edges = edges;
	}

	unordered_map<int, int> bellmanFord(int s) const {
		unordered_map<int, int> dist;
		for (auto p: adjList) {
			int vertex = p.first;
			dist[vertex] = INT_MAX;
		}
		dist[s] = 0;

		int V = adjList.size();
		for (int i=0; i<V-1; i++) {
			for (WeightedEdge edge: edges) {
				if (dist[edge.u] == INT_MAX) continue;
				if (dist[edge.u] + edge.w < dist[edge.v]) {
					dist[edge.v] = dist[edge.u] + edge.w;
				}
			}
		}
		return dist;
	}

	unordered_map<int, int> dijkstra(int s) {
		unordered_map<int, int> dist;
		for (auto p: adjList) {
			int v = p.first;
			dist[v] = INT_MAX;
		}
		dist[s] = 0;

		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({0, s});
		while (!pq.empty()) {
			pair<int, int> p = pq.top(); pq.pop();
			int u = p.second;
			for (int v: adjList[u]) {
				int weight = weights[{u,v}];
				if (dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
					pq.push({dist[v], v});
				}
			}
		}
		return dist;
	}

	unordered_map<int, unordered_map<int, int>> floydWarshall() {
		unordered_map<int, unordered_map<int, int>> dist;
		// Create adjacency matrix
		for (auto pu: adjList) {
			int u = pu.first;
			for (auto pv: adjList) {
				int v = pv.first;
				if (u == v) dist[u][v] = 0;
				else {
					dist[u][v] = weights.count({u,v}) ? weights[{u,v}] : INT_MAX;
				}
			}
		}
		// Floyd-Warshall
		for (auto pk: adjList) {
			int k = pk.first;
			for (auto pi: adjList) {
				int i = pi.first;
				for (auto pj: adjList) {
					int j = pj.first;
					if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;
					if (dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}

		return dist;
	}

	vector<WeightedEdge> kruskalMst() {
		// Create priority queue
		struct Comparator {
			bool operator()(WeightedEdge a, WeightedEdge b) const {
				return a.w > b.w;
			}
		};
		int V = adjList.size();
		unordered_map<int, int> ids;
		int id = 0;
		for (auto p: adjList) {
			int v = p.first;
			ids[v] = id;
			id++;
		}
		priority_queue<WeightedEdge, vector<WeightedEdge>, Comparator> pq(edges.begin(), edges.end());

		// Create MST
		UnionFind uf{V};
		vector<WeightedEdge> mst;
		while (!pq.empty() && ((int) mst.size()) < V-1) {
			WeightedEdge edge = pq.top(); pq.pop();
			int uId = ids[edge.u], vId = ids[edge.v];
			if (!uf.isConnected(uId, vId)) {
				uf.makeUnion(uId, vId);
				mst.push_back(edge);
			}
		}
		return mst;
	}

	vector<WeightedEdge> primMst() {
		struct Comparator {
			bool operator()(WeightedEdge a, WeightedEdge b) const {
				return a.w > b.w;
			}
		};
		unordered_set<int> visited;
		priority_queue<WeightedEdge, vector<WeightedEdge>, Comparator> pq;
		vector<WeightedEdge> mst;

		// Visit first vertex
		int f = edges[0].v;
		visited.insert(f);
		for (int adj: adjList[f]) {
			if (!visited.count(adj)) {
				pq.push({f, adj, weights[{f, adj}]});
			}
		}

		while (!pq.empty()) {
			WeightedEdge edge = pq.top(); pq.pop();
			if (visited.count(edge.u) && visited.count(edge.v)) continue;
			mst.push_back(edge);

			if (!visited.count(edge.u)) {
				visited.insert(edge.u);
				for (int adj: adjList[edge.u]) {
					if (!visited.count(adj)) {
						pq.push({edge.u, adj, weights[{edge.u, adj}]});
					}
				}
			}
			if (!visited.count(edge.v)) {
				visited.insert(edge.v);
				for (int adj: adjList[edge.v]) {
					if (!visited.count(adj)) {
						pq.push({edge.v, adj, weights[{edge.v, adj}]});
					}
				}
			}
		}
		return mst;
	}
};
