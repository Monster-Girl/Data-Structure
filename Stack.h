#include<iostream>
using namespace std;
#include<stack>
#include<assert.h>
template<class T>


class Stack
{
public:
	void Push(const T& data)
	{
		s1.push(data);
		if (Min.empty() || data <= Min.top())
			Min.push(data);
	}

	void Pop()
	{
		assert(!s1.empty());
		if (Min.top() == s1.top())
		{
			Min.pop();
			s1.pop();
		}
		s1.top();
	}

	T& GetMin()
	{
		return Min.top();
	}

protected:
	stack<T> s1;
	stack<T> Min;
};

void Test()
{
	Stack<int> s;
	s.Push(3);
	s.Push(4);
	s.Push(2);
	s.Push(3);
	s.Push(1);

	cout << s.GetMin() << endl;

	s.Pop();
	s.Pop();
	s.Pop();


}