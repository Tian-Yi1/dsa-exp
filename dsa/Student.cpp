#include <string>
#include <sstream>
#include "Student.h"
ostream& operator<<(ostream& os, const Student& s) {
	os << s.name << '(' << s.id << ')';
	return os;
}
string Student::str() const {
	ostringstream ss;
	ss << id << '-' << name << '-' << age << '-' << score;
	return ss.str();
}
Student::~Student() {

}