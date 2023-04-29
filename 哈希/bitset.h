#pragma once 

#include <vector>
using namespace std;

template<size_t N>
class bitset
{
public:
	bitset()
		:_bit((N >> 3)+1,0)
	{}
	// ��x��Ӧ����λ��1
	void set(size_t x)
	{
		size_t index = x / 8;
		size_t pos = x % 8;
		_bit[index] |= (1 << pos);
	}

	//��x��Ӧ����λ��0
	void reset(size_t x)
	{
		size_t index = x / 8;
		size_t pos = x % 8;
		_bit[index] &= ~(1 << pos);
	}

	//// ���λͼ��x�Ƿ�Ϊ1
	bool test(size_t x)
	{
		size_t index = x / 8;
		size_t pos = x % 8;
		return _bit[index] & (1 << pos);
	}

private:
	vector<char> _bit;
};


void test_bitset1()
{
	int arr[] = { 12,18,10,100,200,56,45,45,45,12 };
	bitset<2000> bs;
	//for (auto e : arr)
	//{
	//	bs.set(e);
	//}
	//cout << bs.test(12) << endl;
	//cout << bs.test(45) << endl;
	//cout << bs.test(1) << endl;


	for (int i = 0; i < 1990; ++i)
	{
		bs.set(i);
	}
	for (int i = 0; i < 1999; ++i)
	{
		cout << bs.test(i) << " ";
	}
	cout << endl;
	
}



template<size_t N>
class two_bitset//ͳ�Ƴ������μ�����
{
public:
	void set(size_t x)
	{
		bool b1 = _bit1.test(x), b2 = _bit2.test(x);
		//����bitset������00
		//_bit1����λ��_bit2����λ
		if (b1 == 0 && b2 == 0)//һ��û�г��ֹ�
		{
			//01
			_bit2.set(x);
		}
		else if (b1 == 0 && b2 == 1)//�Ѿ����ֹ�һ��
		{
			//10
			_bit1.set(x);
			_bit2.reset(x);
		}
		else
		{
			//
		}
	}


	void PrintTwo()
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (_bit1.test(i) && !_bit2.test(i))
			{
				cout << i << endl;
			}
		}
	}
private:
	bitset<N> _bit1;
	bitset<N> _bit2;
};


void test_twobitset()
{
	int arr[] = { 12,18,10,100,200,56,45,45,45,12 ,18,100};
	two_bitset<200> bs;
	for (auto e : arr)
	{
		bs.set(e);
	}
	bs.PrintTwo();
}

