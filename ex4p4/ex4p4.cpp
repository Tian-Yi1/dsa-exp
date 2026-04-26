#include <iostream>
#include "../dsa/SingleLinkedList.h"
#include <string>
#include <list>
#include "../dsa/CStu.h"

int main() {
    std::cout << "========== 使用自定义 SLinkedList<CStu> ==========\n";
    SLinkedList<CStu> myList;

    // 1. push_back 添加元素
    myList.push_back(CStu(101, "张三", 20.5f, 88.0));
    myList.push_back(CStu(102, "李四", 21.0f, 92.5));
    myList.push_back(CStu(103, "王五", 19.8f, 76.0));
    std::cout << "初始链表: " << myList << "\n";
    std::cout << "size = " << myList.size() << "\n";

    // 2. insert 在第1个位置插入
    myList.insert(1, CStu(104, "赵六", 22.0f, 95.0));
    std::cout << "在位置1插入后: " << myList << "\n";

    // 3. 使用迭代器遍历
    std::cout << "迭代器输出: ";
    for (auto it = myList.begin(); it != myList.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    // 4. 下标访问
    std::cout << "第一个元素: " << myList[0] << "\n";
    std::cout << "第二个元素: " << myList[1] << "\n";

    // 5. pop_back
    myList.pop_back();
    std::cout << "pop_back 后: " << myList << "\n";

    std::cout << "\n========== 对比标准库 std::list<CStu> ==========\n";
    std::list<CStu> stdList;
    stdList.push_back(CStu(101, "张三", 20.5f, 88.0));
    stdList.push_back(CStu(102, "李四", 21.0f, 92.5));
    stdList.push_back(CStu(103, "王五", 19.8f, 76.0));

    auto pos = stdList.begin();
    std::advance(pos, 1);   // 指向第1个位置
    stdList.insert(pos, CStu(104, "赵六", 22.0f, 95.0));
    stdList.pop_back();

    std::cout << "std::list 内容: ";
    for (const auto& s : stdList) std::cout << s << " ";
    std::cout << "\n";
    std::cout << "\n===== 基本性质对比 =====\n";
    std::cout << "特性                | SLinkedList<CStu>   | std::list<CStu>\n";
    std::cout << "--------------------|--------------------|--------------------\n";
    std::cout << "迭代器类型          | 前向迭代器         | 双向迭代器\n";
    std::cout << "push_back 复杂度    | O(n)               | O(1)\n";
    std::cout << "insert 复杂度       | O(n)               | O(1)（给定位置）\n";
    std::cout << "支持 operator[]     | 是（O(n)）         | 否\n";
    std::cout << "支持反向遍历        | 否                 | 是（rbegin/rend）\n";
    std::cout << "size() 复杂度       | O(1)               | O(1) (C++11起)\n";
    return 0;
}