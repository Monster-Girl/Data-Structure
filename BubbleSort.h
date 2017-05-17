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

void BubbleSort(int* a, size_t n)
{
	assert(a);
	for (int i = 0; i< n ; i++)
	{
		for (int j = 0; j < n-i-1; j++)
		{
			if (a[j]>a[j + 1])
			{
				swap(a[j], a[j + 1]);
				PrintSort(a, 10);
			}	
		}
	}
}


void TestBubbleSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	BubbleSort(a, 10);
	//PrintSort(a, 10);
}
