#include <iostream>
#include "..\dsa\Mystack.h" 

using namespace std;

void testLinkedStack() {
    cout << "===== LinkedStack 测试开始 =====" << endl;

    LinkedStack<int> st;
    cout << "初始状态: empty = " << boolalpha << st.empty()
        << ", size = " << st.size() << endl;

    for (int i = 1; i <= 5; ++i) {
        st.push(i * 10);
        cout << "push(" << i * 10 << ") -> top = " << st.top()
            << ", size = " << st.size() << endl;
    }

    while (!st.empty()) {
        cout << "top = " << st.top() << ", 准备 pop..." << endl;
        st.pop();
        cout << "pop 后 size = " << st.size() << endl;
    }

    try {
        st.pop();
    }
    catch (const out_of_range& e) {
        cerr << "捕获异常（pop）: " << e.what() << endl;
    }

    try {
        st.top();
    }
    catch (const out_of_range& e) {
        cerr << "捕获异常（top）: " << e.what() << endl;
    }

    st.push(100);
    st.push(200);
    cout << "重新压栈后: top = " << st.top() << ", size = " << st.size() << endl;
    st.pop();
    cout << "pop 后 top = " << st.top() << ", size = " << st.size() << endl;

    cout << "===== LinkedStack 测试结束 =====\n" << endl;
}

int main() {
    testLinkedStack();
    return 0;
}