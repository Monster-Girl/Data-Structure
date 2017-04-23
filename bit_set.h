#include<iostream>
using namespace std;
#include<vector>

class BitSet
{
public:
	BitSet(size_t range)
	{
		//_a.resize(range / 32 + 1);
		_a.resize((range >> 5) + 1,0);
	}

	void Set(const size_t& num)
	{
		size_t index = num >> 5;
		size_t pos = num % 32;

		_a[index] |= (1 << pos);
	}

	void Reset(const size_t& num)
	{
		size_t index = num >> 5;
		size_t pos = num % 32;

		_a[index] &= ~(1 << pos);
	}

	bool Test(const size_t& num)
	{
		size_t index = num >> 5;
		size_t pos = num % 32;
		return _a[index] & (1 << pos);
	}

protected:
	vector<int> _a;
};
#include<bitset>
void TestBitset()
{
	BitSet a(-1);
	a.Set(1);
	a.Set(8);
	a.Set(33);
	cout << a.Test(1) << endl;
	cout << a.Test(8) << endl;
	cout << a.Test(33) << endl;
}