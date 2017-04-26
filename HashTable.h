#include<iostream>
using namespace std;

#include<vector>
#include<string>
template<class K>
struct _HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct _HashFunc<string>
{
	static size_t BKDRHash(const char* str)
	{
		unsigned int seed = 131;// 31 131 1313 13131 131313   
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return(hash & 0x7FFFFFFF);
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};


template<class K,class V>
struct HashNode
{
	pair<K, V> _kv;
	HashNode<K, V>* _next;
};

template<class K, class V, class HashFunc = _HashFunc<k>>
class HashTable
{
	typedef HashNode<K, V> Node
public:
	HashTable()
		:_size(0)
	{}

	~HashTable()
	{
		Destory();
	}

	bool Insert(const pair<K,V>& kv)
	{
		_check();
		size_t index = _HashFunc(kv.fist,_tables.size());
		
		Node* cur = _tables[index];  //ÏÈÅÐ¶ÏÊÇ·ñ´æÔÚ
		while (cur)
		{
			if (cur->kv.first == kv.first)
				return false;
			cur = cur->_next;
		}

		Node* tmp = new Node(kv.first);
		tmp->_next = _tables[index];
		_tables[index] = tmp;
		++_size;
		return true;           
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);

	}

protected:
	void Destory()
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			Node* cur = _tables[i];
			while (cur)
			{
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}
			_tables[i] = NULL;
		}
		_size = 0;
	}
	size_t _HashFunc(const K& key,size_t size)
	{
		HashFunc hf;
		return hf(key) % size;
	}

	void _check(); 

protected:
	vector<Node*> _tables;
	size_t _size;
};