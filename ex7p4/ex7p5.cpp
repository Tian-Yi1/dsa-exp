#include "../dsa/BTree.h"
#include <iostream>

int main() {
    // 用广义表表示二叉树：A(B(D,E),C(F,G))
    // 对应二叉树：
    //        A
    //      /   \
    //     B     C
    //    / \   / \
    //   D   E F   G
    std::string glist = "A(B(D,E),C(F,G))";

    // 调用 byGList 构建二叉树（使用默认分界符）
    BTree<char> tree = byGList(glist);

    // 输出遍历序列
    auto print = [](const char& ch) { std::cout << ch << " "; };

    std::cout << "先根遍历: ";
    tree.preOrderTraverse(print);
    std::cout << std::endl;

    std::cout << "中根遍历: ";
    tree.inOrderTraverse(print);
    std::cout << std::endl;

    std::cout << "后根遍历: ";
    tree.postOrderTraverse(print);
    std::cout << std::endl;

    std::cout << "层次遍历: ";
    tree.levelOrderTraverse(print);
    std::cout << std::endl;

    return 0;
}