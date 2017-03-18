#include<iostream>
#include<queue>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;

	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}

	~BinaryTree()
	{}

	BinaryTree(T* a, size_t n, const T& invalid = T())
	{
		size_t index = 0;
		_root=_CreatTree(a, n, invalid, index);
	}

	void PrevOrder()
	{
		cout << "PrevOrder:";
		_PrevOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		cout << "PostOrder:";
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()
	{
		cout << "LevelOrder:";
		queue<Node*> q;
		if (_root)
			q.push(_root);
		while (!q.empty())
		{
			Node* tmp = q.front();
			cout << tmp->_data << " ";
			q.pop();
			if (tmp->_left)  q.push(tmp->_left);
			if (tmp->_right) q.push(tmp->_right);
		}

		cout << endl;
	}

	size_t Size()
	{
		return _Size(_root);
	}

	size_t GetLeafSize()
	{
		return _GetLeafSize(_root);
	}

	size_t GetKLevelSize(size_t k)
	{
		return _GetKLevelSize(_root, k);
	}

protected:
	Node*	_CreatTree(T* a, size_t n, const T& invalid, size_t& index)
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

	void _PrevOrder(Node* root)
	{
		if (root == NULL) return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL) return;
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PostOrder(Node* root)
	{
		if (root == NULL) return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	size_t _Size(Node* root)
	{
		if (root == NULL) return 0;
		return _Size(root->_left) + _Size(root->_right)+1;
	}

	size_t _GetLeafSize(Node* root)
	{
		if (root == NULL) return 0;
		if (root->_left == NULL && (root->_right == NULL)) return 1;
		return _GetLeafSize(root->_left) + _GetLeafSize(root->_right);
	}

	size_t _GetKLevelSize(Node* root, size_t k)
	{
		if (root == NULL) return 0;
		if (k == 0) return 1;
		return _GetKLevelSize(root->_left, k - 1) + _GetKLevelSize(root->_right, k - 1);
 	}

protected:
	Node* _root;
};


void TestBinaryTree()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t(array, 10, '#');
	t.PrevOrder();
	t.InOrder();
	t.PostOrder();
	t.LevelOrder();
	cout<<"Size:"<<t.Size()<<endl;
	cout << "LeafSize:" << t.GetLeafSize() << endl;
	cout << "k层的节点数:" << t.GetKLevelSize(2) << endl;
}