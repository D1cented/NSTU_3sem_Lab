#include "CompleteBinaryTree.h"
#include <queue>
#include <fstream>

CompleteBinaryTree::CompleteBinaryTree() : root(nullptr) {}

CompleteBinaryTree::~CompleteBinaryTree() {
    destroy(root);
}

void CompleteBinaryTree::destroy(TNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void CompleteBinaryTree::clear() {
    destroy(root);
    root = nullptr;
}

//вставка на первый свободный уровень слева направо
void CompleteBinaryTree::insert(const std::string& val) {
    TNode* node = new TNode(val);
    if (!root) {
        root = node;
        return;
    }

    std::queue<TNode*> q;
    q.push(root);
    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();

        if (!cur->left) {
            cur->left = node;
            return;
        } else {
            q.push(cur->left);
        }

        if (!cur->right) {
            cur->right = node;
            return;
        } else {
            q.push(cur->right);
        }
    }
}

bool CompleteBinaryTree::search(const std::string& val) const {
    if (!root) return false;
    std::queue<TNode*> q;
    q.push(root);
    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();

        if (cur->val == val) return true;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return false;
}

//проверка Complete Binary Tree соблюд ли обход BFS (с флагом неполного узла)
bool CompleteBinaryTree::isComplete() const {
    if (!root) return true;
    std::queue<TNode*> q;
    q.push(root);
    bool seen_non_full_node = false;

    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();

        if (cur->left) {
            if (seen_non_full_node) return false;
            q.push(cur->left);
        } else {
            seen_non_full_node = true;
        }

        if (cur->right) {
            if (seen_non_full_node) return false;
            q.push(cur->right);
        } else {
            seen_non_full_node = true;
        }
    }
    return true;
}

void CompleteBinaryTree::printInOrder(TNode* node) const {
    if (!node) return;
    printInOrder(node->left);
    std::cout << node->val << " ";
    printInOrder(node->right);
}

void CompleteBinaryTree::printPreOrder(TNode* node) const {
    if (!node) return;
    std::cout << node->val << " ";
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void CompleteBinaryTree::printLevelOrder() const {
    if (!root) {
        std::cout << "<Tree is empty>\n";
        return;
    }
    std::queue<TNode*> q;
    q.push(root);
    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();
        std::cout << cur->val << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    std::cout << "\n";
}

void CompleteBinaryTree::printTraversals() const {
    std::cout << "[Tree Level-order]: ";
    printLevelOrder();
    std::cout << "[Tree In-order]:    ";
    printInOrder(root);
    std::cout << "\n[Tree Pre-order]:   ";
    printPreOrder(root);
    std::cout << "\n";
}

void CompleteBinaryTree::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open() || !root) return;
    //cохранение в Level-order
    std::queue<TNode*> q;
    q.push(root);
    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();
        out << cur->val << "\n";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

void CompleteBinaryTree::loadFromFile(const std::string& filename) {
    clear();
    std::ifstream in(filename);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) insert(line);
    }
}
