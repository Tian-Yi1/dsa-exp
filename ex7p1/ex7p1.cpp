#include "../dsa/BTree.h"
#include <iostream>

int main() {
    BTNode<int>* node4 = new BTNode<int>(4);
    BTNode<int>* node5 = new BTNode<int>(5);
    BTNode<int>* node6 = new BTNode<int>(6);
    BTNode<int>* node2 = new BTNode<int>(2, node4, node5);
    BTNode<int>* node3 = new BTNode<int>(3, node6, nullptr);
    BTNode<int>* node1 = new BTNode<int>(1, node2, node3);

    BTree<int> tree(node1);

    auto print = [](const int& val) { std::cout << val << " "; };

    std::cout << "前序遍历: ";
    tree.preOrderTraverse(print);
    std::cout << std::endl;

    std::cout << "中序遍历: ";
    tree.inOrderTraverse(print);
    std::cout << std::endl;

    std::cout << "后序遍历: ";
    tree.postOrderTraverse(print);
    std::cout << std::endl;

    std::cout << "层次遍历: ";
    tree.levelOrderTraverse(print);
    std::cout << std::endl;

    return 0;
}