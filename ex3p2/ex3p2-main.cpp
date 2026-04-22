#include "ex3p2-Robot.h"
#include <iostream>
#include <algorithm>
#include "../dsa/dsaUtils.h"
using namespace std;
int main() {
    const int SIZE = 5;
    Robot robots[SIZE] = {
        Robot(102, "Alpha", 120.5),
        Robot(101, "Beta", 150.0),
        Robot(105, "Gamma", 90.8),
        Robot(103, "Delta", 135.2),
        Robot(104, "Epsilon", 110.0)
    };
    Show(robots, robots + SIZE);
    sort(robots, robots + SIZE, cmpByID);
    Show(robots, robots + SIZE);
    sort(robots, robots + SIZE, cmpByIQ);
    Show(robots, robots + SIZE);
}