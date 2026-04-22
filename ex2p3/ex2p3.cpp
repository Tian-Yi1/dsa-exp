#include "../dsa/CStu.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(int agrc, char* argv[]) {
	//建立构造模板数组
	CStu s[] = { {1300,"张三",18.5F,91.19},{1301,"李四",18.6F,90.91},{1302,"王五",19.91F,87.78} };
	//建立CStu线性表
	vector<CStu> myStuList(s, s + 3);
	sort(myStuList.begin(), myStuList.end());
	//迭代器循环
	vector<CStu>::iterator it = myStuList.begin();
	cout << "排序后:";
	for (;it!= myStuList.begin() + myStuList.size();++it) {
		cout << *it << endl;
	}
	myStuList.insert(myStuList.begin()+1, { 1305,"王亮",21.0F,60 });
	myStuList.push_back({ 1306,"王不亮",22.0F,61 });
	//auto
	for (auto& a : myStuList) {
		cout << a.name() << ' ' << a.score() << endl;
	}
	sort(myStuList.begin(), myStuList.end());
	for (auto& stu : myStuList) {
		stu.get();
		cout << endl;
	}
	return 0;
}