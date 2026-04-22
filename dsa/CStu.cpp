#include "CStu.h"
ostream& operator<<(ostream& os, const CStu& stu1) {
	os << stu1._name << '(' << stu1._id << ')';
	return os;
}