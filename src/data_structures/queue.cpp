#pragma once
#include "./linked_list.cpp"

template <typename T>
class Queue {
public:
    int maxSize;
    int size = 0;
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;

    Queue(T k) {
        maxSize = k;
        head = nullptr;
        tail = nullptr;
    }

    bool enQueue(T value) {
        if (size >= maxSize) {
            return false;
        }
        LinkedListNode<T>* newNode = new LinkedListNode<T>{ value };
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = tail->next;
        }
        size++;
        return true;
    }

    bool deQueue() {
        if (size == 0) {
            return false;
        }
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        size--;
        return true;
    }

    T front() {
        return head->data;
    }

    T rear() {
        return tail->data;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == maxSize;
    }
};
