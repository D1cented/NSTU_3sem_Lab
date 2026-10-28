#include "DoublyList.h"
#include <fstream>

DoublyList::DoublyList() : head(nullptr), tail(nullptr) {}

DoublyList::~DoublyList() {
    clear();
}

void DoublyList::clear() {
    while (head) {
        DNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}

void DoublyList::push_head(const std::string& val) {
    DNode* node = new DNode(val);
    if (!head) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void DoublyList::push_tail(const std::string& val) {
    DNode* node = new DNode(val);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

bool DoublyList::insert_after(const std::string& target, const std::string& val) {
    DNode* cur = head;
    while (cur && cur->val != target) cur = cur->next;
    if (!cur) return false;

    if (cur == tail) {
        push_tail(val);
        return true;
    }
    DNode* node = new DNode(val);
    node->next = cur->next;
    node->prev = cur;
    cur->next->prev = node;
    cur->next = node;
    return true;
}

bool DoublyList::insert_before(const std::string& target, const std::string& val) {
    DNode* cur = head;
    while (cur && cur->val != target) cur = cur->next;
    if (!cur) return false;

    if (cur == head) {
        push_head(val);
        return true;
    }
    DNode* node = new DNode(val);
    node->prev = cur->prev;
    node->next = cur;
    cur->prev->next = node;
    cur->prev = node;
    return true;
}

bool DoublyList::pop_head() {
    if (!head) return false;
    DNode* tmp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete tmp;
    return true;
}

bool DoublyList::pop_tail() {
    if (!tail) return false;
    DNode* tmp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete tmp;
    return true;
}

bool DoublyList::delete_after(const std::string& target) {
    DNode* cur = head;
    while (cur && cur->val != target) cur = cur->next;
    if (!cur || !cur->next) return false;

    DNode* target_node = cur->next;
    if (target_node == tail) return pop_tail();

    cur->next = target_node->next;
    target_node->next->prev = cur;
    delete target_node;
    return true;
}

bool DoublyList::delete_before(const std::string& target) {
    DNode* cur = head;
    while (cur && cur->val != target) cur = cur->next;
    if (!cur || !cur->prev) return false;

    DNode* target_node = cur->prev;
    if (target_node == head) return pop_head();

    target_node->prev->next = cur;
    cur->prev = target_node->prev;
    delete target_node;
    return true;
}

bool DoublyList::delete_value(const std::string& val) {
    DNode* cur = head;
    while (cur && cur->val != val) cur = cur->next;
    if (!cur) return false;

    if (cur == head) return pop_head();
    if (cur == tail) return pop_tail();

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
    return true;
}

std::string DoublyList::get(size_t index) const {
    DNode* cur = head;
    size_t i = 0;
    while (cur) {
        if (i == index) return cur->val;
        cur = cur->next;
        i++;
    }
    return "";
}

int DoublyList::search(const std::string& val) const {
    DNode* cur = head;
    int index = 0;
    while (cur) {
        if (cur->val == val) return index;
        cur = cur->next;
        index++;
    }
    return -1;
}

void DoublyList::print() const {
    std::cout << "[DoublyList (forward)]: ";
    DNode* cur = head;
    while (cur) {
        std::cout << cur->val << (cur->next ? " <-> " : "");
        cur = cur->next;
    }
    std::cout << "\n";
}

void DoublyList::print_reverse() const {
    std::cout << "[DoublyList (backward)]: ";
    DNode* cur = tail;
    while (cur) {
        std::cout << cur->val << (cur->prev ? " <-> " : "");
        cur = cur->prev;
    }
    std::cout << "\n";
}

void DoublyList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;
    DNode* cur = head;
    while (cur) {
        out << cur->val << "\n";
        cur = cur->next;
    }
}

void DoublyList::loadFromFile(const std::string& filename) {
    clear();
    std::ifstream in(filename);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) push_tail(line);
    }
}
