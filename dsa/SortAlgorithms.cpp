#include "SortAlgorithms.h"
#include <iostream>
#include "dsaUtils.h"
	/*@brief 排序算法集成
	* @details 包含常见的排序算法，如直接插入排序、希尔排序、冒泡排序、选择排序和快速排序等，并提供了适用于数组和迭代器范围的重载版本
	* @tparam T 排序元素的类型
	* @tparam Compare 可选的比较函数对象类型，默认为 std::less<T>，表示升序排序
	*/
namespace sort {
	// 交换两数
	template <typename T>
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
	// ======================================== 排序算法 ========================================
		/*@brief 直接插入排序
		* @param arr 待排序数组
		* @param n 数组长度
		* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
		*/
	template <typename T, typename Compare = std::less<T>>
	void insertSort(T arr[], int n, Compare comp = Compare()) {
		for (int i = 1; i < n; i++) {
			T key = arr[i];///<存储当前元素
			int j = i - 1;///<从已排序部分的最后一个元素开始比较
			while (j >= 0 && comp(key, arr[j])) {
				arr[j + 1] = arr[j];///<将较大元素向右移动
				j--;
			}
			arr[j + 1] = key;///<将当前元素放到正确位置
			dsaUtils::Show(arr, n);
		}
	}
	/*@overload
	* @param begin 起始迭代器
	* @param end 结束迭代器
	* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
	*/
	template<std::input_iterator T, typename Compare = std::less<T>>
	void insertSort(T begin, T end, Compare comp = Compare()) {
		for (T i = begin;i != end;++i) {
			auto key = *i;///<存储当前元素
			T j = i;///<从已排序部分的最后一个元素开始比较
			while (j != begin && comp(key, *(j - 1))) {
				*j = *(j - 1);
				--j;
			}
			*(j + 1) = key;
			dsaUtils::Show(begin, end);
		}
	}
	/*@brief 希尔排序
	* @param arr 待排序数组
	* @param n 数组长度
	* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
	*/
	template<typename T, typename Compare = std::less<T>>
	void shellSort(T arr[], int n, Compare comp = Compare()) {
		int jump = n / 2;
		while (jump > 0) {
			for (int i = jump;i < n;i++) {
				int j = i - jump;
				while(j >= 0 && comp(arr[j + jump], arr[j])) {
					swap(arr[j], arr[j + jump]);
					j -= jump;
				}
			}
			jump /= 2;
		}
		dsaUtils::Show(arr, n); 
	}
	/*@overload
	* @brief 希尔排序，适用于迭代器范围
	* @param begin 起始迭代器
	* @param end 结束迭代器
	* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
	*/
	template<std::input_iterator T, typename Compare = std::less<T>>
	void shellSort(T begin, T end, Compare comp = Compare()) {
		int n = (int)(end - begin);
		int jump = n / 2;
		while (jump > 0) {
			for (T i = begin + jump; i != end; ++i) {
				T j = i - jump;
				while (j >= begin && comp(*i, *j)) {
					swap(*j, *(j + jump));
					j -= jump;
				}
			}
			jump /= 2;
		}
		dsaUtils::Show(begin, end);
	}
	//  冒泡排序
	void bubbleSort(int arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			bool flag = false;
			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
					swap(arr[j], arr[j + 1]);
					flag = true;
				}
			}
			dsaUtils::Show(arr, n);
			if (!flag) break;
		}
	}

	//  选择排序
	void selectSort(int arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			int minIdx = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[minIdx])
					minIdx = j;
			}
			swap(arr[i], arr[minIdx]);
			dsaUtils::Show(arr, n);
		}
	}

	//  快速排序（对外接口）
	void quickSort(int arr[], int n) {
		quickSort(arr, 0, n - 1);
	}

	// 快速排序递归实现
	void quickSort(int arr[], int left, int right) {
		if (left >= right) return;

		int pivot = arr[left];
		int i = left, j = right;

		while (i < j) {
			while (i < j && arr[j] >= pivot) j--;
			arr[i] = arr[j];
			while (i < j && arr[i] <= pivot) i++;
			arr[j] = arr[i];
		}
		arr[i] = pivot;

		dsaUtils::Show(arr, right + 1);

		quickSort(arr, left, i - 1);
		quickSort(arr, i + 1, right);
	}
}