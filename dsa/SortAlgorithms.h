#pragma once
#include "dsaUtils.h"
// ======================================== 工具函数 ========================================

	// 交换两数
void swap(int& a, int& b);
// ======================================== 排序算法 ========================================
	//  插入排序
void insertSort(int arr[], int n);

	//  冒泡排序
void bubbleSort(int arr[], int n);

	//  选择排序
void selectSort(int arr[], int n);

	//  快速排序（对外接口）
void quickSort(int arr[], int n);

	// 快速排序递归实现
void quickSort(int arr[], int left, int right);
