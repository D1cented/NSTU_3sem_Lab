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

    // 
    void insert(const std::string& val);

    // 
    bool search(const std::string& val) const;

    //вместо проверка на Complete Binary Tree
    bool isComplete() const;

    //чтение
    void printLevelOrder() const;
    void printTraversals() const;
    void clear();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
