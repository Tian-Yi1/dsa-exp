#pragma once
#include <iostream>
#include <stdexcept>

// ========================== 栈抽象基类 ==========================
template <typename T>
class Stack {
public:
    virtual ~Stack() = default;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
    virtual T& top() = 0;
    virtual const T& top() const = 0;
};

// ========================== 顺序栈（动态数组） ==========================
template <typename T>
class SequencedStack : public Stack<T> {
private:
    T* data;
    int capacity;
    int topIndex;   // 栈顶元素索引，-1 表示空栈

    void expand() {
        capacity = capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i <= topIndex; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

public:
    SequencedStack(int initCap = 10) : capacity(initCap), topIndex(-1) {
        if (capacity <= 0) capacity = 10;
        data = new T[capacity];
    }

    ~SequencedStack() { delete[] data; }

    bool empty() const override { return topIndex == -1; }

    int size() const override { return topIndex + 1; }

    void push(const T& value) override {
        if (topIndex + 1 >= capacity)
            expand();
        data[++topIndex] = value;
    }

    void pop() override {
        if (empty())
            throw std::out_of_range("SequencedStack::pop(): empty stack");
        --topIndex;
    }

    T& top() override {
        if (empty())
            throw std::out_of_range("SequencedStack::top(): empty stack");
        return data[topIndex];
    }

    const T& top() const override {
        if (empty())
            throw std::out_of_range("SequencedStack::top(): empty stack");
        return data[topIndex];
    }
};

// ========================== 链式栈（单向链表） ==========================
template <typename T>
class LinkedStack : public Stack<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val, Node* nxt = nullptr) : data(val), next(nxt) {}
    };
    Node* head;   // 栈顶指针（链表头部）
    int count;

public:
    LinkedStack() : head(nullptr), count(0) {}

    ~LinkedStack() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() const override { return count == 0; }

    int size() const override { return count; }

    void push(const T& value) override {
        Node* newNode = new Node(value, head);
        head = newNode;
        ++count;
    }

    void pop() override {
        if (empty())
            throw std::out_of_range("LinkedStack::pop(): empty stack");
        Node* temp = head;
        head = head->next;
        delete temp;
        --count;
    }

    T& top() override {
        if (empty())
            throw std::out_of_range("LinkedStack::top(): empty stack");
        return head->data;
    }

    const T& top() const override {
        if (empty())
            throw std::out_of_range("LinkedStack::top(): empty stack");
        return head->data;
    }
};

