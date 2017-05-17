#include<iostream>
using namespace std;
#include<assert.h>
void PrintSort(int* a, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
void Merge(int* src, int* dst, int left, int right)
{
	if (left >= right) 
		return;
	int mid = left + (right - left)/2;
	Merge(src, dst, left, mid);
	//PrintSort(src, 10);
	Merge(src, dst, mid + 1, right);
	//PrintSort(src, 10);
	int begin1 = left;
	int begin2 = mid + 1;
	int index = left;
	while (begin1 <= mid && begin2 <= right)
	{
		if (src[begin1] < src[begin2])
			dst[index++] = src[begin1++];
		else
			dst[index++] = src[begin2++];
	}

	while (begin1 <= mid)
		dst[index++] = src[begin1++];
	while (begin2 <= right)
		dst[index++] = src[begin2++];
		

	size_t i = left;
	while (i < index)
	{
		src[i] = dst[i];
		i++;
	}
}

void MergeSort(int* a, size_t n)
{
	assert(a);
	int* tmp = new int[n];
	Merge(a, tmp, 0, n - 1);
	delete []tmp;
}


void TestMergeSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	MergeSort(a, 10);
	PrintSort(a, 10);
}