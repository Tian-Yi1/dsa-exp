#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include "globalFunc.h"
using namespace std;
//==================================SLNode==================================

//单个数据类SLNode
template <typename T>
class SLNode {
private:
	T item;							//数据域
	SLNode<T>* next;				//指针域
public:
//==================================公有函数==================================

	//数据接口
	const SLNode<T> item() {
		return item;
	}
	//修改item
	void changeItem(T newItem) {
		item = newItem;
	}
	SLNode<T>& item() {
		return item;
	}
	//指针接口
	const SLNode<T>* next() {
		return next;
	}
	SLNode<T>*& next() {
		return next;
	}
	//修改指针
	void changeNext(SLNode<T>* newNext) {
		next = newNext;
	}
	//缺省构造
	SLNode() :next(nullptr), item{} {
		
	}
	//带参构造
	SLNode(const T& k) :item(k), next(nullptr) {

	}
	//拷贝构造
	//SLNode(const SLNode<T>& other) :item(other.item), next(other.next) {}
	//析构函数
	~SLNode() {
		next = nullptr;
	}
};
//==================================SLinkedList==================================

//链表类SLinkedList
template <typename T>
class SLinkedList {
private:
	SLNode<T>* _head;				//头节点(无效数据)
	unsigned int _count;			//表长度
public:
	template <typename T>
	friend ostream& operator<<(ostream& os, const SLinkedList<T>& rhs);
//================================== STL 前向迭代器==================================

	class iterator {//SLinkedList iterator
	private:
		SLNode<T>* curr;
		friend class SLinkedList<T>;

		template<input_iterator Itr,typename TII>
		friend void ::dispose(Itr,TII);
	public:
		//类型标签
		using value_type = T;							//元素类型
		using pointer = T*;								//元素指针
		using reference = T&;							//元素引用
		using difference_type = ptrdiff_t;				//差值类型
		using iterator_category = forward_iterator_tag;	//随机访问

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
		using value_type =const T;							//元素类型
		using pointer =const T*;								//元素指针
		using reference =const T&;							//元素引用
		using difference_type = ptrdiff_t;				//差值类型
		using iterator_category = forward_iterator_tag;	//随机访问
		
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

	const unsigned int size() const{
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
	template <input_iterator Itr>
	SLinkedList(Itr first, Itr end) :SLinkedList(){
		for (Itr i = first; i != end;++i) {
			push_back(*i);
		}
	}

	//委托构造
	SLinkedList(initializer_list<T> init) :SLinkedList(init.begin(), init.end()) {}

	//以数组构造
	SLinkedList(const T* first, int cnt) {
		_count = cnt > 0 ? cnt : 1;
		_head = new SLNode<T>();
		SLNode<T>* rear=_head;
		SLNode<T>* q;
		for (int i = 0, i < cnt, i++) {
			q = new SLNode<T>(first[i]);
			rear->next() = q;
			rear = q;
		}
	}

	//拷贝构造
	SLinkedList(const SLinkedList& other) {
		
		_head = new SLNode<T>();
		_count = other._count;
		_head->next() = makeLink(other);
	}

	//重载赋值
	const SLinkedList<T>& operator=(const SLinkedList& other) {
		if(this!=&other){
			::dispose(_head->next());
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

	bool empty() const {
		return (_count == 0)&&(_head->next() == nullptr);
	}

	void push_back(const T& val) {
		SLNode<T>* pnewNode = new SLNode<T>(val);
		SLNode<T>* p = _head;
		while (p->next()!= nullptr) {
			p = p->next();
		}
		p->next = pnewNode;
		++_count;
	}

	void push_front(const T& val) {
		SLNode<T>* pnewNode = new SLNode<T>(val);
		pnewNode->changeNext(_head->next());
		_head->changeNext(pnewNode);
		++_count;
	}

	T& operator[](unsigned int index) {
		if (index < 0 || index >= _count) {
			throw out_of_range("越界访问");
		}

		iterator it = begin();

		for (int i = 0;i < index;++i) {
			++it;
		}

		return *it;
	}
	const T& operator[](unsigned int index) const{
		if (index < 0 || index >= _count) {
			throw out_of_range("越界访问");
		}

		iterator it = begin();

		for (int i = 0;i < index;++i) {
			++it;
		}

		return *it;
	}

	void show() {
		SLNode<T>* p = _head->next();
		if (p == nullptr) {
			cout << "null";
		}
		while (p != nullptr) {
			cout << p->item()<<' ';
			p = p->next();
		}
	}

};

template <typename T>
ostream& operator<< (ostream& os, const SLinkedList<T>& rhs) {
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
