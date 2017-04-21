#include<iostream>
using namespace std;
#include<assert.h>
enum Color
{
	RED,
	BLACK,
};

template<class K, class V>
struct RBTreeNode
{
	K _key;
	V _value;
	Color _color;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	RBTreeNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _color(RED)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}


	pair<Node*, bool> Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return make_pair(_root, true);
			
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}

			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}

			else
				return make_pair(cur,false);
				
		}

		cur = new Node(key, value);
		if (parent->_key > key)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		while (parent && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;      //1.判断父亲和叔叔的关系
			if (parent == grandfather->_left)       //父亲在左，叔叔在右
			{
				Node* uncle = grandfather->_right;    //2.判断叔叔的情况
				if (uncle != NULL && uncle->_color == RED)    //a.叔叔存在且为红 -> 变色
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}

				else   //b.叔叔不存在或者叔叔为黑
				{
					if (cur == parent->_right)  
					{
						RotateL(parent);
						swap(cur, parent);
					}

					RotateR(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;
				}
			}


			else       //叔叔在左，父亲在右
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_color == RED)    //叔叔存在且为红 ，变色
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}

				else    //叔叔不存在或为黑
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}

					RotateL(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;
				}
			}

		}
		_root->_color = BLACK;
		return make_pair(_root, true);
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		if (_root == NULL) return true;
		if (_root->_color == RED) return false;

		int BlackNum = 0;    //统计一条路径的黑色节点数量
		Node* left = _root;
		while (left)
		{
			if (left->_color == BLACK)
				BlackNum++;
			left = left->_left;
		}

		int count = 0;
		return _IsBalance(_root,BlackNum,count);
	}

protected:
	void _Inorder(Node* root)
	{
		if (root == NULL)
			return;
		_Inorder(root->_left);
		cout << root->_key << " ";
		_Inorder(root->_right);
	}

	void RotateR(Node* parent)
	{
		assert(parent);
		Node* child = parent->_left;
		Node* grandfather = parent->_parent;
		Node* Rchild = child->_right;

		if (Rchild)
			Rchild->_parent =parent ;
		parent->_left = Rchild;
		parent->_parent = child;
		child->_right = parent;

		if (grandfather == NULL)
		{
			child->_parent = NULL;
			_root = child;
		}

		else
		{
			if (grandfather->_left == parent)
				grandfather->_left = child;

			else
				grandfather->_right = child;

			child->_parent = grandfather;
		}
	}

	void RotateL(Node* parent)
	{
		assert(parent);
		Node* child = parent->_right;
		Node* Lchild = child->_left;
		Node* grandfather = parent->_parent;
		if (Lchild)
			Lchild->_parent = parent;
		parent->_right = Lchild;
		parent->_parent = child;
		child->_left = parent;

		if (grandfather == NULL)
		{
			_root = child;
			child->_parent = NULL;
		}

		else
		{
			if (parent == grandfather->_left)
				grandfather->_left = child;
			else
				grandfather->_right = child;

			child->_parent = grandfather;
		}
	}

	bool _IsBalance(Node* root, const int BlackNum, int count)
	{
		if (root == NULL)  return true;
		if (root->_color == RED && root->_parent->_color == RED)
		{
			cout << "存在连续红节点" << endl;
			return false;
		}

		if (root->_color == BLACK)
			++count;

		if (root->_left == NULL && root->_right == NULL)
		{
			if (count != BlackNum)
			{
				cout << "黑节点数目不同" << endl;
				return false;
			}
				
			else
				return true;
		}
		return _IsBalance(root->_left, BlackNum, count) && _IsBalance(root->_right, BlackNum, count);
	}

protected:
	Node* _root;
};


void TestRBTree()
{
	RBTree<int, int> rb1;
	rb1.Insert(1,1);
	rb1.Insert(2,2);
	rb1.Insert(3,3);
	rb1.Insert(4,4);
	rb1.Insert(5,5);
	rb1.Inorder();

	cout<<rb1.IsBalance()<<endl;

}