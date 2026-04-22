#include <vector>
#include <iostream>
using namespace std;
int main(int argc,char* argv[]) {
	vector<int> a;
	a.push_back(3);
	a.push_back(4);
	a.push_back(6);
	a.push_back(1230);
	a.insert(a.begin(), 1);
	a.insert(a.begin() + 1, 2);
	a.insert(a.begin() + 4, 5);
	a.pop_back();
	cout << a.size() << a.capacity();
	for (auto x : a) {
		cout << x;
	}
	a.clear();
	return 0;
}