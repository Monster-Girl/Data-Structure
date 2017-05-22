#include<iostream>
using namespace std;

class UnionSet
{
public:
	UnionSet(int n)
		:_size(n + 1)
	{
		_parent = new int[n + 1];
		memset(_parent, -1, sizeof(int)*(n + 1));
	}

	~UnionSet()
	{
		delete [] _parent;
	}

	int Find(int index)
	{
		int root = index;
		while (_parent[root] >= 0)
		{
			root = _parent[root];
		}
		return root;
	}

	void Union(int r1, int r2)
	{
		int root1 =Find(r1);
		int root2 =Find(r2);
		if (root1 != root2)
		{
			_parent[root1] += _parent[root2];
			_parent[root2] += root1;
		}
	}

protected:
	int* _parent;
	int _size;
};