//求两个节点最近的公共节点
//1.假如这棵树是二叉搜索树

//#include<iostream>
//using namespace std;
//
//template<class K>
//struct SearchBinaryNode
//{
//	K _key;
//	SearchBinaryNode<K>* _left;
//	SearchBinaryNode<K>* _right;
//
//	SearchBinaryNode(const K& x)
//		:_key(x)
//		, _left(NULL)
//		, _right(NULL)
//	{}
//};
//
//template<class K>
//class SearchBninaryTree
//{
//	typedef SearchBinaryNode<K> Node;
//public:
//	SearchBninaryTree()
//		:_root(NULL)
//	{}
//
//	bool Insert(const K& key)
//	{
//		if (_root == NULL)   //1.当没有结点时，创建一个结点，并赋值给它
//		{
//			_root = new Node(key);
//			return true;
//		}
//
//		//2.已存在结点，判断key值与结点的大小
//		Node* parent = NULL;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key > key)      //当key < 根时，在结点的左边
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//
//			else if (cur->_key < key)   //当key > 根时，在结点的右边
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//
//			else
//			{
//				return false;
//			}
//
//		}
//
//		if (parent->_key > key)
//		{
//			parent->_left = new Node(key);
//			return true;
//		}
//		else
//		{
//			parent->_right = new Node(key);
//			return true;
//		}
//	}
//
//	Node* Find(const K& key)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key > key)
//				cur = cur->_left;
//			else if (cur->_key < key)
//				cur = cur->_right;
//			else return cur;
//		}
//		return NULL;
//	}
//	Node* FindSameParent(Node* k1, Node* k2)
//	{
//		K min = 0;
//		K max = 0;
//
//		if ((k1->_key) > (k2->_key))
//		{
//			min = k2->_key;
//			max = k1->_key;
//		}
//
//		else
//		{
//			min = k1->_key;
//			max = k2->_key;
//		}
//
//		Node* cur = _root;
//		while (cur)
//		{
//			if (max >= cur->_key && min <= cur->_key)
//				return cur;
//			if (max < cur->_key)
//				cur = cur->_left;
//			if (min>cur->_key)
//				cur = cur->_right;
//		}
//		return NULL;
//	}
//protected:
//		Node* _root;
//};
//
//void TestSearchBinary()
//{
//	int arr[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
//	SearchBninaryTree<int> bst1;
//	SearchBninaryTree<int> bst2;
//	for (int i = 0; i < 10; i++)
//		bst1.Insert(arr[i]);
//
//	cout << (bst1.FindSameParent(bst1.Find(6), bst1.Find(9)))->_key << endl;
//}

//2.假设这是一棵普通的二叉树。
//a.假设有父节点,改成求两个链表的公共节点。
//#include<iostream>
//using namespace std;
//#include<vector>
//template<class T>
//struct BinaryTreeNode
//{
//	BinaryTreeNode<T>* _left;
//	BinaryTreeNode<T>* _right;
//	BinaryTreeNode<T>* _parent;
//	T _data;
//
//	BinaryTreeNode(const T& data)
//		:_left(NULL)
//		, _right(NULL)
//		, _data(data)
//		, _parent(NULL)
//	{}
//};
//
//template<class T>
//class BinaryTree
//{
//public:
//	typedef BinaryTreeNode<T> Node;
//	BinaryTree()
//		:_root(NULL)
//	{}
//
//	~BinaryTree()
//	{}
//
//	BinaryTree(T* a, size_t n, const T& invalid = T())
//	{
//		size_t index = 0;
//		Node* parent = NULL;
//		_root = _CreatTree(a, n, invalid, index,NULL);
//	}
//
//	Node* Find(const T& data)
//	{
//		return _Find(_root, data);
//	}
//
//
//
//protected:
//		Node* _CreatTree(T* a, size_t n, const T& invalid , size_t& index,Node* parent)
//		{
//			Node* root = NULL;
//			if (index < n && a[index] != invalid)
//			{
//				root = new Node(a[index]);
//				root->_parent = parent;
//				root->_left = _CreatTree(a, n, invalid, ++index,root);
//				root->_right = _CreatTree(a, n, invalid, ++index,root);
//			}
//			return root;
//		}
//	
//		Node* _Find(Node* root, const T& data)
//		{
//			if (root == NULL)
//				return NULL;
//			if (root->_data == data)
//				return root;
//			Node* cur = _Find(root->_left, data);
//			if (cur)
//				return cur;
//			return _Find(root->_right, data);
//		}
//
//	Node* _Find(Node* root, const T& data)
//	{
//		if (root == NULL)
//			return NULL;
//		if (root->_data == data)
//			return root;
//		Node* cur = _Find(root->_left, data);
//		if (cur)
//			return cur;
//		return _Find(root->_right, data);
//	}
//
//protected:
//		Node* _root;
//};
//
//void TestBinaryTree()
//{
// 	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
//	BinaryTree<int> t(array, 10, '#');
//	BinaryTree<int>::Node* k1 = t.Find(3);
//	BinaryTree<int>::Node* k2 = t.Find(6);
//	BinaryTree<int>::Node* ret = t.FindSameParent(k1,k2);
//	cout <<ret->_data << endl;
//}

//b.没有父节点
#include<iostream>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;

	BinaryTreeNode(const T& data)
		:_left(NULL)
		, _right(NULL)
		, _data(data)
	{}
};

template<class T>
class BinaryTree
{

public:
	typedef BinaryTreeNode<T> Node;
	BinaryTree()
		:_root(NULL)
	{}

	~BinaryTree()
	{}

	BinaryTree(T* a, size_t n, const T& invalid = T())
	{
		size_t index = 0;
		_root = _CreatTree(a, n, invalid, index);
	}



	Node* Find(const T& data)
	{
		return _Find(_root, data);
	}

	/*Node* FindSameParent(Node* k1, Node* k2)
	{
		return _FindSameParent(_root, k1, k2);
	}*/

	Node* FindSameParent(Node* k1, Node* k2)
	{
		if (_root == NULL)
			return NULL;
		stack<Node*> s1;
		stack<Node*> s2;

		_GetPath(_root, k1, s1);
		_GetPath(_root, k2, s2);

		while (s1.size() > s2.size())
		{
			s1.pop();
		}

		while (s1.size() < s2.size())
		{
			s2.pop();
		}

		while (s1.top() != s2.top())
		{
			s1.pop();
			s2.pop();
		}
		return s1.top();
	}

protected:
	Node* _CreatTree(T* a, size_t n, const T& invalid , size_t& index)
	{
		Node* root = NULL;
		if (index < n && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreatTree(a, n, invalid, ++index);
			root->_right = _CreatTree(a, n, invalid, ++index);
		}
		return root;
	}

	bool _GetPath(Node* root, Node* k, stack<Node*>& s)
	{
		if (root == NULL)
			return false;
		if (k == root)
		{
			s.push(root);
			return true;
		}
		s.push(root);
		if(_GetPath(root->_left, k, s))
			return true;
		
		if(_GetPath(root->_right, k, s))
			return true;
		s.pop();
		return false;
	}

	Node* _Find(Node* root, const T& data)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == data)
			return root;
		Node* cur = _Find(root->_left, data);
		if (cur)
			return cur;
		return _Find(root->_right, data);
	}

	/*Node* _FindSameParent(Node* root, Node* k1, Node* k2)
	{
		if (root == NULL)
			return NULL;
		if (root == k1 || root == k2)
			return root;
		Node* _k1 = _FindSameParent(root->_left, k1, k2);
		Node* _k2 = _FindSameParent(root->_right, k1, k2);
		if (_k1 && _k2)
			return root;
		return _k1 ? _k1 : _k2;
	}*/

protected:
	Node* _root;

};

void TestBinaryTree()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t(array, 10, '#');
	BinaryTree<int>::Node* k1 = t.Find(3);
	BinaryTree<int>::Node* k2 = t.Find(6);
	BinaryTree<int>::Node* ret = t.FindSameParent(k1,k2);
	cout <<ret->_data << endl;
}