#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isTerminal;

    TrieNode() {
        isTerminal = false;
    }
};

class Trie {
private:
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode{};
    }

    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (!current->children.count(c)) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isTerminal = true;
    }

    bool search(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.count(c)) {
                current = current->children[c];
            }
            else {
                return false;
            }
        }
        return current->isTerminal;
    }

    bool startsWith(string prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (!current->children.count(c)) {
                return false;
            }
            current = current->children[c];
        }
        return true;
    }

    void remove(string word) {
        TrieNode* current = root;
        for (char c : word) {
            TrieNode* node = current->children[c];
            if (node == nullptr) {
                return;
            }
            current = node;
        }
        current->isTerminal = false;
    }
};
