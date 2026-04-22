#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include "../dsa/dsaUtils.h"
using namespace std;
int main(int argc, char* argv[]) {
	const int a = 20;
	int s[a];
	int i = 1;
	if (argc > 1)
		i = stoi(argv[1]);
	RandomData(s, a, i);
	Show(s, s + a);
	cout << "排序后:";
	sort(s, s + a);
	Show(s, s + a);
	cout << endl << "按绝对值排序后:";
	sort(s, s + a, [](int x, int y) {return abs(x) < abs(y); });
	Show(s, s + a);
	return 0;
}