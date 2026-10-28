#pragma once
#include <string>
#include <iostream>

struct DNode {
    std::string val;
    DNode* next;
    DNode* prev;
    DNode(const std::string& v) : val(v), next(nullptr), prev(nullptr) {}
};

class DoublyList {
private:
    DNode* head;
    DNode* tail;

public:
    DoublyList();
    ~DoublyList();

    // 4 способа добавления:
    void push_head(const std::string& val);
    void push_tail(const std::string& val);
    bool insert_after(const std::string& target, const std::string& val);
    bool insert_before(const std::string& target, const std::string& val);

    // 4 способа удаления + по значению:
    bool pop_head();
    bool pop_tail();
    bool delete_after(const std::string& target);
    bool delete_before(const std::string& target);
    bool delete_value(const std::string& val);

    // Чтение и поиск
    std::string get(size_t index) const;
    int search(const std::string& val) const;
    void print() const;
    void print_reverse() const;
    void clear();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
