#pragma once

#include <vector>

using namespace std;

class MinQueue {
private:
	vector<int> queue;

	int leftChildIdx(int idx) {
		return 2 * idx + 1;
	}

	int rightChildIdx(int idx) {
		return leftChildIdx(idx) + 1;
	}

	int parentIdx(int idx) {
		return (idx - 1) / 2;
	}

	void swap(int i, int j) {
		int temp = queue[i];
		queue[i] = queue[j];
		queue[j] = temp;
	}

	void heapifyUp() {
		int idx = queue.size() - 1;
		int pIdx = parentIdx(idx);
		while (pIdx >= 0 && queue[pIdx] > queue[idx]) {
			swap(idx, pIdx);
			idx = pIdx;
			pIdx = parentIdx(idx);
		}
	}

	bool canKeepDownHeapify(int idx) {
		int leftIdx = leftChildIdx(idx);
		if (leftIdx < queue.size() && queue[leftIdx] < queue[idx]) {
			return true;
		}
		int rightIdx = rightChildIdx(idx);
		if (rightIdx < queue.size() && queue[rightIdx] < queue[idx]) {
			return true;
		}
		return false;
	}

	void heapifyDown(int idx) {
		while (canKeepDownHeapify(idx)) {
			int minIdx = leftChildIdx(idx);
			int rightIdx = rightChildIdx(idx);
			if (rightIdx < queue.size() && queue[rightIdx] < queue[minIdx]) {
				minIdx = rightIdx;
			}
			swap(idx, minIdx);
			idx = minIdx;
		}
	}
public:
	MinQueue() {};

	MinQueue(vector<int> startingElements) {
		for (int e : startingElements) {
			insert(e);
		}
	};

	void insert(int val) {
		queue.push_back(val);
		if (queue.size() == 1) return;
		heapifyUp();
	}

	int pop() {
		int result = queue[0];
		queue[0] = queue[queue.size() - 1];
		queue.pop_back();
		if (queue.size() > 1) {
			heapifyDown(0);
		}
		return result;
	}

	void remove(int val) {
		int idx = -1;
		for (int i = 0; i < queue.size(); i++) {
			if (queue[i] == val) {
				idx = i;
				break;
			}
		}
		if (idx == -1) {
			return;
		}
		queue[idx] = queue[queue.size() - 1];
		queue.pop_back();
		if (queue.size() > 1) {
			heapifyDown(idx);
		}
	}

	int top() {
		return queue[0];
	}
};
