#include<iostream>
using namespace std;

//对称矩阵
//0 1 2
//1 0 1          
//2 1 0

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(int* matrix, size_t N)  //将二维数组用一维数组的动态方式进行存储
		:_N(N)
	{
		_matrix = new T[N*(N + 1) / 2];
		size_t index = 0;
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				if (i >= j)
				{
					_matrix[index++] = matrix[i*N + j];   //_matrix中存储的是下三角
				}
				else
					break;
			}
		}
	}

	~SymmetricMatrix()
	{
		delete[] _matrix;
		_matrix = NULL;
		_N = 0;
	}

	const T& Access(size_t i, size_t j) const 
	{
		if (i < j)
			swap(i, j);

		return _matrix[i*(i + 1) / 2 + j];
	}

	void Display()
	{
		for (size_t i = 0; i < _N; i++)
		{
			for (size_t j = 0; j < _N; j++)
			{
				cout << Access(i, j)<<" ";
			}
			cout << endl;
		}
	}

protected:
	T* _matrix;   //压缩存储矩阵
	size_t _N;    //N*N的矩阵
};


//稀疏矩阵
template<class T>
struct Triple
{
	size_t _row;
	size_t _col;
	T _value;

	Triple(size_t row = 0, size_t col = 0, const T& v = T())
		:_row(row)
		, _col(col)
		, _value(v)
	{}
};


template<class T>
class SparseMatrix
{
protected:
	  

};