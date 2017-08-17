#pragma once 
#include<iostream>
using namespace std;
#include<string>
typedef long long INT_64;
const INT_64 MAXINT64 = 9223372036854775807;
const INT_64 MININT64 = 9223372036854775807-1;

class BigData
{
public:
	BigData(INT_64 value)
		:_value(value)
	{}

	BigData(const string & strData)
		:_value(0)
		, _strData("+0")
	{
		if (strData == "")
			return;
		const char* data = (char*)strData.c_str();


		while (isspace(*data))   //����ǰ�õĿհ��ַ�
			++data;

		if ('\0' == *data)
			return;

		char symbol = *data;
		if ('+' == *data || '-' == *data)  //�ж�����
			++data;
		else if(isdigit(*data))
			symbol = '+';
		else
			return;

		
		while ('0' == *data)   //�ж�ǰ�ö�0���
			++data;

		if ('\0' == *data)
			return;

		_strData.resize(strlen(data) + 1);  //��Ҫ���Ƿ���
		_strData[0] = symbol;

		size_t i = 1;
		while (isdigit(*data))
		{
			_value = _value * 0 + *data - '0';
			_strData[i++] = *data;
			data++;
		}
		if (symbol == '-')  //_valueȫ�����ģ���Ҫ�������
			_value = 0 - _value;

		_strData.resize(i);  //12345a1234,��Ҫ����_strData�Ĵ�С
}

	BigData operator + (const BigData& big)
	{
		if (!IsINT64OverFlow() && !big.IsINT64OverFlow())
		{
			if (_strData[0]==big._strData[0])
				return BigData(_value + big._value);
			else
			{
				if (('+' == _strData[0] && MAXINT64 - _value >= big._value) ||
					('-' == _strData[0] && MININT64 - _value <= big._value))
					return BigData(_value + big._value);
			}
		}
		
		//�������  1.��һ������ 2.��Ӻ󳬳�
		if (_strData[0] == big._strData[0])
		  return Add(_strData,big._strData); 

	}
private:
	friend ostream& operator <<(ostream& _cout, const BigData& big);
	bool IsINT64OverFlow()const
	{
		string tmp("+9223372036854775807");
		if ('-' == _strData[0])
			tmp = "-9223372036854775808";

		if (_strData.size() < tmp.size())
			return false;
		else if (_strData.size() == tmp.size() && _strData < tmp)
			return false;
		
		return true;		
	}

	string Add(string left, string right)
	{
		int lsize = left.size();
		int rsize = right.size();
		if (lsize < rsize)
		{
			left.swap(right);
			swap(lsize, rsize);
		}

		string strRet;
		strRet.resize(lsize + 1);
		strRet[0] = left[0];
		char step = 0;
		for (int i = lsize - 1, j = rsize - 1; i >= 1; --i, --j)
		{
			char cRet = left[i] - '0'+step;
			if (j >= 1)  //�ж϶̵��Ƿ��Ѿ�������
				cRet = cRet + (right[j] - '0');
			step = 0;
			if (cRet >= 10)
			{
				step = 1;
				cRet -= 10;
			}
			strRet[i + 1] = cRet + '0';
		}
		strRet[1] = step + '0';
		return strRet;
	}
private:
	string _strData;
	INT_64 _value;
};

ostream& operator <<(ostream& _cout, const BigData& big)
{
	const char* data = big._strData.c_str();
	if ('+' == *data)
		++data;
	_cout<<data;
	return _cout;
}