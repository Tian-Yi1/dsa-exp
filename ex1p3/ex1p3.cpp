#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include "../dsa/dsaUtils.h"
using namespace std;
int main(int argc, char* argv[]) {
	int* p = new int[30];
	int k = 1;
	if (argc != 1)
		k = stoi(argv[1]);
	RandomData(p, 30, k);
	int a = 50;
	auto ans1 = find(p, p + 30, a);
	if (ans1 != p + 30) {
		cout << "数组中包含元素值" << a << endl;
		cout << "数组第一个大小为50的元素在第" << ans1 - p + 1 << "位" << endl;
	}
	else
		cout << "数组中不包含元素值" << a << endl;
	auto ans2 = find_if(p, p + 30, [](int i) {return i > 40 && i < 90;});
	if (ans2 != p + 30) {
		cout << "数组第一个大于40小于90的元素在第" << ans2 - p + 1 << "位" << endl;
	}
	delete[]p;
	return 0;
}