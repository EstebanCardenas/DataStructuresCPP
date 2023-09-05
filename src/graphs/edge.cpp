#pragma once

struct Edge {
	int u;
	int v;

	Edge(int pU, int pV): u(pU), v(pV) {}

	bool operator==(const Edge& other) const {
		return u == other.u && v == other.v;
	}
};

class WeightedEdge: public Edge {
public:
	int w;

	WeightedEdge(int pU, int pV, int pW): Edge(pU, pV) {
		w = pW;
	}
};
