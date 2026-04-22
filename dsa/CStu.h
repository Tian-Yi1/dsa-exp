#pragma once
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
//CStu成员:_id,_name,_age,_score
class CStu {
private:
	int _id;
	string _name;
	float _age;
	double _score;
public:
	//C++
	CStu(int _id, string _name, float _age, double _score) :_name(move(_name)) {
		this->_id = _id;
		this->_age = _age;
		this->_score = _score;
	}
	//C
	CStu(int _id, const char* _name, float _age, double _score) :_name(move(_name)) {
		this->_id = _id;
		this->_age = _age;
		this->_score = _score;
	}
	CStu() :_name("unknown") {
		_id = 0;
		_age = 0.0;
		_score = -1.0;
	}
	//拷贝构造(必写)
	CStu(const CStu& other) : _id(other._id),_name(other._name),_age(other._age),_score(other._score) {

	}
	//移动构造
	CStu(CStu&& rhs) noexcept :_name(move(rhs._name)) {
		_id = rhs._id;
		_age = rhs._age;
		_score = rhs._score;
	}
	//返回this引用，应用CStu&
	CStu& operator=(CStu&& rhs) noexcept {
		if (this != &rhs) {
			_id = rhs._id;
			_age = rhs._age;
			_score = rhs._score;
			_name = move(rhs._name);
		}
		return *this;
	}
	//定义比较逻辑,便于排序sort,按成绩排序,成员函数中只接收外部变量this省略
	bool operator<(const CStu& stu1) {
		return this->_score < stu1._score;
	}
	//开放私有成员变量接口，方便查看，调用和修改
	//返回常量，只能被常量调用
	int id() const {
		return _id;
	}
	//返回引用，可作为左值修改
	int& id() {
		return _id;
	}
	string name() const {
		return _name;
	}
	//可以写stu1.name()="newName"修改成员
	string& name() {
		return _name;
	}
	float age() const {
		return _age;
	}
	float& age() {
		return _age;
	}
	double score() const {
		return _score;
	}
	double& score() {
		return _score;
	}
	//提供一种简便修改接口
	void setName(const string& newName) {
		this->_name = newName;
	}
	void setId(const int& newId) {
		_id = newId;
	}
	void setAge(const float& newAge) {
		_age = newAge;
	}
	void setScore(const double& newScore) {
		_score = newScore;
	}
	//拼接并输出单个类信息，利用输出流存储，输出到控制台（cout）
	void get() const {
		ostringstream oss;
		oss << "学生姓名:" << _name << "    年龄:" << _age << "    学号：" << _id << "    成绩：" << _score;
		cout << oss.str();
	}
	//返回流,cout<<str();
	string str() const {
		ostringstream oss;
		oss << _id << '-' << _name << '-' << _age << '-' << _score;
		return oss.str();
	}
	~CStu() {

	}
	//声明<<友元，实现在.cpp中
	friend ostream& operator<<(ostream& os, const CStu& stu1);
};
