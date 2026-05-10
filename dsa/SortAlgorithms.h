#pragma once
#include <iterator>
#include <functional>
#include "dsaUtils.h"
/*@brief 排序算法集成
* @details 包含常见的排序算法，如直接插入排序、希尔排序、冒泡排序、选择排序和快速排序等，并提供了适用于数组和迭代器范围的重载版本
* @tparam T 排序元素的类型
* @tparam Compare 可选的比较函数对象类型，默认为 std::less<T>，表示升序排序
*/
/*namespace sort {
	// 交换两数
	template<typename T>
	void swap(T& a, T& b);
	// ======================================== 排序算法 ========================================
		/*@brief 直接插入排序
		* @param arr 待排序数组
		* @param n 数组长度
		* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
		*/
	/*template<typename T, typename Compare = std::less<T>>
	void insertSort(T arr[], int n, Compare comp = Compare());
		/*@overload
		* @brief 直接插入排序，适用于迭代器范围
		* @param begin 起始迭代器
		* @param end 结束迭代器
		* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
		*/
		/*template<std::input_iterator T, typename Compare = std::less<T>>
	void insertSort(T begin, T end, Compare comp = Compare());
		/*@brief 希尔排序
		* @param arr 待排序数组
		* @param n 数组长度
		* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
		*/
		/*template<typename T, typename Compare = std::less<T>>
	void shellSort(T arr[], int n, Compare comp = Compare());
		/*@overload
		* @brief 希尔排序，适用于迭代器范围
		* @param begin 起始迭代器
		* @param end 结束迭代器
		* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
		*/
		/*template<std::input_iterator T, typename Compare = std::less<T>>
	void shellSort(T begin, T end, Compare comp = Compare());
		/*@brief 冒泡排序
		* @param arr 待排序数组
		* @param n 数组长度
		* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
		*/
		/*template<typename T, typename Compare = std::less<T>>
	void bubbleSort(T arr[], int n, Compare comp = Compare());
		/*@overload
		* @brief 冒泡排序，适用于迭代器范围
		* @param begin 起始迭代器
		* @param end 结束迭代器
		* @param comp 可选的比较函数对象，默认为 std::less<T>，表示升序排序
		*/
		/*template<std::input_iterator T, typename Compare = std::less<T>>
	void bubbleSort(T begin, T end, Compare comp = Compare());

	//  选择排序
	template<typename T>
	void selectSort(T arr[], int n);

	//  快速排序（对外接口）
	template<typename T>
	void quickSort(T arr[], int n);
	// 快速排序递归实现
	template<typename T>
	void quickSort(T arr[], int left, int right);
}*/
