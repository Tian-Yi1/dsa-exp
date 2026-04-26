#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <string>
#include <sstream>
#include "globalFunc.h"
#include "BaseList.h"

// Forward declarations to allow making operator<< a friend without shadowing template parameters
template <typename T> class SLinkedList;
template <typename T> std::ostream& operator<<(std::ostream& os, const SLinkedList<T>& rhs);

//==================================SLNode==================================

//单个数据类SLNode
template <typename T>
class SLNode {
private:
	T _item;                            //数据域 (renamed to avoid clash with accessor)
	SLNode<T>* _next;                //指针域 (renamed to avoid clash with accessor)
public:
//==================================公有函数==================================

    //数据接口
    const T item() const{
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
    const SLNode<T>* next() const{
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
//==================================SLinkedList==================================

//链表类SLinkedList
template <typename T>
class SLinkedList : public IList<T> {
private:
    SLNode<T>* _head;                //头节点(无效数据)
    unsigned int _count;            //表长度
public:
    // Make the templated operator<< a friend without introducing a new template parameter named T
	template <typename T>
    friend std::ostream& operator<< (std::ostream& os, const SLinkedList<T>& rhs);
//================================== STL 前向迭代器==================================

    class iterator {//SLinkedList iterator
    private:
        SLNode<T>* curr;
        friend class SLinkedList<T>;

        template<std::input_iterator Itr,typename TII>
        friend void ::dispose(Itr,TII);
    public:
        //类型标签
        using value_type = T;                            //元素类型
        using pointer = T*;                                //元素指针
        using reference = T&;                            //元素引用
        using difference_type = ptrdiff_t;                //差值类型
        using iterator_category = std::forward_iterator_tag;    //随机访问

        iterator(SLNode<T>* p=nullptr):curr(p){}

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
        friend class SLinkedList<T>;
    public:
        using value_type =const T;                            //元素类型
        using pointer =const T*;                                //元素指针
        using reference =const T&;                            //元素引用
        using difference_type = ptrdiff_t;                //差值类型
        using iterator_category = std::forward_iterator_tag;    //随机访问
        
        const_iterator(SLNode<T>* p=nullptr):curr(p){}
        const_iterator(const iterator& other):curr(other.curr){}

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

        bool operator==(const const_iterator& other) const{
            return curr == other.curr;
        }

        bool operator!=(const const_iterator& other) const{
            return curr != other.curr;
        }
    };
//==================================公有函数==================================

    //接口
    const SLNode<T>* head() const{
        return _head;
    }
    SLNode<T>*& head() {
        return _head;
    }
    //change _head
    void change_head(SLNode<T>* newHead) {
        _head = newHead;
    }

    unsigned int size() const override{
        return _count;
    }
    const unsigned int count() const{
        return _count;
    }
    //缺省构造
    SLinkedList() : _count(0) {
        _head = new SLNode<T>();
    }

    //以容器构造
    template <std::input_iterator Itr>
    SLinkedList(Itr first, Itr end) :SLinkedList(){
        for (Itr i = first; i != end;++i) {
            push_back(*i);
        }
    }

    //委托构造
    SLinkedList(std::initializer_list<T> init) :SLinkedList(init.begin(), init.end()) {}

    //以数组构造
    SLinkedList(const T* first, int cnt) {
        _count = cnt > 0 ? cnt : 1;
        _head = new SLNode<T>();
        for (int i = 0; i < cnt; i++) {
            push_back(first[i]);
        }
    }

    //拷贝构造
    SLinkedList(const SLinkedList& other) {
        
        _head = new SLNode<T>();
        _count = other._count;
        _head->next() = makeLink(other);
    }

    //移动构造
    SLinkedList(SLinkedList&& other) noexcept {
        _head = other._head;
        _count = other._count;
        other._head = new SLNode<T>();
        other._count = 0;
    }

    //重载赋值
    const SLinkedList<T>& operator=(const SLinkedList& other) {
        if(this!=&other){
            ::dispose(begin());
            _count = other._count;
            _head->next() = makeLink(other);
        }
        return *this;
    }


    ~SLinkedList() {
        ::dispose(begin(),_head);
    }

    // ==============================
    // 迭代器入口
    // ==============================
    
    iterator begin() {
        return iterator(_head->next());
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator begin() const {
        return const_iterator(_head->next());
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    const_iterator cbegin() const {
        return const_iterator(_head->next());
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }

    // ==============================
    // 基础功能
    // ==============================

    bool empty() const override{
        return (_count == 0)&&(_head->next() == nullptr);
    }

    void push_back(const T& val) override {//尾部插入
        SLNode<T>* pnewNode = new SLNode<T>(val);
        SLNode<T>* p = _head;
        while (p->next()!= nullptr) {
            p = p->next();
        }
        p->next() = pnewNode;
        ++_count;
    }

    void push_front(const T& val) override {//头部插入
        SLNode<T>* pnewNode = new SLNode<T>(val);
        pnewNode->changeNext(_head->next());
        _head->changeNext(pnewNode);
        ++_count;
    }

    T& operator[](unsigned int index) override {
        if (index < 0 || index >= _count) {
            throw std::out_of_range("越界访问");
        }

        iterator it = begin();

        for (int i = 0;i < index;++i) {
            ++it;
        }

        return *it;
    }
    const T& operator[](unsigned int index) const override {
        if (index < 0 || index >= _count) {
            throw std::out_of_range("越界访问");
        }

        const_iterator it = begin();

        for (int i = 0;i < index;++i) {
            ++it;
        }

        return *it;
    }

    SLNode<T>*& findNode(int a) {//查找第i个节点(i>=0)
        if (a < 0 || a > _count) {
            throw std::out_of_range("查找越界");
        }
        SLNode<T>* p = _head;
        for (int i = 0;i < a;++i) {
            p = p->next();
        }
        return p->next();
    }
    const SLNode<T>* findNode(int a) const {//查找第i个节点(i>=0)
        if (a < 0 || a > _count) {
            throw std::out_of_range("查找越界");
        }
        SLNode<T>* p = _head;
        for (int i = 0;i < a;++i) {
            p = p->next();
        }
        return p->next();
    }

    void show() {
        SLNode<T>* p = _head->next();
        if (p == nullptr) {
            std::cout << "null";
        }
        while (p != nullptr) {
            std::cout << p->item()<<' ';
            p = p->next();
        }
    }

    std::string str(bool needTypeName = false) const {//返回字符串
        std::ostringstream oss;
        if (needTypeName)
            oss << "SLinkedList:";
        SLNode<T>* q = _head->next();
        while (q != nullptr) {
            oss << q->item() << ' ';
            q = q->next();
        }
        return oss.str();
    }

    void insert(int i, const T& k) override{//第i个位置插入元素(第i个变成新元素)
        if (i < 0 || i > _count) {
            throw std::out_of_range("插入越界");
        }
        if (i == 0) {
            push_front(k);
        }
        else if (i == _count ) {
            push_back(k);
        }
        else {
            SLNode<T>* p = new SLNode<T>(k);
            SLNode<T>*& q = findNode(i - 1);
            p->changeNext(q->next());
            q->changeNext(p);
            ++_count;
        }
    }

    bool removeAnItem(int index) {//remove the node with input index
        if (index < 0 || index >= _count) {
            throw std::out_of_range("删除越界");
        }
        SLNode<T>* p;
        if (index == 0) {
            p = _head;
        }
        else if (index == _count-1) {
            pop_back();
            return true;
        }
        else {
            p = findNode(index - 1);
        }
        SLNode<T>* q = p->next();
        p->changeNext(q->next());
        delete q;
        --_count;
        return true;
    }

    bool removeTheFirstItem(const T& k) {//删除表中第一个值为k的节点
        SLNode<T>* p = _head->next();
        int i = 0;
        for (;p != nullptr;++i) {
            if (p->item() == k)
                break;
            p = p->next();
        }
        if (p == nullptr) {
            return false;
        }
        removeAnItem(i);
        return true;
    }

    bool removeAllItems(const T& k) {//删除表中所有值为k的节点
        bool removed = false;
        SLNode<T>* p = _head;
        SLNode<T>* q = p->next();
        while (q != nullptr) {
            if (q->item() == k) {
                p->changeNext(q->next());
                delete q;
                q = p->next();
                --_count;
                removed = true;
            }
            else {
                p = p->next();
                q = p->next();
            }
        }
        return removed;
    }

    const bool contains(const T& k) const {//表中是否包含值为k的节点
        SLNode<T>* p = _head->next();
        while (p != nullptr) {
            if (p->item() == k) {
                return true;
            }
            p = p->next();
        }
        return false;
    }

    void subSLinkedList(int i, int j) {//截取第i到j-1个节点组成新的链表
        if (i < 0 || j > _count || i >= j) {
            throw std::out_of_range("截取越界");
        }
        SLinkedList<T> newList;
        for (int k = i;k < j;++k) {
            newList.push_back((*this)[k]);
        }
        std::cout << newList;
    }

    void addList(const SLinkedList<T>& other) {//将other链表添加到当前链表末尾
        SLNode<T>* p = _head;
        while (p->next() != nullptr) {
            p = p->next();
        }
        p->changeNext(makeLink(other));
        _count += other._count;
    }

    void pop_back() override {//尾部删除
        if (empty()) {
            throw std::out_of_range("空表无法删除");
        }
        SLNode<T>* p = _head;
        SLNode<T>* q = p->next();
        while (q->next() != nullptr) {
            p = p->next();
            q = q->next();
        }
        delete p->next();
        p->changeNext(nullptr);
        --_count;
    }

    void pop_front() override { 
        removeAnItem(0); 
    }

    bool removeAt(unsigned int index) override {
        if (index >= size()) return false;
        return removeAnItem(index);
    }

    void print(std::ostream& os = std::cout) const override {
        os << *this;
    }

};

template <typename T>
std::ostream& operator<< (std::ostream& os, const SLinkedList<T>& rhs) {
    os << "SLinkedList:";
    if (!rhs.empty()) {
        typename SLinkedList<T>::const_iterator it = rhs.begin();
        while (it != rhs.end()) {
            os << *it << ' ';
            ++it;
        }
    }
    else {
        os << "null";
    }
    return os;
}

template <typename T>
SLNode<T>* makeLink(const SLinkedList<T>& other) {
    if (other.empty())
        return nullptr;
    SLNode<T>* p = other.head()->next();
    SLNode<T>* front = new SLNode<T>(p->item());
    SLNode<T>* q = front;
    p = p->next();
    while (p != nullptr) {
        q->next() = new SLNode<T>(p->item());
        q = q->next();
        p = p->next();
    }
    return front;
}
