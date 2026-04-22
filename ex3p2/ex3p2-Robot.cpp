#include "ex3p2-Robot.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
//============================================构造和析构============================================
	//无参数构造
Robot::Robot() :_name("unKnown") {
	_ID = 0;
	_IQ = -1.0;
}
	//有参数赋值(C++)
Robot::Robot(int _ID, string _name, double _IQ) :_name(move(_name)){
	this->_ID = _ID;
	this->_IQ = _IQ;
}
	//有参数赋值(C)
Robot::Robot(int _ID, const char* _name, double _IQ) :_name(move(_name)) {
	this->_ID = _ID;
	this->_IQ = _IQ;
}
	//拷贝构造函数
Robot::Robot(const Robot& other) {
	_ID = other._ID;
	_name = other._name;
	_IQ = other._IQ;
}
	//移动构造函数
Robot::Robot(Robot&& rhs) noexcept  {
	if (this != &rhs) {
		_ID = rhs._ID;
		_name = move(rhs._name);
		_IQ = rhs._IQ;
	}
}
	//拷贝赋值
Robot& Robot::operator=(const Robot& other) {
	if (this != &other) {
		_ID = other._ID;
		_name = other._name;
		_IQ = other._IQ;
	}
	return *this;
}
	//移动赋值
Robot& Robot::operator=(Robot&& rhs) noexcept {
	if (this != &rhs) {
		_ID = rhs._ID;
		_name = move(rhs._name);
		_IQ = rhs._IQ;
	}
	return *this;
}
	//析构函数
Robot::~Robot() {

}
//============================================获取私有成员============================================

	//getID
int Robot::getID() const{
	return _ID;
}
	//getName
string Robot::getName() {
	return _name;
}
	//getIQ
double Robot::getIQ() const{
	return _IQ;
}
//============================================修改成员接口============================================

	//ID成员接口
void Robot::setID(int newID) {
	_ID = newID;
}
	//name成员接口
void Robot::setName(string newName) {
	_name = move(newName);
}
	//IQ成员接口
void Robot::setIQ(double newIQ) {
	_IQ = newIQ;
}

//============================================print成员信息============================================

	//直接打印
void Robot::getRobot()const {
	cout << "机器人编号:" << _ID << ' ' << "机器人名称:" << _name << "机器人智商:" << _IQ<<endl;
}
	//拼接字符串
string Robot::str()const {
	ostringstream oss;
	oss << _ID << '-' << _name << '-' << _IQ;
	return oss.str();
}
//============================================重载运算符============================================

	//<比较机器人智商
bool Robot::operator<(const Robot& other)const {
	return _IQ < other._IQ;
}
bool Robot::operator<(double a)const {
	return _IQ < a;
}
	//>比较机器人智商
bool Robot::operator>(const Robot& other)const {
	return _IQ > other._IQ;
}
bool Robot::operator>(double a)const {
	return _IQ > a;
}
	//==比较机器人智商
bool Robot::operator==(const Robot& other)const {
	return _IQ == other._IQ;
}
bool Robot::operator==(double a)const {
	return _IQ == a;
}
	//重载<<
ostream& operator<<(ostream& os, const Robot& other) {
	os << other._ID << ' ' << other._name << ' ' << other._IQ;
	return os;
}

// ============================================比较函数============================================

	// 按 ID 升序
bool cmpByID(const Robot& a, const Robot& b) {
	return a.getID() < b.getID();
}

	// 按智商降序
bool cmpByIQ(const Robot& a, const Robot& b) {
	return a.getIQ() > b.getIQ();
}