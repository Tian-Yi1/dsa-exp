#include "../dsa/BTree.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = { 1, 2, 3, 4, 5, 6, 7 };

    // 调用 byArray 构建二叉树
    BTree<int> tree = byArray(values);

    // 输出遍历序列
    auto print = [](const int& val) { std::cout << val << " "; };

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