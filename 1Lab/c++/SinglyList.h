#pragma once
#include <string>
#include <iostream>

struct SNode {
    std::string val;
    SNode* next;
    SNode(const std::string& v) : val(v), next(nullptr) {}
};

class SinglyList {
private:
    SNode* head;
    SNode* tail;

public:
    SinglyList();
    ~SinglyList();

    //добавление:
    void push_head(const std::string& val);
    void push_tail(const std::string& val);
    bool insert_after(const std::string& target, const std::string& val);
    bool insert_before(const std::string& target, const std::string& val);

    //удаления + по значению:
    bool pop_head();
    bool pop_tail();
    bool delete_after(const std::string& target);
    bool delete_before(const std::string& target);
    bool delete_value(const std::string& val);

    //чтение и поиск
    std::string get(size_t index) const;
    int search(const std::string& val) const;
    void print() const;
    void clear();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
