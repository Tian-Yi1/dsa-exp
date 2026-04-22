#include "../dsa/dsaUtils.h"
#include <iostream>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
	const int cnt = 20;
	int a[cnt];
	int random = 1;
	if (argc > 1)
		random = argc;
	//随机初始化数组
	RandomData(a, cnt, random);
	//显示数组
	cout << "初始数组:";
	Show(a, a + cnt);
	//重新随机化数组
	RandomData(a, cnt, random + 1);
	//显示数组
	cout << "another:";
	Show(a, a + cnt);
	//利用lambda表达式限制比较谓词对数组进行排序
	sort(a, a + cnt, [](int a, int b) {return abs(a) < abs(b);});
	//显示排序结果
	cout << "升序:";
	Show(a, a + cnt);
	//降序
	sort(a, a + cnt, [](int a, int b) {return abs(a) > abs(b);});
	cout << "降序:";
	Show(a, a + cnt);
}