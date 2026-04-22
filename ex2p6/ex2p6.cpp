#include <iostream>
#include "../dsa/CStu.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
	int a[5] = { 1,2,3,4,5 };
	CStu s[5] = { {3016, "张超", 17.1F, 89}, { 3053, "马飞", 19.4F, 80 }, { 3041, "刘羽",
	21.0F, 96 }, { 3025, "赵备", 18.5, 79 }, { 3039, "关云", 20, 85 } };
	for (const auto& it : s) {
		it.get();
		cout << endl << it.str() << endl;
	}
	return 0;
}