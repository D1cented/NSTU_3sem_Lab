#include "SinglyList.h"
#include <fstream>

SinglyList::SinglyList() : head(nullptr), tail(nullptr) {}

SinglyList::~SinglyList() {
    clear();
}

void SinglyList::clear() {
    while (head) {
        SNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}

void SinglyList::push_head(const std::string& val) {
    SNode* node = new SNode(val);
    node->next = head;
    head = node;
    if (!tail) tail = head;
}

void SinglyList::push_tail(const std::string& val) {
    SNode* node = new SNode(val);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

bool SinglyList::insert_after(const std::string& target, const std::string& val) {
    SNode* cur = head;
    while (cur && cur->val != target) cur = cur->next;
    if (!cur) return false;

    SNode* node = new SNode(val);
    node->next = cur->next;
    cur->next = node;
    if (cur == tail) tail = node;
    return true;
}

bool SinglyList::insert_before(const std::string& target, const std::string& val) {
    if (!head) return false;
    if (head->val == target) {
        push_head(val);
        return true;
    }
    SNode* cur = head;
    while (cur->next && cur->next->val != target) cur = cur->next;
    if (!cur->next) return false;

    SNode* node = new SNode(val);
    node->next = cur->next;
    cur->next = node;
    return true;
}

bool SinglyList::pop_head() {
    if (!head) return false;
    SNode* tmp = head;
    head = head->next;
    delete tmp;
    if (!head) tail = nullptr;
    return true;
}

bool SinglyList::pop_tail() {
    if (!head) return false;
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return true;
    }
    SNode* cur = head;
    while (cur->next != tail) cur = cur->next;
    delete tail;
    tail = cur;
    tail->next = nullptr;
    return true;
}

bool SinglyList::delete_after(const std::string& target) {
    SNode* cur = head;
    while (cur && cur->val != target) cur = cur->next;
    if (!cur || !cur->next) return false;

    SNode* tmp = cur->next;
    cur->next = tmp->next;
    if (tmp == tail) tail = cur;
    delete tmp;
    return true;
}

bool SinglyList::delete_before(const std::string& target) {
    if (!head || head->val == target || !head->next) return false;
    if (head->next->val == target) {
        return pop_head();
    }
    SNode* prev = nullptr;
    SNode* cur = head;
    while (cur->next && cur->next->val != target) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur->next) return false;

    prev->next = cur->next;
    delete cur;
    return true;
}

bool SinglyList::delete_value(const std::string& val) {
    if (!head) return false;
    if (head->val == val) return pop_head();

    SNode* cur = head;
    while (cur->next && cur->next->val != val) cur = cur->next;
    if (!cur->next) return false;

    SNode* tmp = cur->next;
    cur->next = tmp->next;
    if (tmp == tail) tail = cur;
    delete tmp;
    return true;
}

std::string SinglyList::get(size_t index) const {
    SNode* cur = head;
    size_t i = 0;
    while (cur) {
        if (i == index) return cur->val;
        cur = cur->next;
        i++;
    }
    return "";
}

int SinglyList::search(const std::string& val) const {
    SNode* cur = head;
    int index = 0;
    while (cur) {
        if (cur->val == val) return index;
        cur = cur->next;
        index++;
    }
    return -1;
}

void SinglyList::print() const {
    std::cout << "[SinglyList]: ";
    SNode* cur = head;
    while (cur) {
        std::cout << cur->val << (cur->next ? " -> " : "");
        cur = cur->next;
    }
    std::cout << "\n";
}

void SinglyList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;
    SNode* cur = head;
    while (cur) {
        out << cur->val << "\n";
        cur = cur->next;
    }
}

void SinglyList::loadFromFile(const std::string& filename) {
    clear();
    std::ifstream in(filename);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) push_tail(line);
    }
}
