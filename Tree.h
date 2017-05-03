//求两个节点最近的公共节点
//1.假如这棵树是二叉搜索树

#include<iostream>
using namespace std;
template<class K>
struct SearchBinaryNode
{
	K _key;
	SearchBinaryNode<K>* _left;
	SearchBinaryNode<K>* _right;

	SearchBinaryNode(const K& x)
		:_key(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K>
class SearchBninaryTree
{
	typedef SearchBinaryNode<K> Node;
public:
	SearchBninaryTree()
		:_root(NULL)
	{}

	bool Insert(const K& key)
	{
		if (_root == NULL)   //1.当没有结点时，创建一个结点，并赋值给它
		{
			_root = new Node(key);
			return true;
		}

		//2.已存在结点，判断key值与结点的大小
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)      //当key < 根时，在结点的左边
			{
				parent = cur;
				cur = cur->_left;
			}

			else if (cur->_key < key)   //当key > 根时，在结点的右边
			{
				parent = cur;
				cur = cur->_right;
			}

			else
			{
				return false;
			}

		}

		if (parent->_key > key)
		{
			parent->_left = new Node(key);
			return true;
		}
		else
		{
			parent->_right = new Node(key);
			return true;
		}
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else return cur;
		}
		return NULL;
	}
	Node* FindSameParent(Node* k1, Node* k2)
	{
		K min = 0;
		K max = 0;

		if ((k1->_key) > (k2->_key))
		{
			min = k2->_key;
			max = k1->_key;
		}

		else
		{
			min = k1->_key;
			max = k2->_key;
		}

		Node* cur = _root;
		while (cur)
		{
			if (max >= cur->_key && min <= cur->_key)
				return cur;
			if (max < cur->_key)
				cur = cur->_left;
			if (min>cur->_key)
				cur = cur->_right;
		}
		return NULL;
	}
protected:
		Node* _root;
};


void TestSearchBinary()
{
	int arr[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	SearchBninaryTree<int> bst1;
	SearchBninaryTree<int> bst2;
	for (int i = 0; i < 10; i++)
		bst1.Insert(arr[i]);

	cout << (bst1.FindSameParent(bst1.Find(6), bst1.Find(9)))->_key << endl;
}
