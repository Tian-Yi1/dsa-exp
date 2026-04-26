#include "../dsa/CircularLinkedList_ex4p6.h"
#include <iostream>
#include "../dsa/SortAlgorithms.h"

// ==================== 带头结点的单向循环链表 ====================
template <typename T>
class HeadCircularList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val = T()) : data(val), next(nullptr) {}
    };
    Node* head;   // 头结点（虚拟节点，不存储有效数据）
    int len;

public:
    HeadCircularList() : len(0) {
        head = new Node();
        head->next = head;   // 空循环链表：头结点指向自身
    }

    ~HeadCircularList() {
        Node* cur = head->next;
        while (cur != head) {
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        delete head;
    }

    bool empty() const { return head->next == head; }
    int size() const { return len; }

    // 尾部插入：始终从 head 开始找最后一个（即 head->prev，但循环链表中可简化）
    void push_back(const T& val) {
        Node* newNode = new Node(val);
        Node* last = head;
        while (last->next != head) last = last->next;
        last->next = newNode;
        newNode->next = head;
        ++len;
    }

    // 头部插入：直接在 head 之后插入
    void push_front(const T& val) {
        Node* newNode = new Node(val);
        newNode->next = head->next;
        head->next = newNode;
        ++len;
    }

    // 删除头部（第一个有效节点）
    void pop_front() {
        if (empty()) throw std::out_of_range("pop_front on empty list");
        Node* toDel = head->next;
        head->next = toDel->next;
        delete toDel;
        --len;
    }

    // 遍历输出
    void print() const {
        std::cout << "HeadCircularList: ";
        Node* cur = head->next;
        while (cur != head) {
            std::cout << cur->data << ' ';
            cur = cur->next;
        }
        std::cout << '\n';
    }
};

// ==================== 不带头结点的单向循环链表 ====================
template <typename T>
class NoHeadCircularList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val = T()) : data(val), next(nullptr) {}
    };
    Node* tail;   // 尾指针，方便尾部快速插入（循环链表中 tail->next 就是头）
    int len;

public:
    NoHeadCircularList() : tail(nullptr), len(0) {}

    ~NoHeadCircularList() {
        if (!tail) return;
        Node* head = tail->next;
        Node* cur = head;
        do {
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        } while (cur != head);
    }

    bool empty() const { return tail == nullptr; }
    int size() const { return len; }

    // 尾部插入：需要区分空表和非空表
    void push_back(const T& val) {
        Node* newNode = new Node(val);
        if (empty()) {
            tail = newNode;
            tail->next = tail;   // 指向自己，形成环
        }
        else {
            Node* head = tail->next;
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
        ++len;
    }

    // 头部插入：同样需要区分空表
    void push_front(const T& val) {
        Node* newNode = new Node(val);
        if (empty()) {
            tail = newNode;
            tail->next = tail;
        }
        else {
            Node* head = tail->next;
            newNode->next = head;
            tail->next = newNode;
        }
        ++len;
    }

    // 删除头部
    void pop_front() {
        if (empty()) throw std::out_of_range("pop_front on empty list");
        if (len == 1) {
            delete tail;
            tail = nullptr;
        }
        else {
            Node* head = tail->next;
            tail->next = head->next;
            delete head;
        }
        --len;
    }

    void print() const {
        std::cout << "NoHeadCircularList: ";
        if (empty()) {
            std::cout << "(empty)\n";
            return;
        }
        Node* head = tail->next;
        Node* cur = head;
        do {
            std::cout << cur->data << ' ';
            cur = cur->next;
        } while (cur != head);
        std::cout << '\n';
    }
};

// ==================== 测试对比 ====================
int main() {
    // 带头结点的循环链表
    HeadCircularList<int> headList;
    headList.push_back(10);
    headList.push_back(20);
    headList.push_front(5);
    headList.push_back(30);
    std::cout << "带头结点链表: ";
    headList.print();      // 5 10 20 30
    headList.pop_front();
    std::cout << "删除头部后: ";
    headList.print();      // 10 20 30

    // 不带头结点的循环链表
    NoHeadCircularList<int> noHeadList;
    noHeadList.push_back(10);
    noHeadList.push_back(20);
    noHeadList.push_front(5);
    noHeadList.push_back(30);
    std::cout << "\n不带头结点链表: ";
    noHeadList.print();    // 5 10 20 30
    noHeadList.pop_front();
    std::cout << "删除头部后: ";
    noHeadList.print();    // 10 20 30

    // 对比实现差异
    std::cout << "\n=== 设计对比 ===\n";
    std::cout << "带头结点：\n"
        << "  - 构造函数中创建固定头结点，空链表时 head->next = head。\n"
        << "  - push_back 只需找尾，无需判空（因为头结点永远存在）。\n"
        << "  - pop_front 无需判断链表长度，因为即使只剩最后一个有效节点，删除后 head->next 仍指向 head（空状态）。\n"
        << "不带头结点：\n"
        << "  - 空链表时 tail 为 nullptr，每次插入、删除都必须判断 empty() 和单元素特殊情况。\n"
        << "  - 例如 push_back 需要区分第一次插入和后续插入，pop_front 需要特判 len==1。\n"
        << "  - 代码分支多，容易遗漏边界条件。\n";
    return 0;
}