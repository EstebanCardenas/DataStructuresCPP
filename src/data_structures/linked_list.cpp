#pragma once

#include <iostream>

template <typename T>
class LinkedListNode {
public:
	T data;
	LinkedListNode<T>* next;

	LinkedListNode(T data) {
		this->data = data;
		next = nullptr;
	}
};

template <typename T>
class LinkedList {
private:
	LinkedListNode<T>* head;
public:
	LinkedList() {
		head = nullptr;
	}

	LinkedList(T data) {
		head = new LinkedListNode<T>(data);
	}

	void addNode(T data) {
		LinkedListNode<T>* newNode = new LinkedListNode<T>(data);
		if (head == nullptr) {
			head = newNode;
		} else {
			LinkedListNode<T>* currentNode = head;
			while (currentNode->next != nullptr) {
				currentNode = currentNode->next;
			}
			currentNode->next = newNode;
		}
	}

	void removeNode(int idx) {
		if (head == nullptr || idx < 0) {
			return;
		}
		if (idx == 0) {
			head = head->next;
			return;
		}
		LinkedListNode<T>* currentNode = head;
		for (int i = 0; i < idx - 1; i++) {
			LinkedListNode<T>* nextNode = currentNode->next;
			if (nextNode != nullptr) {
				currentNode = nextNode;
			} else {
				break;
			}
		}
		if (currentNode->next != nullptr) {
			currentNode->next = currentNode->next->next;
		}
	}

	void reverse() {
		if (head == nullptr || head->next == nullptr) {
			return;
		}
		LinkedListNode<T>* previous = head;
		LinkedListNode<T>* current = head->next;
		head->next = nullptr;
		while (current->next != nullptr) {
			LinkedListNode<T>* next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}
		head = current;
		head->next = previous;
	}

	int length() {
		if (head == nullptr) {
			return 0;
		}
		int length = 1;
		LinkedListNode<T>* current = head;
		while (current->next != nullptr) {
			length++;
			current = current->next;
		}
		return length;
	}

	void print() {
		if (head != nullptr) {
			std::cout << head->data;
			LinkedListNode<T>* currentNode = head;
			while (currentNode->next != nullptr) {
				currentNode = currentNode->next;
				std::cout << "->" << currentNode->data;
			}
			std::cout << std::endl;
		}
	}
};
