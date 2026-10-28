#pragma once
#include <string>
#include <iostream>

class MyQueue {
private:
    struct Node {
        std::string val;
        Node* next;
        Node(const std::string& v) : val(v), next(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    MyQueue();
    ~MyQueue();

    void push(const std::string& val);
    bool pop();
    std::string peek() const;
    bool empty() const;
    void print() const;
    void clear();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
