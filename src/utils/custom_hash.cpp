#pragma once

#include <unordered_map>
#include "../graphs/edge.cpp"

using namespace std;

struct IntPairHash {
    size_t operator()(const pair<int, int> x) const {
        return x.first ^ x.second;
    }
};

struct EdgeHash {
	size_t operator()(const Edge edge) const {
		auto hasher = hash<int>{};
		return hasher(edge.u) ^ hasher(edge.v) << 1;
	}
};
