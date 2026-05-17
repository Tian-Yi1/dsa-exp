#pragma once
#include "BTNode.h"
#include <queue>
#include <functional>
#include <vector>
#include <string>
#include <cctype>
template <typename T>
class BTree {
private:
    BTNode<T>* root;

    // 递归删除所有结点（后序遍历）
    void clear(BTNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // 递归前序遍历
    void preOrder(BTNode<T>* node, const std::function<void(const T&)>& visit) const {
        if (node) {
            visit(node->data);
            preOrder(node->left, visit);
            preOrder(node->right, visit);
        }
    }

    // 递归中序遍历
    void inOrder(BTNode<T>* node, const std::function<void(const T&)>& visit) const {
        if (node) {
            inOrder(node->left, visit);
            visit(node->data);
            inOrder(node->right, visit);
        }
    }

    // 递归后序遍历
    void postOrder(BTNode<T>* node, const std::function<void(const T&)>& visit) const {
        if (node) {
            postOrder(node->left, visit);
            postOrder(node->right, visit);
            visit(node->data);
        }
    }

public:
    // 构造函数
    BTree() : root(nullptr) {}

    // 带根结点的构造函数
    explicit BTree(BTNode<T>* r) : root(r) {}

    // 析构函数
    ~BTree() { clear(root); }

    // 获取根结点指针（非const版本）
    BTNode<T>* getRoot() { return root; }
    // const版本
    const BTNode<T>* getRoot() const { return root; }

    // 设置根结点
    void setRoot(BTNode<T>* r) { root = r; }

    // 判断树是否为空
    bool isEmpty() const { return root == nullptr; }

    // 前序遍历（递归）
    void preOrderTraverse(const std::function<void(const T&)>& visit) const {
        preOrder(root, visit);
    }

    // 中序遍历（递归）
    void inOrderTraverse(const std::function<void(const T&)>& visit) const {
        inOrder(root, visit);
    }

    // 后序遍历（递归）
    void postOrderTraverse(const std::function<void(const T&)>& visit) const {
        postOrder(root, visit);
    }

    // 层次遍历（使用队列）
    void levelOrderTraverse(const std::function<void(const T&)>& visit) const {
        if (!root) return;
        std::queue<BTNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            BTNode<T>* cur = q.front();
            q.pop();
            visit(cur->data);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }
};
template <typename T>
BTree<T> byArray(const std::vector<T>& arr) {
    if (arr.empty()) {
        return BTree<T>(); // 空树
    }

    // 创建所有结点的指针数组，初始为 nullptr
    std::vector<BTNode<T>*> nodes(arr.size(), nullptr);
    for (size_t i = 0; i < arr.size(); ++i) {
        nodes[i] = new BTNode<T>(arr[i]);
    }

    // 对于索引 i (从0开始)，左孩子索引 = 2*i+1，右孩子索引 = 2*i+2
    for (size_t i = 0; i < arr.size(); ++i) {
        size_t leftIdx = 2 * i + 1;
        size_t rightIdx = 2 * i + 2;
        if (leftIdx < arr.size()) {
            nodes[i]->left = nodes[leftIdx];
        }
        if (rightIdx < arr.size()) {
            nodes[i]->right = nodes[rightIdx];
        }
    }

    return BTree<T>(nodes[0]);
}
// 辅助函数：跳过空白字符
static void skipSpace(const std::string& s, size_t& i) {
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
}

// 递归解析广义表，返回子树的根结点
static BTNode<char>* parseGList(const std::string& s, size_t& i,
    char leftBracket, char rightBracket, char separator) {
    skipSpace(s, i);
    if (i >= s.size()) return nullptr;

    // 读取结点值（一个字符）
    char val = s[i++];
    BTNode<char>* node = new BTNode<char>(val);

    skipSpace(s, i);
    // 如果遇到左括号，说明有子树
    if (i < s.size() && s[i] == leftBracket) {
        ++i; // 跳过 '('
        skipSpace(s, i);
        // 解析左子树
        node->left = parseGList(s, i, leftBracket, rightBracket, separator);
        skipSpace(s, i);
        // 期待分隔符
        if (i < s.size() && s[i] == separator) {
            ++i; // 跳过 ','
            skipSpace(s, i);
            node->right = parseGList(s, i, leftBracket, rightBracket, separator);
            skipSpace(s, i);
        }
        // 期待右括号
        if (i < s.size() && s[i] == rightBracket) {
            ++i; // 跳过 ')'
        }
    }
    return node;
}

// 广义表建树函数（结点值为 char）
inline BTree<char> byGList(const std::string& glist,
    char leftBracket = '(',
    char rightBracket = ')',
    char separator = ',') {
    if (glist.empty()) return BTree<char>();
    size_t idx = 0;
    BTNode<char>* root = parseGList(glist, idx, leftBracket, rightBracket, separator);
    return BTree<char>(root);
}