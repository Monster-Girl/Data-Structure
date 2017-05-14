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

void Adjust(int* a, size_t n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child] < a[child + 1])
			++child;
		if (a[child]>a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		} 
		else
			break;
	}
}

void HeapSort(int* a, size_t n)
{
	assert(a);
	for (int i = (n - 2) / 2; i >= 0; --i)
		Adjust(a, n, i);
	size_t end = n - 1;
	while (end > 0)
	{
		
		swap(a[0] , a[end]);
		Adjust(a, end, 0);
		--end;
		PrintSort(a, 10);
	}
}

void TestHeapSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	HeapSort(a, 10);

}