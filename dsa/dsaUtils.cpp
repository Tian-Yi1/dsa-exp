#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include "dsaUtils.h"
using namespace std;
void RandomData(int* a, int b, unsigned int seed, int minValue, int maxValue) {
	srand(seed);
	int u = 0;
	for (int i = 0; i < b; i++) {
		u = (int)((double)rand() / (double)(RAND_MAX + 1) * (maxValue - minValue)) + minValue;
		*(a + i) = u;
	}
}