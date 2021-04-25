// 定义应用程序的入口点。
//
#include "SortAlg.h"
#include <iostream>

using namespace std;

int main()
{
	int quick[] = { 0,2,6,8,7,5,3,9,1,4 };
	int data[] = { 0,1,2,3,4,5 };
	int a[] = { 0,5,4,1,2,3 };

	SortAlg test;
	test.MergeSort(quick, 10);


	for (size_t i = 1; i < 10; i++)
	{
		cout << quick[i] << ",";
	}
	cin.get();
	return 0;
}