#pragma once
#include <iostream>
#include <stdexcept>
#include <iterator>
#include "BaseList.h"
#include "globalFunc.h"

template <typename T>
class SLNode {
private:
    T _item;                            //数据域 (renamed to avoid clash with accessor)
    SLNode<T>* _next;                //指针域 (renamed to avoid clash with accessor)
public:
    //==================================公有函数==================================

        //数据接口
    const T item() const {
        return _item;
    }
    //修改item
    void changeItem(T newItem) {
        _item = newItem;
    }
    T& item() {
        return _item;
    }
    //指针接口
    const SLNode<T>* next() const {
        return _next;
    }
    SLNode<T>*& next() {
        return _next;
    }
    //修改指针
    void changeNext(SLNode<T>* newNext) {
        _next = newNext;
    }
    //缺省构造
    SLNode() :_next(nullptr), _item{} {

    }
    //带参构造
    SLNode(const T& k) :_item(k), _next(nullptr) {

    }
    //拷贝构造
    //SLNode(const SLNode<T>& other) :_item(other._item), _next(other._next) {}
    //析构函数
    ~SLNode() {
        _next = nullptr;
    }
};

template <typename T>
class CircularLinkedList : public IList<T> {
private:
    SLNode<T>* _head;
    unsigned int _count;

    void clear() {
        SLNode<T>* curr = _head;
        while (curr != nullptr) {
            SLNode<T>* next = curr->next();
            delete curr;
            curr = next;
        }
        _head = nullptr;
        _count = 0;
    }

public:
        class iterator {
        private:
            SLNode<T>* curr;
            friend class CircularLinkedList<T>;

            template<std::input_iterator Itr, typename TII>
            friend void ::dispose(Itr, TII);
        public:
            //类型标签
            using value_type = T;                            //元素类型
            using pointer = T*;                                //元素指针
            using reference = T&;                            //元素引用
            using difference_type = ptrdiff_t;                //差值类型
            using iterator_category = std::forward_iterator_tag;    //随机访问

            iterator(SLNode<T>* p = nullptr) :curr(p) {}

            reference operator*() const {
                return curr->item();
            }

            pointer operator->() const {
                return &(curr->item());
            }

            iterator& operator++() {//前置自增
                curr = curr->next();
                return *this;
            }
            iterator operator++(int) {//后置自增
                iterator temp = *this;
                curr = curr->next();
                return temp;
            }

            bool operator==(const iterator& other) const {
                return curr == other.curr;
            }

            bool operator!=(const iterator& other) const {
                return curr != other.curr;
            }
        };
        class const_iterator {// const 迭代器
        private:
            SLNode<T>* curr;
            friend class CircularLinkedList<T>;
        public:
            using value_type = const T;                            //元素类型
            using pointer = const T*;                                //元素指针
            using reference = const T&;                            //元素引用
            using difference_type = ptrdiff_t;                //差值类型
            using iterator_category = std::forward_iterator_tag;    //随机访问

            const_iterator(SLNode<T>* p = nullptr) :curr(p) {}
            const_iterator(const iterator& other) :curr(other.curr) {}

            reference operator*() const {
                return curr->item();
            }

            pointer operator->() const {
                return &(curr->item());
            }

            const_iterator& operator++() {
                curr = curr->next();
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator temp = *this;
                curr = curr->next();
                return temp;
            }

            bool operator==(const const_iterator& other) const {
                return curr == other.curr;
            }

            bool operator!=(const const_iterator& other) const {
                return curr != other.curr;
            }
        };
    CircularLinkedList() : _head(nullptr), _count(0) {}
    ~CircularLinkedList() { clear(); }
    CircularLinkedList(const CircularLinkedList& other) : _head(nullptr), _count(0) {
        if (!other._head) return;
        _head = new SLNode<T>(other._head->item());
        SLNode<T>* dest = _head;
        SLNode<T>* src = other._head->next();
        while (src) {
            dest->next() = new SLNode<T>(src->item());
            dest = dest->next();
            src = src->next();
        }
        _count = other._count;
    }
    CircularLinkedList(CircularLinkedList&& other) noexcept
        : _head(other._head), _count(other._count) {
        other._head = nullptr;
        other._count = 0;
    }
    CircularLinkedList& operator=(const CircularLinkedList& other) {
        if (this != &other) {
            clear();
            if (!other._head) return *this;
            _head = new SLNode<T>(other._head->item());
            SLNode<T>* dest = _head;
            SLNode<T>* src = other._head->next();
            while (src) {
                dest->next() = new SLNode<T>(src->item());
                dest = dest->next();
                src = src->next();
            }
            _count = other._count;
        }
        return *this;
    }
    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            _head = other._head;
            _count = other._count;
            other._head = nullptr;
            other._count = 0;
        }
        return *this;
    }

    // 迭代器入口
    iterator begin() { return iterator(_head); }
    iterator end() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(_head); }
    const_iterator end() const { return const_iterator(nullptr); }

    // 容量
    bool empty() const override { return _count == 0; }
    unsigned int size() const override { return _count; }

    // 插入
    void push_front(const T& val) override {
        SLNode<T>* newNode = new SLNode<T>(val);
        newNode->next() = _head;
        _head = newNode;
        ++_count;
    }
    void push_back(const T& val) override {
        SLNode<T>* newNode = new SLNode<T>(val);
        if (!_head) {
            _head = newNode;
        }
        else {
            SLNode<T>* p = _head;
            while (p->next()) p = p->next();
            p->next() = newNode;
        }
        ++_count;
    }
    void insert(int i, const T& val) override {
        if (i < 0 || i >(int)_count) throw std::out_of_range("insert index out of range");
        if (i == 0) { push_front(val); return; }
        auto it = begin();
        for (int pos = 0; pos < i - 1; ++pos) ++it;
        SLNode<T>* newNode = new SLNode<T>(val);
        newNode->next() = it.getNode()->next();
        it.getNode()->next() = newNode;
        ++_count;
    }

    // 删除
    void pop_front() override {
        if (empty()) throw std::out_of_range("pop_front on empty list");
        SLNode<T>* tmp = _head;
        _head = _head->next();
        delete tmp;
        --_count;
    }
    void pop_back() override {
        if (empty()) throw std::out_of_range("pop_back on empty list");
        if (_count == 1) {
            delete _head;
            _head = nullptr;
        }
        else {
            auto it = begin();
            for (unsigned int i = 0; i < _count - 2; ++i) ++it;
            delete it.getNode()->next();
            it.getNode()->next() = nullptr;
        }
        --_count;
    }
    bool removeAt(unsigned int index) override {
        if (index >= _count) return false;
        if (index == 0) {
            pop_front();
            return true;
        }
        auto it = begin();
        for (unsigned int i = 0; i < index - 1; ++i) ++it;
        SLNode<T>* toDel = it.getNode()->next();
        it.getNode()->next() = toDel->next();
        delete toDel;
        --_count;
        return true;
    }

    // 访问
    T& operator[](unsigned int index) override {
        auto it = begin();
        for (unsigned int i = 0; i < index; ++i) ++it;
        return *it;
    }
    const T& operator[](unsigned int index) const override {
        auto it = begin();
        for (unsigned int i = 0; i < index; ++i) ++it;
        return *it;
    }

    // 打印
    void print(std::ostream& os = std::cout) const override {
        os << "CircularLinkedList:";
        for (auto it = begin(); it != end(); ++it)
            os << ' ' << *it;
        os << '\n';
    }
};
