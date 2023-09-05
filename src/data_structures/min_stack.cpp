#pragma once
#include <stack>
#include <limits.h>

using namespace std;

struct MinStackNode {
    int val;
    int minVal;

    MinStackNode(int val) {
        this->val = val;
        minVal = INT_MAX;
    }

    MinStackNode(int val, int minVal) {
        this->val = val;
        this->minVal = minVal;
    }
};

class MinStack {
private:
    stack<MinStackNode*> elements;
    int minVal = INT_MAX;
public:
    MinStack() {}

    void push(int val) {
        MinStackNode* node = new MinStackNode{ val, minVal };
        elements.push(node);
        if (val < minVal) {
            minVal = val;
        }
    }

    void pop() {
        MinStackNode* node = elements.top();
        elements.pop();
        minVal = node->minVal;
    }

    int top() {
        return elements.top()->val;
    }

    int getMin() {
        return minVal;
    }
};
