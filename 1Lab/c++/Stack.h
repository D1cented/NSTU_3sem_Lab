#pragma once
#include <string>
#include <iostream>

class MyStack {
private:
    struct Node {
        std::string val;
        Node* next;
        Node(const std::string& v, Node* n = nullptr) : val(v), next(n) {}
    };
    Node* topNode;

public:
    MyStack();
    ~MyStack();

    void push(const std::string& val);
    bool pop();
    std::string peek() const;
    bool empty() const;
    void print() const;
    void clear();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
