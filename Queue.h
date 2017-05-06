//使用两个栈实现一个队列 
#include<iostream>
using namespace std;
#include<stack>

template<class T>
class Queue
{
public:
	void Push(const T& data)
	{
		if (s1.empty())
			s1.push(data);
		else
		{
			while (!s1.empty())
			{
				size_t index = s1.top();
				s2.push(index);
				s1.pop();
			}

			s1.push(data);
			while (!s2.empty())
			{
				size_t index = s2.top();
				s1.push(index);
				s2.pop();
			}
		}
	}
	void Pop()
	{
		s1.pop();
	}

	T& Front()
	{
		return s1.top();
	}

	size_t Size()
	{
		return s1.size();
		/*size_t count = 0;
		while (!s1.empty())
		{
			size_t index = s1.top();
			s2.push(index);
			count++;
			s1.pop();
		}

		while (!s2.empty())
		{
			size_t index = s2.top();
			s1.push(index);
			s2.pop();
		}
		return count;*/
	}
protected:
	stack<T> s1;
	stack<T> s2;
};

void TestQueue()
{
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	cout << q1.Size() << endl;
	q1.Pop();
	q1.Pop();
	cout << q1.Size() << endl;
	cout << q1.Front() << endl;
}