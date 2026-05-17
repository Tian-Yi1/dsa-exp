#pragma once

template <typename T>
class BTNode {
public:
    T data;
    BTNode<T>* left;
    BTNode<T>* right;

    // 构造函数
    explicit BTNode(const T& val = T(), BTNode<T>* l = nullptr, BTNode<T>* r = nullptr)
        : data(val), left(l), right(r) {
    }

    // 方便修改数据的接口
    T getData() const { return data; }
    void setData(const T& val) { data = val; }

    BTNode<T>* getLeft() const { return left; }
    void setLeft(BTNode<T>* l) { left = l; }

    BTNode<T>* getRight() const { return right; }
    void setRight(BTNode<T>* r) { right = r; }
};
