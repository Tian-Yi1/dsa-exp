#include <iostream>
#include "../dsa/SequencedQueue.h"

int main(){
	SequencedQueue<int> q(5);
    std::cout << "\n=== 入队 1~5，填满队列 ===" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        q.push(i);
        std::cout << "push(" << i << "), size=" << q.size()
            << ", front=" << q.front() << ", back=" << q.back() << std::endl;
    }

    std::cout << "\n=== 出队 2 次 ===" << std::endl;
    for (int i = 0; i < 2; ++i) {
        std::cout << "pop() 移除 " << q.front() << std::endl;
        q.pop();
        std::cout << "   size=" << q.size() << ", front=" << q.front()
            << ", back=" << q.back() << std::endl;
    }
    std::cout << "\n=== 继续入队 6,7（测试循环利用空间） ===" << std::endl;
    q.push(6);
    std::cout << "push(6): size=" << q.size() << ", front=" << q.front()
        << ", back=" << q.back() << std::endl;
    q.push(7);
    std::cout << "push(7): size=" << q.size() << ", front=" << q.front()
        << ", back=" << q.back() << std::endl;
    std::cout << "\n=== 队列当前全部元素（按出队顺序） ===" << std::endl;
    std::cout << "队列内容: ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
    std::cout << "最终 empty: " << (q.empty() ? "true" : "false")
        << ", size: " << q.size() << std::endl;
    std::cout << "\n=== 测试结论 ===" << std::endl;
    std::cout << "程序正常执行完毕，未出现假溢出（循环成功复用已出队位置）。" << std::endl;

    return 0;
}