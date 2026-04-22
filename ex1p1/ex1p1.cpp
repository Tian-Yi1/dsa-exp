#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
	int sum;
	if (argc == 3) {
		sum = stoi(argv[1]) + stoi(argv[2]);
		cout << argv[1] << "+" << argv[2] << "=" << sum << endl;
	}
	else {
		cout << "" << endl;
		return -1;
	}
	vector<string> v1{ "Hello","C++","World","!" };
	for (const auto& x : v1) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}