#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	K _key;
	V _value;
	int _bf;
};


template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
	{}

	~AVLTree()
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}

			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}

		if (parent->_key >key)
		{
			parent->_left = new Node(key);
		}
		else
		{
			parent->_right = new Node(key);
		}

		while (parent)         //����ƽ������
		{
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0)    // ���ƽ�����ӵ���0���Ѿ�ƽ�⣬����Ҫ������
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}

			else      //�ж���ת��ʽ
			{
				if (parent->_bf == 2)
				{
					if (parent->_left->_bf == 1)
						RotetaL(parent);
					else
						RotateRL(parent);
				}
				else
				{
					if (parent->_left->_bf == -1)
						RotateR(parent);
					else
						RotateLR(parent);
				}
			}
		}
	}

	void RotateL(Node* parent)  //����
	{
		Node* ppNode = parent->_parent;
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;

		parent->_parent = subR;

		if (ppNode == NULL)   //�ж�parent�Ƿ�Ϊ���ڵ�
		{
			_root = subR;
			subR->_parent = NULL;
		}

		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
		parent->_bf = subR->_bf = 0;
	}

	void RotateR(Node* parent)    //�ҵ���
	{
		Node* ppNode = parent->_parent;
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_left = parent;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
		parent->_bf = subL->_bf = 0;
	}

protected:
	Node* _root;
};