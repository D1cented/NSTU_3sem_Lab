#include "Array.h"
#include <fstream>

MyArray::MyArray() : capacity(4), length(0) {
    data = new std::string[capacity];
}

MyArray::~MyArray() {
    delete[] data;
}

void MyArray::resize(size_t new_capacity) {
    std::string* new_data = new std::string[new_capacity];
    for (size_t i = 0; i < length; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void MyArray::push_back(const std::string& value) {
    if (length == capacity) {
        resize(capacity * 2);
    }
    data[length++] = value;
}

bool MyArray::insert(size_t index, const std::string& value) {
    if (index > length) return false;
    if (length == capacity) {
        resize(capacity * 2);
    }
    for (size_t i = length; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    length++;
    return true;
}

std::string MyArray::get(size_t index) const {
    if (index >= length) return "";
    return data[index];
}

bool MyArray::remove(size_t index) {
    if (index >= length) return false;
    for (size_t i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }
    length--;
    return true;
}

bool MyArray::replace(size_t index, const std::string& value) {
    if (index >= length) return false;
    data[index] = value;
    return true;
}

size_t MyArray::size() const {
    return length;
}

void MyArray::print() const {
    std::cout << "[Array]: ";
    for (size_t i = 0; i < length; ++i) {
        std::cout << data[i] << (i + 1 < length ? ", " : "");
    }
    std::cout << "\n";
}

void MyArray::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;
    for (size_t i = 0; i < length; ++i) {
        out << data[i] << "\n";
    }
}

void MyArray::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return;
    length = 0;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) push_back(line);
    }
}
