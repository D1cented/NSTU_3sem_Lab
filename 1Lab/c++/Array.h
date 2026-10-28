#pragma once
#include <string>
#include <iostream>

class MyArray {
private:
    std::string* data;
    size_t capacity;
    size_t length;

    void resize(size_t new_capacity);

public:
    MyArray();
    ~MyArray();

    void push_back(const std::string& value);
    bool insert(size_t index, const std::string& value);
    std::string get(size_t index) const;
    bool remove(size_t index);
    bool replace(size_t index, const std::string& value);
    size_t size() const;
    void print() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
