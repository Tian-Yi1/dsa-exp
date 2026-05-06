/*@brief 提供"CompareKey"枚举类,根据参数k的值定义数据元素的比较规则
 *@date 2026-05-06
 */
#pragma once
#include <functional>
#include "CStu.h"
namespace StudentUtils {
	/**
	*@brief 定义枚举类CompareKey
	*@details 包含ID、Name、Age、Score、IDD、NameD、AgeD、ScoreD等成员，分别表示按照学号、姓名、年龄、成绩升序和降序排序的比较规则
	*/
	enum class CompareKey {
	ID,Name,Age,Score,IDD,NameD,AgeD,ScoreD
	};
	/**
	*@brief 比较函数
	*@param ID 学生的学号
	*@param Name 学生的姓名
	*@param Age 学生的年龄
	*@param Score 学生的成绩
	*@param IDD 学生的学号降序
	*@param NameD 学生的姓名降序
	*@param AgeD 学生的年龄降序
	*@param ScoreD 学生的成绩降序
	*@return 返回一个std::function对象，表示根据参数k的值定义的数据元素的比较规则
	*@warning 该函数返回的比较规则仅适用于CStu类型的对象，且需要保证CStu类中已经定义了相应的成员函数（如id()、name()、age()、score()等）以供比较使用
	*/
	std::function<bool(const CStu&, const CStu&)> ComparisonBy(CompareKey k = CompareKey::ID) {
		std::function<bool(const CStu&, const CStu&)> cmp;
		switch (k) {
			case CompareKey::ID:
				cmp = [](const CStu& a, const CStu& b) { return a.id() < b.id(); };
				break;
			case CompareKey::Name:
				cmp = [](const CStu& a, const CStu& b) { return a.name() < b.name(); };
				break;
			case CompareKey::Age:
				cmp = [](const CStu& a, const CStu& b) { return a.age() < b.age(); };
				break;
			case CompareKey::Score:
				cmp = [](const CStu& a, const CStu& b) { return a.score() < b.score(); };
				break;
			case CompareKey::IDD:
				cmp = [](const CStu& a, const CStu& b) { return a.id() > b.id(); };
				break;
			case CompareKey::NameD:
				cmp = [](const CStu& a, const CStu& b) { return a.name() > b.name(); };
				break;
			case CompareKey::AgeD:
				cmp = [](const CStu& a, const CStu& b) { return a.age() > b.age(); };
				break;
			case CompareKey::ScoreD:
				cmp = [](const CStu& a, const CStu& b) { return a.score() > b.score(); };
				break;
		}
		return cmp;
	};
}