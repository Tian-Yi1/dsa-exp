#include <queue>
#include <iostream>
#include <stack>
using namespace std;
int main(int argc, char* argv[]) {
	queue<int> q1;
	for (size_t i = 0;i < 10;i++) {
		q1.push(i * i);
	}
	queue<int> q2(q1);
	while (!q2.empty()) {
		cout << q2.front() << endl;
		q2.pop();
	}
	stack<int> s1;
	size_t cnt = q1.size();
	for (size_t i = 0;i < cnt;i++) {
		s1.push(q1.front());
		q1.pop();
	}
	stack<int> s2(s1);
	while (!s2.empty()) {
		cout << s2.top() << endl;
		s2.pop();
	}
	return 0;
}