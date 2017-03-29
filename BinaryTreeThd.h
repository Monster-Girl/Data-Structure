#include<iostream>
using namespace std;

enum Pointer
{
	THREAD,
	LINK
};

template<class T>
struct BinaryTreeNodeThd
{
	T _data;
	BinaryTreeNodeThd<T>* _left;
	BinaryTreeNodeThd<T>* _right;
	Pointer _leftTag;
	Pointer _rightTag;


	BinaryTreeNodeThd(const T& x)
		:_left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
		, _data(x)
	{}
};

template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;

public:
	BinaryTreeThd(T* a, size_t n, const T& invalid)
	{
		size_t index = 0;
		_root = _CreatTree(a, n, invalid, index);
	}


	//leftTag==0  left�д�ŵ���ָ�����ӽ���ָ��
	//leftTag==1  left�д�ŵ��Ǹý�������µ�ǰ�����ָ��
	void InOrderThreading()  //����������
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}

	void InOrderThd()     //��������������
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			
			cur = cur->_right;
		}
		cout << endl;
	}

	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root, prev);
	}

	void PrevOrderThd()
	{
 		Node* cur = _root;
		while(cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}

			cout << cur->_data << " ";
			cur = cur->_right;
		}
		cout << endl;
	}


protected:
	Node* _CreatTree(T* a, size_t n, const T& invalid, size_t& index)
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

	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL) return;
		_InOrderThreading(cur->_left,prev);   //�ݹ飬����������

		if (cur->_left == NULL)     //������ǰ����ǰ������
		{
			
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)    //������ǰ���ĺ������
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;      //ǰ�����ϣ���ǰ�����ǰ����
		_InOrderThreading(cur->_right, prev);   //�ݹ飬�Һ���������
	}
	
	void _PrevOrderThreading(Node* root, Node*& prev)
	{
		if (root == NULL) return;
		if (root->_left == NULL)
		{
			root->_left = prev;
			root->_leftTag = THREAD;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_right = root;
			prev->_rightTag = THREAD;
		}

		prev = root;

		if (root->_leftTag == LINK)
			_PrevOrderThreading(root->_left, prev);
		if (root->_rightTag == LINK)
			_PrevOrderThreading(root->_right, prev);
	}


protected:
	Node* _root;
};


void TestBinaryTreeThd()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array2[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8, };
	/*BinaryTreeThd<int> b(array, 10, '#');
	b.InOrderThreading();
	b.InOrderThd();*/

	BinaryTreeThd<int> b2(array, sizeof(array)/sizeof(array[0]), '#');
	b2.PrevOrderThreading();
	b2.PrevOrderThd();
}