#include <queue>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <vector>

int main() {
	std::queue<int> q;
	std::stack<int> s;
	std::vector<int> v;
	int val;
	char ch;
	std::cout << "ÊäÈë¶ÓÁÐ ";
	while (std::cin.get(ch)&&ch!='\n') {
		if (std::isdigit(ch) || ch == '-') {
			std::cin.putback(ch);
			if (std::cin >> val) {
				v.push_back(val);
			}
		}
	}
	for (int i = 0;i < v.size();++i) {
		q.push(v[i]);
		s.push(v[i]);
	}
	std::cout << "queue: ";
	for (int i = 0;i < v.size();++i) {
		std::cout << q.front()<<' ';
		q.pop();
	}
	std::cout << std::endl;
	std::cout << "stack: ";
	for (int i = 0;i < v.size();++i) {
		std::cout << s.top() << ' ';
		s.pop();
	}
	v.clear();
	std::cin.clear();
	return 0;
}