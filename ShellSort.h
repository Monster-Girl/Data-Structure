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

void ShellSort(int* a, size_t n)
{
	assert(a);
	int gap = n;
	while (gap > 1)
	{
		
		gap = gap / 3 + 1;
		for (size_t i = 0; i < n - gap; i++)
		{
			
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				
				if (a[end]>tmp)
					a[end + gap] = a[end];
					
				else
					break;
				end -= gap;
			}
			a[end + gap] = tmp;
		}	
	}
}

void TestShellSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	ShellSort(a, 10);
}