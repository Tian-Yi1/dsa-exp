/**
 * @file LinkedQueue.h
 * @brief 简单链式队列 (基本功能)
 */

#pragma once

#include <cstddef>  // size_t
#include <stdexcept> // std::out_of_range

 /**
  * @brief 链式队列类模板
  * @tparam T 元素类型
  */
template<typename T>
class LinkedQueue {
private:
    // 节点结构
    struct Node {
        T data;
        Node* next;
        Node(const T& val, Node* nxt = nullptr) : data(val), next(nxt) {}
    };

    Node* head;  // 队首
    Node* tail;  // 队尾
    size_t sz;   // 元素个数

public:
    /**
     * @brief 构造空队列
     */
    LinkedQueue() : head(nullptr), tail(nullptr), sz(0) {}

    /**
     * @brief 析构函数，释放所有节点
     */
    ~LinkedQueue() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    /**
     * @brief 入队，在队尾插入元素
     * @param val 要插入的值
     */
    void push(const T& val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        ++sz;
    }

    /**
     * @brief 出队，移除队首元素
     * @note 队列为空时调用将抛出异常
     * @throw std::out_of_range
     */
    void pop() {
        if (empty()) {
            throw std::out_of_range("LinkedQueue::pop(): empty queue");
        }
        Node* tmp = head;
        head = head->next;
        delete tmp;
        if (head == nullptr) {
            tail = nullptr;
        }
        --sz;
    }

    /**
     * @brief 访问队首元素
     * @return 队首元素的引用
     * @throw std::out_of_range 队列为空时
     */
    T& front() {
        if (empty()) {
            throw std::out_of_range("LinkedQueue::front(): empty queue");
        }
        return head->data;
    }

    /**
     * @brief 访问队首元素 (const 版本)
     * @return 队首元素的常引用
     */
    const T& front() const {
        if (empty()) {
            throw std::out_of_range("LinkedQueue::front(): empty queue");
        }
        return head->data;
    }

    /**
     * @brief 判断队列是否为空
     * @return true 空, false 非空
     */
    bool empty() const noexcept {
        return sz == 0;
    }

    /**
     * @brief 获取队列中元素个数
     * @return 元素数量
     */
    size_t size() const noexcept {
        return sz;
    }
};