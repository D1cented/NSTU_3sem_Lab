#include "Queue.h"
#include <fstream>

MyQueue::MyQueue() : head(nullptr), tail(nullptr) {}

MyQueue::~MyQueue() {
    clear();
}

void MyQueue::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}

void MyQueue::push(const std::string& val) {
    Node* node = new Node(val);
    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

bool MyQueue::pop() {
    if (!head) return false;
    Node* tmp = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete tmp;
    return true;
}

std::string MyQueue::peek() const {
    if (!head) return "";
    return head->val;
}

bool MyQueue::empty() const {
    return head == nullptr;
}

void MyQueue::print() const {
    std::cout << "[Queue (front -> back)]: ";
    Node* cur = head;
    while (cur) {
        std::cout << cur->val << (cur->next ? " <- " : "");
        cur = cur->next;
    }
    std::cout << "\n";
}

void MyQueue::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;
    Node* cur = head;
    while (cur) {
        out << cur->val << "\n";
        cur = cur->next;
    }
}

void MyQueue::loadFromFile(const std::string& filename) {
    clear();
    std::ifstream in(filename);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) push(line);
    }
}
