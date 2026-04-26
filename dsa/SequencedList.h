#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
//默认表容量
const int LCapacity = 16;
using namespace std;

template <typename T>
//泛型类
class SequencedList {
private:
	//===================私有成员变量===================

	//typename T 作为存储数据数组的元素类型
	T* name;
	//当前表中元素个数
	int size;
	//表容量
	int capacity;

	//===================私有函数===================

	//扩容函数
	void expand(int newCapacity){
		if (newCapacity <= capacity) {
			return;
		}
		T* newData = new T[newCapacity];
		for (int i = 0;i < size;i++) {
			newData[i] = name[i];
		}
		delete[] name;
		name = newData;
		capacity = newCapacity;
	}
	//缩容函数
	void shrink() {
		if (size <= capacity / 4 && capacity > LCapacity) {
			int newCap = max(size, LCapacity);
			T* newData = new T[newCap];
			for (int i = 0; i < size; i++) {
				newData[i] = name[i];
			}
			delete[] name;
			name = newData;
			capacity = newCap;
		}
	}
public:
	//===================构造函数===================

	//空构造
	SequencedList() {
		name = new T[LCapacity];
		capacity = LCapacity;
		size = 0;
	}
	//指定初始容量的构造函数
	explicit SequencedList(int cnt) {
		if (cnt <= 0) {
			throw invalid_argument("容量须大于0");
		}
		name = new T[cnt];
		capacity = cnt;
		size = 0;
	}
	//从数组构造
	template <typename ITR>
	SequencedList(const ITR first, int cnt) {
		if (cnt <= 0) {
			throw invalid_argument("容量须大于0");
		}
		ITR it = (ITR)first;
		size = cnt;
		capacity = cnt > LCapacity ? cnt : LCapacity;
		name = new T[capacity];
		for (int i = 0;i < size;i++) {
			name[i] = *it++;
		}
	}
	//从容器构造
	template <typename ITR>
	SequencedList(const ITR begin, const ITR end) {
		size = (int)(end - begin);
		capacity = max(size, LCapacity);
		ITR it = (ITR)begin;
		name = new T[capacity];
		for (int i = 0;i < size;i++) {
			name[i] = *it++;
		}
	}
	//拷贝构造函数
	SequencedList(const SequencedList<T>& other) {
		name = new T[other.capacity];
		size = other.size;
		capacity = other.capacity;
		for (int i = 0;i < size;i++) {
			name[i] = other.name[i];
		}
	}
	//移动构造函数
	SequencedList(SequencedList<T>&& rhs) :name(rhs.name),capacity(rhs.capacity),size(rhs.size){
		rhs.name = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;
	}
	//赋值运算
	SequencedList<T>& operator=(const SequencedList<T>& other) {
		if (this != &other) {
			delete[] name;
			name = new T[other.capacity];
			size = other.size;
			capacity = other.capacity;
			for (int i = 0;i < size;i++) {
				name[i] = other.name[i];
			}
		}
		return *this;
	}

	//===================析构函数===================

	//析构函数
	~SequencedList() {
		delete[] name;
	}

	//===================基本操作===================

	//尾部添加元素
	void push_back(const T& element) {
		if (size == capacity) {
			expand(capacity + 1);
		}
		name[size] = element;
		size++;
	}
	//指定位置插入元素
	void insert(int index, const T& element) {
		if (index < 0 || index > size) {
			throw std::out_of_range("插入位置越界");
		}
		if (size == capacity) {
			expand(capacity + 1);
		}
		for (int i = size;i > index;i--) {
			name[i] = name[i - 1];
		}
		name[index] = element;
		size++;
	}
	//删除指定位置元素
	T remove(int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("插入位置越界");
		}
		T removedElement = name[index];
		for (int i = index;i < size-1;i++) {
			name[i] = name[i + 1];
		}
		size--;
		shrink();
		return removedElement;
	}
	//删除第一个指定元素
	bool removeElement(const T& element) {
		int i = 0;
		for (;i < size;i++) {
			if (name[i] == element)
				break;
		}
		if (i == size) {
			return false;
		}
		else {
			remove(i);
			return true;
		}
	}
	//清空顺序表
	void clear() {
		delete[] name;
		name = new T[LCapacity];
		capacity = LCapacity;
		size = 0;
	}
	//获取指定位置元素
	T get(int index) const {
		if (index < 0 || index >= size) {
			throw std::out_of_range("访问位置越界");
		}
		return name[index];
	}
	//修改指定位置元素
	void set(int index, const T& element) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("修改位置越界");
		}
		name[index] = element;
	}
	//查找元素，返回索引，-1表示不存在
	int find(const T& element) const {
		for (int i = 0;i < size;i++) {
			if (name[i] == element)
				return i;
		}
		return -1;
	}
	//判断是否包含元素
	bool contains(const T& element) const {
		return find(element)!=-1;
	}
	//获取当前元素个数
	int getSize() const {
		return size;
	}
	//获取当前容量
	int getCapacity() const {
		return capacity;
	}
	//判断是否为空
	bool isEmpty() const {
		return size == 0;
	}
	//预留容量
	bool reserve(int newCapacity) {
		if (newCapacity > capacity) {
			expand(newCapacity);
			return true;
		}
		return false;
	}
	//将容量调整为当前大小
	void trimToSize() {
		shrink();
	}

	//===================运算符重载===================

	//下标访问(可修改)
	T& operator[](int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("下标越界");
		}
		return *(name + index);
	}
	//下标访问(不可修改)
	const T& operator[](int index) const{
		if (index < 0 || index >= size) {
			throw std::out_of_range("下标越界");
		}
		return name[index];
	}
	//相等逻辑
	bool operator==(const SequencedList<T>& other) const {
		if (size != other.size)
			return false;
		if (capacity != other.capacity)
			return false;
		for (int i = 0;i < size;i++) {
			if (name[i] != other.name[i])
				return false;
		}
		return true;
	}
	//不相等逻辑
	bool operator!=(const SequencedList<T>& other) const {
		return !(*this == other);
	}
	//小于逻辑
	bool operator<(const SequencedList<T>& other) const {
		return size < other.size;
	}
	//大于逻辑
	bool operator>(const SequencedList<T>& other) const {
		return size > other.size;
	}
	//友元函数：输出运算符重载
	template <typename U>
	friend ostream& operator<<(ostream& os, const SequencedList<U>& list);

	//===================高级功能===================

	//反转顺序表
	void reverse() {
		T temp = 0;
		for (int i = 0;i < size/2;i++) {
			temp = name[i];
			name[i] = name[size - 1 - i];
			name[size - 1 - i] = temp;
		}
	}
	//排序(升序)
	void sort() {
		std::sort(name, name + size);
	}
	//去重(需先排序)
	void unique() {
		if (size <= 1) return;
		int j = 0;
		for (int i = 1;i < size;i++) {
			if (name[i] != name[j]) {
				name[++j] = name[i];
			}
		}
		size = j + 1;
		shrink();
	}
	//截取子表
	SequencedList<T> subList(int fromIndex, int toIndex) const {
		if (fromIndex < 0 || toIndex > size || fromIndex > toIndex) {
			throw std::out_of_range("子表索引越界");
		}
		SequencedList<T> subList(toIndex - fromIndex);
		for (int i = fromIndex;i < toIndex;i++) {
			subList.push_back(name[i]);
		}
		return subList;
	}

	//===================迭代器支持===================

	//begin iterator
	T* begin() {
		return name;
	}
	//const begin iterator
	const T* begin() const {
		return name;
	}
	//end iterator
	T* end() {
		return name + size;
	}
	//const end iterator
	const T* end() const{
		return name + size;
	}
};
template <typename U>
std::ostream& operator<<(std::ostream& os, const SequencedList<U>& list) {
	os << '[';
	for (int i = 0;i < list.getSize();i++) {
		os << list.get(i);
		if (i != list.getSize() - 1)
			os << ',';
	}
	os << ']';
	return os;
}