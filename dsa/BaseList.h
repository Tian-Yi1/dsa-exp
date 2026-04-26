#pragma once
#include <iostream>

template <typename T>
class IList {
public:
    virtual ~IList() = default;
    virtual bool empty() const = 0;
    virtual unsigned int size() const = 0;
    virtual void push_front(const T& val) = 0;
    virtual void push_back(const T& val) = 0;
    virtual void insert(int index, const T& val) = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual bool removeAt(unsigned int index) = 0;
    virtual T& operator[](unsigned int index) = 0;
    virtual const T& operator[](unsigned int index) const = 0;
    virtual void print(std::ostream& os = std::cout) const = 0;
};