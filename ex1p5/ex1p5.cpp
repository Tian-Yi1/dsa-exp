#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../dsa/Student.h"
using namespace std;
int main(int argc, char* argv[]) {
	vector<int> v;
	v.push_back(3);
	v.insert(v.begin() + 1, 4);
	for (auto a : v) {
		cout << a << ' ';
	}
	sort(v.begin(), v.end());
	cout << endl;
	Student a_2506[] = { {302121001,"张三",18.3f,91},{302121002,"李四",19.1f,89},{302121210,"王五",18.5f,60} };
	vector<Student> stuList1(a_2506, a_2506 + 3);
	vector<Student> stuList2{ {302121001,"张三",18.3f,91},{302121002,"李四",19.1f,89},{302121210,"王五",18.5f,60} };
	auto it = stuList2.begin();
	sort(it, it + 3);
	for (int i = 0;i < 3;i++) {
		cout << stuList2[i].name << '\t' << stuList2[i].id << '\t' << stuList2[i].score <<
			endl;
	}
	for (auto& i : stuList1) {
		cout << i.name << i.age << i.id << i.score << endl;
		cout << i.str()<<endl;
	}
	for (auto& STU : a_2506) {
		cout << STU << endl;
	}
}