#pragma once
#include <iostream>
#include <string>
using namespace std;
//Robot成员:_ID,_name,_IQ
class Robot {
private:
	int _ID=0;
	string _name;
	double _IQ=0.0;
public:
	//============================================构造和析构============================================

	//无参数构造
	Robot();
	//有参数赋值(C++)
	Robot(int _ID, string _name, double _IQ);
	//有参数赋值(C)
	Robot(int _ID, const char* _name, double _IQ);
	//拷贝构造函数
	Robot(const Robot& other);
	//移动构造函数
	Robot(Robot&& rhs) noexcept;
	//拷贝赋值
	Robot& operator=(const Robot& other);
	//移动赋值
	Robot& operator=(Robot&& other) noexcept;
	//析构函数
	~Robot();

	//============================================获取私有成员============================================

	//getID
	int getID()const;
	//getName
	string getName();
	//getIQ
	double getIQ()const;

	//============================================修改成员接口============================================

	//ID成员接口
	void setID(int newID);
	//name成员接口
	void setName(string newName);
	//IQ成员接口
	void setIQ(double newIQ);

	//============================================print成员信息============================================

	//直接打印
	void getRobot()const;
	//拼接字符串
	string str()const;

	//============================================重载运算符============================================

	//<比较机器人智商
	bool operator<(const Robot& other)const;
	bool operator<(double a)const;
	//>比较机器人智商
	bool operator>(const Robot& other)const;
	bool operator>(double a)const;
	//==比较机器人智商
	bool operator==(const Robot& other)const;
	bool operator==(double a)const;
	//重载<<
	friend ostream& operator<<(ostream& os, const Robot& other);
};
// ============================================比较函数============================================

	// 按 ID 升序
bool cmpByID(const Robot& a, const Robot& b);

	// 按智商降序
bool cmpByIQ(const Robot& a, const Robot& b);