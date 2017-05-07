#include<iostream>
using namespace std;
#include<assert.h>
template<class K,size_t M=3>
struct BTreeNode
{
	K _keys[M];  //多开一个，方便我们排序调整
	BTreeNode<K, M>* _parent;
	BTreeNode<K, M>* _subs[M - 1];
	size_t _size;

	BTreeNode()
	{
		memset(_subs, 0, sizeof(_subs));
		_parent = NULL;
		_size = 0;
	}
};

template<class K, size_t M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size = 1;
			return true;
		}
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)   //存在重复节点，返回false
			return false;

		Node* cur = ret.first;
		K newKey = key;
		Node* sub = NULL;
		while (1)
		{
			InsertKey(cur, newKey, sub); 
			if (cur->_size < M)    //该节点未满，直接插入
				return true;

			Node* newNode = new Node;
			size_t mid = M / 2;
			size_t index = 0;
			size_t i = 0;
			for (; i < cur->_size; ++i)
			{
				newNode->_keys[index] = cur->_keys[i];
				newNode->_subs[index] = cur->_subs[i];   //处理关键码，也要处理孩子

				if (cur->_subs[i])     //如果孩子存在，那么孩子的父亲也要处理
					cur->_subs[i]->_parent = newNode;

				++index;
			}
			newNode->_size++;
			newNode->_subs[index] = cur->_subs[i];  //处理最后一个节点
			if (cur->_subs[i])
				cur->_subs[i]->_parent = newNode;

			if (cur->_parent == NULL)  //处理根节点
			{
				_root = new Node;
				_root->_keys[0] = cur->_keys[mid];
				_root->_subs[0] = cur;
				cur->_parent = _root;
				_root->_subs[1] = newNode;
				newNode->_parent = _root;
				return true;
			}

			else
			{
				newKey = cur->_keys[mid];  //先处理中间节点，在向上调整
				cur = cur->_parent;
				sub = newNode;
			}
		}
	}

	pair<Node*, size_t> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			for (; i < cur->_size; i++)
			{
				if (cur->_keys[i]>key)
					break;
				else if (cur->_keys[i] < key)
					++i;
				else
					return make_pair(cur, i);
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return make_pair(parent, -1);
	}

	void InsertKey(Node* cur, const K& key, Node* sub)
	{
		assert(cur);
		int end = cur->_size - 1;
		for (; end >= 0; --end)
		{
			if (cur->_keys[end] > key)
			{
				cur->_keys[end + 1] = cur->_keys[end];
				cur->_subs[end + 2] = cur->_subs[end + 1];
			}
			else
				break;
		}
		cur->_keys[end + 1] = key;
		cur->_subs[end + 2] = sub;
		if (sub)
			sub->_parent = cur;
		cur->_size++;
	}

protected:
	Node* _root;
};

void TestBTree()
{
	BTree<int> b1;
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (size_t i = 0; i < 7; i++)
	{
		b1.Insert(a[i]);
	}

}