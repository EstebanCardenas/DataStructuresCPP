#pragma once

#include <vector>
#include <functional>

using namespace std;

template <typename T, typename N>
vector<N> mapVector(vector<T> src, function<N(T)> transform) {
	vector<N> result;
	for (const T e: src) {
		result.push_back(transform(e));
	}
	return result;
}
