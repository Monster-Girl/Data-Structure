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

void SelectSort(int* a, size_t n)
{
	assert(a);
	int left = 0;
	int right = n - 1;
	while (left < right)
	{
		PrintSort(a, n);
		size_t minIndex = left;
		size_t maxIndex = right;
		for (size_t i = left; i <= right; i++)
		{
			
			if (a[i] < a[minIndex])
				minIndex = i;
			if (a[i] > a[maxIndex])
				maxIndex = i;
		}
		
		swap(a[left], a[minIndex]);
		if (maxIndex == left)  //当最大的恰好在最左边时，会多交换一次
			maxIndex = minIndex; 
		swap(a[right], a[maxIndex]);
		++left;
		--right;
	}
}

void TestSelectSort()
{
	int a[] = { 9, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	SelectSort(a, 10);
}