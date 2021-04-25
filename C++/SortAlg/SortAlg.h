// SortAlg.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#ifndef __SORTALG_H__
#define __SORTALG_H__
#include <iostream>

class SortAlg
{
public:
	SortAlg() {}
	~SortAlg() {}

	/**
		插入排序：
		  1、顺序插入排序：使用顺序查找法确定数据插入的位置
		  2、折半插入排序：使用二分查找法确定数据插入的位置
		  3、希尔排序：根据某特定的增量序列来进行顺序插入
	*/

	///顺序插入排序
	/// 为兼容希尔排序，加入offset表示增量，当offset=1为顺序插入排序
	void OrderInsertSort(int data[], int length, int offset = 1);

	///折半插入排序
	void BinInsertSort(int data[], int length);

	///希尔排序
	void ShellSort(int data[], int length, int increment[], int k);

	/**
		交换排序：
		  1、快速排序：找出中间元素，比其小的放其左边，比其大的放其右边
		  2、冒泡排序：每一趟，对列表元素两两比较，将最大的元素冒泡到后方
	*/
	///快速排序
	void QuickInsertSort(int data[], int left, int right);
	///找到快速排序分界元素在数组中的位置
	int FinidMid(int data[], int left, int right);

	///冒泡排序
	void BubbSort(int data[], int length);

	/**
		选择排序：
		  1、简单选择排序
		  2、堆排序
	*/
	///简单选择排序
	void SelectSort(int data[], int length);

	///堆排序
	void HeapSort(int data[], int length);
	/// 调整大顶堆
	void AdjustBigHeap(int data[], int length, int index);

	/**
		其他排序：
		  1、归并排序
		  2、基数排序
	*/
	/**
		归并排序：将两个有序的序列归并到一临时序列中
	*/
	void MergeSort(int data[], int length);
	/// 确保序列的有序
	void MeSort(int data[], int left, int right, int tempArr[]);
	/// 将两序列合并
	void MergeData(int data[], int left, int right, int tempArr[]);

private:

};






#endif // !__SORTALG_H__
