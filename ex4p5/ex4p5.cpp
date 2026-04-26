#include <iostream>
#include <list>

using namespace std;

// 约瑟夫环求解，返回出列顺序
list<int> josephus(int n, int m) {
    list<int> people;           // 存储所有人的编号（1~n）
    for (int i = 1; i <= n; ++i)
        people.push_back(i);

    list<int> result;           // 记录出列顺序
    auto it = people.begin();   // 当前报数的起始位置

    while (!people.empty()) {
        // 报数 1~m，实际移动 m-1 步到被删除的人
        for (int cnt = 1; cnt < m; ++cnt) {
            ++it;
            if (it == people.end())   // 循环链表效果
                it = people.begin();
        }
        // it 指向要删除的人
        result.push_back(*it);        // 记录编号
        it = people.erase(it);        // 删除并返回下一个迭代器
        if (it == people.end())       // 删除后若到末尾，则绕回头
            it = people.begin();
    }
    return result;
}

int main() {
    int n, m;
    cout << "请输入总人数 n 和报数上限 m: ";
    cin >> n >> m;

    list<int> outOrder = josephus(n, m);
    cout << "出列顺序: ";
    for (int x : outOrder)
        cout << x << " ";
    cout << endl;

    return 0;
}