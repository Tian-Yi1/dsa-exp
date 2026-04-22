#include <iostream>
using namespace std;
void swapint(int& x, int& y);
void swapdouble(double& x, double& y);
template<typename T>
void myswap(T& x, T& y);
int main() {
	int a = 3, b = 7;
	cout << "a=" << a << "\tb=" << b << endl;
	swapint(a, b);
	cout << "after swap" << endl;
	cout << "a=" << a << "\tb=" << b << endl;
	double ad = 3.5, bd = 7.5;
	cout << "ad=" << ad << "\tbd=" << bd << endl;
	swapdouble(ad, bd);
	cout << "after swap" << endl;
	cout << "ad=" << ad << "\tbd=" << bd << endl;
	cout << "a=" << a << "\tb=" << b << endl;
	myswap(a, b);
	cout << "after swap" << endl;
	cout << "a=" << a << "\tb=" << b << endl;
	cout << "ad=" << ad << "\tbd=" << bd << endl;
	myswap(ad, bd);
	cout << "after swap" << endl;
	cout << "ad=" << ad << "\tbd=" << bd << endl;
	return 0;
}
void swapint(int& x, int& y) {
	int t;
	t = x; x = y; y = t;
}
void swapdouble(double& x, double& y) {
	double t;
	t = x; x = y; y = t;
}
template<typename T>
void myswap(T& x, T& y) {
	T t;
	t = x; x = y; y = t;
}