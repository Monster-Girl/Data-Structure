#include<iostream>
using namespace std;
#include<assert.h>
template<class K,size_t M=3>
struct BTreeNode
{
	K _keys[M];  //�࿪һ�������������������
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
		if (ret.second >= 0)   //�����ظ��ڵ㣬����false
			return false;

		Node* cur = ret.first;
		K newKey = key;
		Node* sub = NULL;
		while (1)
		{
			InsertKey(cur, newKey, sub); 
			if (cur->_size < M)    //�ýڵ�δ����ֱ�Ӳ���
				return true;

			Node* newNode = new Node;
			size_t mid = M / 2;
			size_t index = 0;
			size_t i = 0;
			for (; i < cur->_size; ++i)
			{
				newNode->_keys[index] = cur->_keys[i];
				newNode->_subs[index] = cur->_subs[i];   //����ؼ��룬ҲҪ������

				if (cur->_subs[i])     //������Ӵ��ڣ���ô���ӵĸ���ҲҪ����
					cur->_subs[i]->_parent = newNode;

				++index;
			}
			newNode->_size++;
			newNode->_subs[index] = cur->_subs[i];  //�������һ���ڵ�
			if (cur->_subs[i])
				cur->_subs[i]->_parent = newNode;

			if (cur->_parent == NULL)  //������ڵ�
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
				newKey = cur->_keys[mid];  //�ȴ����м�ڵ㣬�����ϵ���
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