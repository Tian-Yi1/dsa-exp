#include "SortAlgorithms.h"
#include <iostream>
#include "dsaUtils.h"
using namespace std;
// ======================================== 工具函数 ========================================

	// 交换两数
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
// ======================================== 排序算法 ========================================
	//  插入排序
void insertSort(int arr[], int n) {
	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		Show(arr, n);
	}
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
		Show(arr, n);
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
		Show(arr, n);
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

	Show(arr, right + 1);

	quickSort(arr, left, i - 1);
	quickSort(arr, i + 1, right);
}