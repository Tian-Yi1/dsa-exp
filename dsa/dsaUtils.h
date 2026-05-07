#pragma once
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
namespace dsaUtils {
	//随机数函数,参数(首地址,大小,随机数种子,随机最小值,随机最大值)
	void RandomData(int* a, int b, unsigned int seed = 1, int minValue = -99, int maxValue = 99);
	//泛型函数show,C形式传指针(首地址,长度)
	template<typename T>
	void Show(T* a, int cnt) {
		for (int i = 0;i < cnt;i++) {
			std::cout << a[i] << ' ';
		}
		std::cout << std::endl;
	}
	//泛型函数show,C++形式传迭代器(v.begin,v.end)
	template<typename IIt>
	void Show(IIt begin, IIt end) {
		while (begin != end) {
			std::cout << *begin << ' ';
			begin++;
		}
		std::cout << std::endl;
	}
}