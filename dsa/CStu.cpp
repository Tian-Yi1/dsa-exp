#include "CStu.h"
std::ostream& operator<<(std::ostream& os, const CStu& stu1) {
	os << stu1._name << '(' << stu1._id << ')';
	return os;
}