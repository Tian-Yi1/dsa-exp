#include <iostream>
#include "../dsa/SequencedList.h"
using namespace std;
int main() {
    SequencedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    cout << list << endl;

    list.insert(1, 99);
    cout << list << endl;

    list.remove(2);
    cout << list << endl;

    list.removeElement(99);
    cout << list << endl;

    cout << list.find(30) << endl;
    cout << list.contains(40) << endl;
    cout << list.contains(99) << endl;

    list.set(0, 100);
    cout << list.get(0) << endl;
    cout << list << endl;

    cout << list[1] << endl;
    list[1] = 200;
    cout << list << endl;

    SequencedList<int> list2(list);
    cout << list2 << endl;

    SequencedList<int> list3;
    list3 = list;
    cout << list3 << endl;

    list.reverse();
    cout << list << endl;

    list.sort();
    cout << list << endl;

    list.push_back(200);
    list.unique();
    cout << list << endl;

    SequencedList<int> sub = list.subList(0, 2);
    cout << sub << endl;

    cout << list.getSize() << endl;
    cout << list.getCapacity() << endl;
    cout << list.isEmpty() << endl;

    list.clear();
    cout << list << endl;

    return 0;
}
