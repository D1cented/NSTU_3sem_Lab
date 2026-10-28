#include "Stack.h"
#include <fstream>
#include <vector>

MyStack::MyStack() : topNode(nullptr) {}

MyStack::~MyStack() {
    clear();
}

void MyStack::clear() {
    while (topNode) {
        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
    }
}

void MyStack::push(const std::string& val) {
    topNode = new Node(val, topNode);
}

bool MyStack::pop() {
    if (!topNode) return false;
    Node* tmp = topNode;
    topNode = topNode->next;
    delete tmp;
    return true;
}

std::string MyStack::peek() const {
    if (!topNode) return "";
    return topNode->val;
}

bool MyStack::empty() const {
    return topNode == nullptr;
}

void MyStack::print() const {
    std::cout << "[Stack (top -> bottom)]: ";
    Node* cur = topNode;
    while (cur) {
        std::cout << cur->val << (cur->next ? " | " : "");
        cur = cur->next;
    }
    std::cout << "\n";
}

void MyStack::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;
    // Сохраняем снизу вверх, чтобы при последовательном чтении стек восстановился в том же порядке
    std::vector<std::string> elems;
    Node* cur = topNode;
    while (cur) {
        elems.push_back(cur->val);
        cur = cur->next;
    }
    for (int i = (int)elems.size() - 1; i >= 0; --i) {
        out << elems[i] << "\n";
    }
}

void MyStack::loadFromFile(const std::string& filename) {
    clear();
    std::ifstream in(filename);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) push(line);
    }
}
