#include<iostream>
using namespace std;
#include<vector>
#include<string>

enum state
{
	EMPTY,
	EXIST,
	DELETE,
};

template<class K, class V>
struct HashNode
{
	pair<K, V> _kv;
	state _s;
};

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

template<class K, class V,class HashFunc=_HashFunc<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable()
		:_size(0)
	{}

	HashTable(size_t n)
		:_size(0)
	{
		_tables.resize(n);
	}

	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		_check();
		size_t index = _HashFunc(kv.first);
		while (_tables[index]._s == EXIST)
		{
			if (_tables[index]._kv.first == kv.first)
				return make_pair(&_tables[index], false);

			index += 1;
			if (index == _tables.size())
				index = 0;
		}

		_tables[index]._kv = kv;
		_tables[index]._s = EXIST;
		++_size;
		return make_pair(&_tables[index], true);
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);
		while (_tables[index]._s != EMPTY)
		{
			if (_tables[index]._kv.first == key && _tables[index]._s!=DELETE)
				return &_tables[index];
			index += 1;
			if (index == _tables.size())
				index = 0;
			return NULL;
		}
	}

	bool Remove(const K& key)
	{
		Node* cur = Find(key);
		if (cur)
		{
			cur->_s = DELETE;
			--_size;
			return true;
		}
		else
			return false;
	}

	V& operator[](const K& key)
	{
		pair<Node*, bool> node = Insert(make_pair(key, V()));
		return (node.first->_kv).second;
	}


protected:

	size_t _HashFunc(const K& key)
	{
		HashFunc hf;
		return hf(key) % _tables.size();
	}

	void _check()
	{
		if (_tables.size() == 0)
		{
			_tables.resize(GetNextPrime(0));
		}

		else if (_size * 10 / _tables.size() == 7)    //负载因子大于7就需要考虑增容
		{
			size_t newSize = GetNextPrime(_tables.size());
			HashTable<K, V,HashFunc> newHT(newSize);
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i]._s == EXIST)
					newHT.Insert(_tables[i]._kv);
			}
			Swap(newHT);
		}
	}

	void Swap(HashTable<K, V,HashFunc>& ht)
	{
		swap(_size, ht._size);
		_tables.swap(ht._tables);
	}


	size_t GetNextPrime(size_t num)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{ 53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
		};

		for (size_t i = 0; i < _PrimeSize; i++)
		{
			if (_PrimeList[i]>num)
				return _PrimeList[i];
		}
		return _PrimeList[_PrimeSize - 1];
	}

protected:
	vector<Node> _tables;
	size_t _size;
};


void TestHashTables()
{
	HashTable<int,int> ht;
	int a[] = { 89, 18, 49, 58, 9 };

	for(size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		 ht.Insert(make_pair(a[i], i));
	}

	ht.Insert(make_pair(3, 1));
	ht.Insert(make_pair(43, 1));
	ht.Insert(make_pair(24, 1));
	ht.Insert(make_pair(109, 1));
	ht.Insert(make_pair(26, 1));
	ht.Insert(make_pair(8, 1));

	cout << ht.Find(58) << endl;
	cout << ht.Find(1) << endl;

	cout << ht.Remove(58) << endl;
	cout << ht.Find(58) << endl;
	cout << ht.Remove(58) << endl;

	HashTable<string, string> dict;
	dict["left"] = "左边";
	dict["left"] = "剩余";
}