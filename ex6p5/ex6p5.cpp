#include "../dsa/LinkedQueue.h"
#include <iostream>

int main() {
    LinkedQueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    std::cout << "front: " << q.front() << ", size: " << q.size() << std::endl; // 10, 3
    q.pop();
    std::cout << "after pop, front: " << q.front() << std::endl; // 20
    while (!q.empty()) q.pop();
    std::cout << "empty: " << q.empty() << std::endl; // 1
    return 0;
}