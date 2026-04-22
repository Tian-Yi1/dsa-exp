#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
using namespace std;
struct Student
{
	int id;string name;float age;double score;


	Student(int id, const string& name, float age, double score) :name(name) {
		this->id = id;
		this->age = age;
		this->score = score;
	}
	Student(int id, const char* name, float age, double score) :name(name) {
		this->id = id;
		this->age = age;
		this->score = score;
	}
	Student() :name("null") {
		id = 0;
		age = 0;
		score = -1;
	}
	Student(const Student& other) :name(other.name) {
		id = other.id;
		age = other.age;
		score = other.score;
	}
	Student& operator=(const Student& rhs) {
		if (this != &rhs) {
			id = rhs.id;
			age = rhs.age;
			score = rhs.score;
			name = rhs.name;
		}
		return *this;
	}
	Student& operator=(Student&& rhs) noexcept {
		if (this != &rhs) {
			id = rhs.id;
			age = rhs.age;
			name = move(rhs.name);
			score = rhs.score;
		}
		return *this;
	}
	Student(Student&& rhs)noexcept :name(move(rhs.name)) {
		id = rhs.id;
		age = rhs.age;
		score = rhs.score;
	}
	bool operator<(const Student& y)const { return id < y.id; }
	string str() const;
	~Student() ;
};
ostream& operator<<(ostream& os, const Student& s);