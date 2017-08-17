#include"bigData.h"

void TestAdd()
{
	BigData b1("999");
	BigData b2("99");
	cout << b1 + b2 << endl;
}


int main()
{
	TestAdd();
	system("pause");
	return 0;
}