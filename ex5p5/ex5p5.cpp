#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../dsa/Mystack.h"

// 工具函数：返回运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;   // 其他（如括号）优先级最低
}

// 判断字符是否为运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 中缀表达式转后缀表达式（使用 SequencedStack<char>）
std::string infixToPostfix(const std::string& infix) {
    SequencedStack<char> opStack;
    std::string postfix = "";
    for (char ch : infix) {
        if (isspace(ch)) continue;          // 忽略空格
        if (isdigit(ch)) {                  // 操作数直接输出
            postfix += ch;
        }
        else if (ch == '(') {
            opStack.push(ch);
        }
        else if (ch == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // 弹出 '('
            else throw std::runtime_error("括号不匹配");
        }
        else if (isOperator(ch)) {
            while (!opStack.empty() && opStack.top() != '(' &&
                precedence(opStack.top()) >= precedence(ch)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(ch);
        }
        else {
            throw std::runtime_error(std::string("无效字符: ") + ch);
        }
    }
    while (!opStack.empty()) {
        if (opStack.top() == '(' || opStack.top() == ')')
            throw std::runtime_error("括号不匹配");
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

int evaluatePostfix(const std::string& postfix) {
    SequencedStack<int> valStack;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            valStack.push(ch - '0');
        }
        else if (isOperator(ch)) {
            if (valStack.size() < 2)
                throw std::runtime_error("表达式错误：操作数不足");
            int b = valStack.top(); valStack.pop();
            int a = valStack.top(); valStack.pop();
            int result = 0;
            switch (ch) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) throw std::runtime_error("除零错误");
                result = a / b;
                break;
            }
            valStack.push(result);
        }
        else {
            throw std::runtime_error(std::string("无效后缀字符: ") + ch);
        }
    }
    if (valStack.size() != 1)
        throw std::runtime_error("表达式错误：最终栈内应只有一个值");
    return valStack.top();
}

int main() {
    try {
        std::string infix;
        std::cout << "请输入中缀表达式（支持 + - * / 和括号，操作数为0-9的一位整数）: ";
        std::getline(std::cin, infix);

        std::string postfix = infixToPostfix(infix);
        std::cout << "后缀表达式: " << postfix << std::endl;

        int result = evaluatePostfix(postfix);
        std::cout << "计算结果: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}