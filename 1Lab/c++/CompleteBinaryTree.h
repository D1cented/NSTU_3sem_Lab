#pragma once
#include <string>
#include <iostream>

struct TNode {
    std::string val;
    TNode* left;
    TNode* right;
    TNode(const std::string& v) : val(v), left(nullptr), right(nullptr) {}
};

class CompleteBinaryTree {
private:
    TNode* root;

    void destroy(TNode* node);
    void printInOrder(TNode* node) const;
    void printPreOrder(TNode* node) const;

public:
    CompleteBinaryTree();
    ~CompleteBinaryTree();

    // Добавление элемента с сохранением структуры полного двоичного дерева
    void insert(const std::string& val);

    // Поиск элемента
    bool search(const std::string& val) const;

    // Вместо удаления: операция проверки на Complete Binary Tree
    bool isComplete() const;

    // Чтение структуры
    void printLevelOrder() const;
    void printTraversals() const;
    void clear();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
