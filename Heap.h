#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;


//���
//template<class T>
//class Heap
//{
//public:
//	Heap()
//	{}
//
//	Heap(T* a, size_t n)
//	{
//		_a.reserve(n); 
//		for (size_t i = 0; i < n; i++)
//		{
//			_a.push_back(a[i]);
//		}
//
//		for (int i = _a.size() - 2 / 2; i >= 0; --i)
//			_AdjustDown(i);
//	}
//
//	void Push(const T& x)
//	{
//		_a.push_back(x);
//		_AdjustUp(_a.size() - 1);   //�������ǲ�������һ��Ԫ�أ��������һ������
//	}
//
//	void Pop()
//	{
//		assert(!_a.empty());
//		swap(_a[0], _a[_a.size() - 1]);
//		_a.pop_back();
//		_AdjustDown(0);
//	}
//
//protected:
//	void _AdjustDown(int root)
//	{
//		int parent = root;
//		int child = root * 2 + 1;
//		while (child < _a.size())
//		{
//			if (child + 1 < _a.size() && _a[child] < _a[child + 1])
//				++child;
//			if (_a[child]>_a[parent])
//			{
//				swap(_a[child], _a[parent]);
//				parent = child;
//				child = parent * 2 + 1;
//			}
//			else
//				break;
//		}
//	}
//
//	void _AdjustUp(int child)
//	{
//		int parent = (child - 1) >> 1;
//		while (child > 0)
//		{
//			if (_a[child] > _a[parent])
//			{
//				swap(_a[child], _a[parent]);
//				child = parent;
//				parent = (child - 1) >> 1;
//			}
//			else
//				break;
//		}
//	}
//
//protected:
//	vector<T> _a;
//};


//����ѣ��÷º�������ʵ��
template<class T>
struct Less
{
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <class T>
struct Great
{
	bool operator()(const T& l, const T& r) const
	{
		return l > r;
	}
};

template<class T,class Compare>
class Heap
{
public:
	Heap()
	{}

	Heap(T* a, size_t n)
	{
		_a.reserve(n); 
		for (size_t i = 0; i < n; i++)
		{
			_a.push_back(a[i]);
		}

		for (int i = _a.size() - 2 / 2; i >= 0; --i)
			_AdjustDown(i);
	}

	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size() - 1);   //�������ǲ�������һ��Ԫ�أ��������һ������
	}

	void Pop()
	{
		assert(!_a.empty());
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}

protected:
	void _AdjustDown(int root)
	{
		Compare comFunc;
		int parent = root;
		int child = root * 2 + 1;
		while (child < _a.size())
		{
			if (child + 1 < _a.size() && _a[child] < _a[child + 1])
				++child;
			if (comFunc( _a[child],_a[parent]))
			{
				swap(_a[child], _a[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}

	void _AdjustUp(int child)
	{
		Compare comFunc;
		int parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (comFunc(_a[child], _a[parent]))
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
				break;
		}
	}

protected:
	vector<T> _a;
};




void TestHeap()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Heap<int,Less<int>> h(a, 10);
	h.Push(30);
	h.Pop();
}