

#include "SortAlg.h"

void SortAlg::OrderInsertSort(int data[], int length, int offset)
{
	//将data中的0号位置作为哨兵位置
	for (size_t i = offset; i < length; i++)
	{
		data[0] = data[i];
		int j = i - offset;
		for (; data[0] < data[j]; j = j - offset)//使用了哨兵元素确保不会超出界限，因此，不需要比较j与0的关系
		{
			data[j + offset] = data[j];
			data[j] = data[0];
		}
	}
	return;
}

void SortAlg::BinInsertSort(int data[], int length)
{
	//每一个数据都得进行二分查找确定插入位置
	for (size_t i = 2; i < length; i++)
	{
		///哨兵位置做临时存储
		data[0] = data[i];
		int left = 1;
		int right = i;
		///二分查找查到插入位置
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (data[i] <= data[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}//left > right结束,则left - 1 或 right + 1为插入点
		///从i元素开始将数据移位置		
		for (int j = i; j > left - 1; j--)
		{
			data[j] = data[j - 1];
		}
		data[left - 1] = data[0];
	}

}

void SortAlg::ShellSort(int data[], int length, int increment[], int k)
{
	for (size_t i = 0; i < k; i++)
	{
		OrderInsertSort(data, length, increment[i]);
	}
}

void SortAlg::QuickInsertSort(int data[], int left, int right)
{
	if (left > right)//结束标志
	{
		return;
	}

	int index = FinidMid(data, left, right);
	QuickInsertSort(data, left, index - 1);
	QuickInsertSort(data, index + 1, right);
}

int SortAlg::FinidMid(int data[], int left, int right)
{
	/*
		以此元素为分界元素进行分界，将比它大的放其右边，比其小的放左边
		使用0位置保存后，相当于其本身的位置可以用来充当临时交换的空间
	*/
	data[0] = data[left];
	int low = left;
	int high = right;

	while (low < high) {
		//1、首先，从尾往头找到比data[0]小的元素，存入分界元素原本的地址空间，不用额外的增加空间复杂度
		while (low < high && data[high] > data[0]) {
			high--;
		}
		data[low] = data[high];//2、步将小的元素存到前面，因此空出来高位的存储空间
		//3、然后，从头往尾找到比data[0]大的存入上一步空出来的高位存储空间
		while (low < high && data[low] < data[0]) {
			low++;
		}
		data[high] = data[low];
	}//结束的标志 low == high,也就是分界元素的位置

	data[low] = data[0];//将分界元素放在该位置

	return low;
}

void SortAlg::BubbSort(int data[], int length)
{
	bool flag = true;//加入优化,false表明，经过一趟的比较之后都没有满足条件，则证明已经排序好了
	for (size_t i = 1; i < length && flag; i++)
	{
		flag = false;
		for (size_t j = 1; j < length - i; j++)
		{
			if (data[j] > data[j + 1])
			{
				int temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				flag = true;
			}
		}
	}
	return;
}

void SortAlg::SelectSort(int data[], int length)
{
	for (size_t i = 1; i < length; i++)
	{
		data[0] = data[i];
		int min = data[i];
		int minIndex = 0;
		for (size_t j = i + 1; j < length; j++)
		{
			if (data[j] < min)
			{
				min = data[j];
				minIndex = j;
			}
			else
			{
				continue;
			}
		}
		data[i] = data[minIndex];
		data[minIndex] = data[0];
	}

	return;
}

void SortAlg::HeapSort(int data[], int length)
{
	///将无序序列构造成大顶堆(用作升序)或者小顶堆(用作降序)
	///从第一个非叶子节点开始调整创建大顶堆
	for (int i = (length - 1) / 2; i > 0; i--)
	{
		AdjustBigHeap(data, length, i);
	}

	///将叶子结点与根节点互换，再进行调整,上一轮调整好的位置不放入这一轮调整的范围内
	for (int i = 1; i < length; i++)
	{
		int temp = data[1];
		data[1] = data[length - i];
		data[length - i] = temp;
		AdjustBigHeap(data, length - i - 1, 1);//需要调整的节点为根节点
	}
}

void SortAlg::AdjustBigHeap(int data[], int length, int index)
{
	data[0] = data[index];//哨兵作临时存储
	int Child = 2 * index;//第一个孩子的下标
	for (; Child <= length; Child *= 2)
	{
		///存在左右孩子的情况
		if (Child + 1 <= length && data[Child + 1] > data[Child])
		{
			Child++;
		}

		if (data[Child] > data[0])
		{
			data[index] = data[Child];
			index = Child;//下表更新
		}
	}
	data[index] = data[0];//确定调整的inedx元素真实位置所在
	return;
}


void SortAlg::MergeSort(int data[], int length)
{
	int* tempArr = new int[10];
	int left = 1;
	int right = length - 1;
	MeSort(data, left, right, tempArr);
	delete[]tempArr;
	tempArr = nullptr;
	return;
}

void SortAlg::MeSort(int data[], int left, int right, int tempArr[])
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	//分：分别对左右进行排序
	MeSort(data, left, mid, tempArr);
	MeSort(data, mid + 1, right, tempArr);
	//治：使用临时内存tempArr合并左右序列的数据到data
	MergeData(data, left, right, tempArr);

	return;
}

void SortAlg::MergeData(int data[], int left, int right, int tempArr[])
{
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = 1;
	while (i <= mid && j <= right)
	{
		if (data[i] < data[j])
		{
			tempArr[k++] = data[i++];
		}
		else
		{
			tempArr[k++] = data[j++];
		}
	}
	while (i <= mid)
	{
		tempArr[k++] = data[i++];
	}
	while (j <= right)
	{
		tempArr[k++] = data[j++];
	}

	k = 1;
	while (left <= right)
	{
		data[left++] = tempArr[k++];
	}
	return;
}