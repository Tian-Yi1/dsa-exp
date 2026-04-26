#include <iostream>
#include <stack>
#include <string>

int main() {
    int decimal;
    std::cout << "请输入一个十进制整数: ";
    std::cin >> decimal;

    // 特殊情况：如果输入为0，直接输出0
    if (decimal == 0) {
        std::cout << "十六进制: 0" << std::endl;
        return 0;
    }

    std::stack<int> st;   // 用于存储余数的栈

    int num = decimal;
    // 转换过程：除16取余，余数压入栈
    while (num > 0) {
        int remainder = num % 16;
        st.push(remainder);   // 余数入栈
        num /= 16;
    }

    // 输出十六进制结果（栈顶为高位，依次弹出）
    std::cout << "十六进制: ";
    while (!st.empty()) {
        int val = st.top();
        st.pop();
        // 10~15 转换为 A~F
        if (val < 10)
            std::cout << val;
        else
            std::cout << char('A' + (val - 10));
    }
    std::cout << std::endl;

    return 0;
}