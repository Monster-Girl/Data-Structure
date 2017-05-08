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
void InsertSort(int* a, size_t n)
{
	assert(a);
	for (size_t i = 0; i < n-1; i++)
	{
		int tmp = a[i + 1];
		int end = i;
		while (end >= 0)
		{
			if (a[end]>tmp)
			{
				a[end + 1] = a[end];
				--end;
			}
			else
				break;
		}  
		a[end + 1] = tmp;
		PrintSort(a, 10);
	}
}

void TestSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	InsertSort(a, 10);
}