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

	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else return true;
		}
		return false;
	}

	bool Remove(const K& key)
	{
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
			{
				Node* del = cur;
				if (cur->_left == NULL)
				{
					if (parent->_right == cur)
					{
						parent->_right = cur->_right;
					}

					else
						parent->_left = cur->_right;
				}
				else if (cur->_right == NULL)
				{
					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else
						parent->_right = cur->_left;

				}

				else   //替代法
				{
					Node* subRight = cur->_right;
					Node* subParent = cur;
					while (subRight->_left)
					{
						subRight = subRight->_left;
					}

					cur->_key = subRight->_key;
					del = subRight;

					if (subParent->_right == subRight)
						subParent->_right = subRight->_right;
					else
						subParent->_left = subRight->_left;
				}
				delete del;
				return true;
			}
		}
		return false;
	}

protected:
	bool _InsertR(Node*& root, const K& key)
	{
		if (root == NULL)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key > key)
		{
			_InsertR(root->_left, key);
			return true;
		}

		if (root->_key < key)
		{
			_InsertR(root->_right, key);
			return true;
		}
		return false;
	}

	bool _FindR(Node* root, const K& key)
	{
		if (root==NULL) return false;
		else if (root->_key > key)
			_FindR(root->_left, key);
		else if (root->_key < key)
			_FindR(root->_right, key);

		else
			return root;
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

		for (int i = 0; i < 10; i++)
			bst2.InsertR(arr[i]);

		/*cout << bst1.Find(0) << endl;
		cout << bst1.Find(2) << endl;
		cout << bst1.Find(4) << endl;
		cout << bst1.Find(6) << endl;
		cout << bst1.Find(9) << endl;
		cout << bst1.Find(10) << endl;*/
		
		//bst1.Remove(4);
		//bst1.Remove(6);
		//bst1.Remove(9);
		//bst1.Remove(5);

		cout << bst1.FindR(0) << endl;
		cout << bst1.FindR(2) << endl;
		cout << bst1.FindR(4) << endl;
		cout << bst1.FindR(6) << endl;
		cout << bst1.FindR(9) << endl;
		cout << bst1.FindR(10) << endl;
	}