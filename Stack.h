#include<iostream>
using namespace std;
#include<stack>
#include<assert.h>

//ʵ��һ��ջ��Ҫ��ʵ��Push����ջ����Pop����ջ����Min��������Сֵ�Ĳ����� ��ʱ�临�Ӷ�ΪO(1) 
//template<class T>
//class Stack
//{
//public:
//	void Push(const T& data)
//	{
//		s1.push(data);
//		if (Min.empty() || data <= Min.top())
//			Min.push(data);
//	}
//
//	void Pop()
//	{
//		assert(!s1.empty());
//		if (Min.top() == s1.top())
//		{
//			Min.pop();
//			s1.pop();
//		}
//		s1.top();
//	}
//
//	T& GetMin()
//	{
//		return Min.top();
//	}
//
//protected:
//	stack<T> s1;
//	stack<T> Min;
//};
//
//void Test()
//{
//	Stack<int> s;
//	s.Push(3);
//	s.Push(4);
//	s.Push(2);
//	s.Push(3);
//	s.Push(1);
//
//	cout << s.GetMin() << endl;
//
//	s.Pop();
//	s.Pop();
//	s.Pop();
//}

//ʹ����������ʵ��һ��ջ 
//#include<iostream>
//using namespace std;
//#include<queue>
//
//template<class T>
//class Stack
//{
//public:
//	void Push(const T& data)
//	{
//		q1.push(data);
//	}
//
//	void Pop()
//	{
//		size_t index = q1.size() - 1;
//		while (index --)
//		{
//			size_t cur = q1.front();
//			q2.push(cur);
//			q1.pop();
//		}
//		q1.pop();
//		index = q2.size();
//		while (index--)
//		{
//			size_t cur = q2.front();
//			q1.push(cur);
//			q2.pop();
//		}
//	}
//
//	T& Top()
//	{
//		return q1.back();
//	}
//
//	size_t Size()
//	{
//		return q1.size();
//	}
//
//protected:
//	queue<T> q1;
//	queue<T> q2;
//};
//
//void TestStack()
//{
//	Stack<int> s;
//	s.Push(1);
//	s.Push(2);
//	s.Push(3);
//	s.Push(4);
//	s.Push(5);
//	cout << s.Size() << endl;
//	s.Pop();
//	s.Pop();
//	cout << s.Size() << endl;
//}



