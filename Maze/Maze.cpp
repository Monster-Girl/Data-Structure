#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<fstream>
#include<assert.h>
#include<stack>
using namespace std;

#define N 10
struct Pos
{
	Pos(const int& row = 0, const int& col = 0)
	:_row(row)
	, _col(col)
	{}

	int _row;  //行
	int _col;  //列
};

void InitMazeMap(int maze[][N],size_t n)   //1.首先从文件中读出一个迷宫的地图
{
	FILE* fout = fopen("MazeMap.txt", "r");
	assert(fout);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; )
		{
			char ch = fgetc(fout);
			if (ch == '0' || ch == '1')
			{
				maze[i][j] = ch - '0';
				++j;
			}
		}
	}
}

void Print(int maze[][N])    //2.打印出地图
{
	for (size_t i = 0; i < N;i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool CheckAccess(int maze[][N], Pos pos)  //3.判断出口
{
	if ((pos._col < N && pos._row >= 0) && (pos._row < N && pos._col >= 0))
	{
		if (maze[pos._row][pos._col] == 0)
			return true;
	}
	return false;
}

bool GetPath(int maze[][N], stack<Pos>& path, Pos entry)  //4.开始在迷宫寻找出口
{
	Pos cur = entry;
	Pos next;
	path.push(cur);
	while (!path.empty())
	{
		if ((cur._row != entry._row && cur._col != entry._col) &&     //入口！=出口
			((cur._row == 0) || (cur._col == 0) || (cur._col == N - 1) || (cur._row == N - 1)))   //只能从四个边界出来

		{
			maze[cur._row][cur._col] = 2;
			return true;
		}

		maze[cur._row][cur._col] = 2;

		//向右走
		next = cur;
		++next._col;
		if (CheckAccess(maze, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}

		//向左走
		next = cur;
		--next._col;
		if (CheckAccess(maze, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}

		//向上走
		next = cur;
		--next._row;
		if (CheckAccess(maze, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}

		//向下走
		next = cur;
		++next._row;
		if (CheckAccess(maze, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}

		cur = path.top();
		path.pop();
	}
	return false;
}


void Test()
{
	int maze[N][N] = { 0 };
	stack<Pos> path;
	InitMazeMap(maze,10);
	Print(maze);
	GetPath(maze, path, Pos(2, 0));
	Print(maze);
}

int main()
{
	Test();
	system("pause");
	return 0;
}