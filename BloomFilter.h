#include"bit_set.h"

template<class K>
struct _HashFunc1
{
	size_t BKDRHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};

template<class K>
struct _HashFunc2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}

	size_t operator()(const string& key)
	{
		return SDBMHash(key.c_str());
	}
};

template<class K>
struct _HashFunc3
{
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}

	size_t operator()(const string& key)
	{
		return APHash(key.c_str());
	}
};


template<class K = string, class HashFunc1 = _HashFunc1<K>, 
class HashFunc2 = _HashFunc2<K>, class HashFunc3 = _HashFunc3<K>>
class BloomFilter
{
public:
	BloomFilter(size_t n)   //如果要求布隆过滤器只填充一半
		:_bs(3 * n * 2)
		, _range(3 * n * 2)
	{}

	void Set(const K& key)
	{
		size_t hash1 = HashFunc1()(key);
		size_t hash2 = HashFunc2()(key);
		size_t hash3 = HashFunc3()(key);

		_bs.Set(hash1%_range);
		_bs.Set(hash2%_range);
		_bs.Set(hash3%_range);
	}
	 bool Test(const K& key)
	{
		size_t hash1 = HashFunc1()(key);
		if (_bs.Test(hash1%_range) == false)
			return false;

		size_t hash2 = HashFunc2()(key);
		if (_bs.Test(hash2%_range) == false)
			return false;

		size_t hash3 = HashFunc3()(key);
		if (_bs.Test(hash3%_range) == false)
			return false;

		return true;
	}

protected:
	BitSet _bs;
	size_t _range;
};

void TestBloom()
{
	BloomFilter< > bm(100);
	bm.Set("peter");
	bm.Set("hehe");
	bm.Set("lalala");
	cout << bm.Test("peter") << endl;
	cout << bm.Test("hehe") << endl;
	cout << bm.Test("land") << endl;

}