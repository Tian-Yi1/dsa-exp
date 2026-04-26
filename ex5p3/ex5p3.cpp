#include <iostream>
#include <stack>       // 标准库栈，用于对比
#include <stdexcept>
#include "../dsa/Mystack.h"

std::string decimalToHexUsingSeqStack(int decimal) {
    if (decimal == 0) return "0";

    SequencedStack<int> st;
    int num = decimal;
    while (num > 0) {
        st.push(num % 16);
        num /= 16;
    }

    std::string hex = "";
    while (!st.empty()) {
        int val = st.top();
        st.pop();
        if (val < 10)
            hex += char('0' + val);
        else
            hex += char('A' + (val - 10));
    }
    return hex;
}

std::string decimalToHexUsingStdStack(int decimal) {
    if (decimal == 0) return "0";

    std::stack<int> st;
    int num = decimal;
    while (num > 0) {
        st.push(num % 16);
        num /= 16;
    }

    std::string hex = "";
    while (!st.empty()) {
        int val = st.top();
        st.pop();
        if (val < 10)
            hex += char('0' + val);
        else
            hex += char('A' + (val - 10));
    }
    return hex;
}

// ==================== 主函数 ====================
int main() {
    int decimal;
    std::cout << "请输入一个十进制整数: ";
    std::cin >> decimal;

    // 使用自定义 SequencedStack
    std::string hex1 = decimalToHexUsingSeqStack(decimal);
    std::cout << "使用 SequencedStack 转换结果: " << hex1 << std::endl;

    // 使用标准库 stack 对比
    std::string hex2 = decimalToHexUsingStdStack(decimal);
    std::cout << "使用 std::stack 转换结果: " << hex2 << std::endl;
    return 0;
}