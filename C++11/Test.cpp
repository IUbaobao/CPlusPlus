#include <iostream>
#include <string>
#include <map>
using namespace std;

//double Division(int a, int b)
//{
//	if (b == 0)
//	{
//		//throw "Division by zero condition!";
//		string s("Division by zero condition!");
//		throw s;
//	}
//	else
//	{
//		return (double)a / b;
//	}
//}
//void func()
//{
//	int a, b;
//	cin >> a >> b;
//	try
//	{
//		Division(a, b);
//	}
//	catch (const string&& errmsg)//���ԭ��
//	{
//		//cout <<"fun():" << errmsg << endl;
//		throw errmsg;//Ҳ�����׸���һ��
//	}
//}
//
//int main()
//{
//	try
//	{
//		func();
//	}
//	catch (const string&& errmsg)
//	{
//		cout <<"main():" << errmsg << endl;
//	}
//	catch (...)//...������������
//	{
//		cout << "δ֪����" << endl;
//	}
//	return 0;
//}


//
//double Division(int a, int b)
//{
//	if (b == 0)
//	{
//		//throw "Division by zero condition!";
//		string s("Division by zero condition!");
//		throw s;
//	}
//	else
//	{
//		return (double)a / b;
//	}
//}
//void func()
//{
//	// ������Կ������������0�����׳��쳣�����������arrayû�еõ��ͷš�
//	// �������ﲶ���쳣�󲢲������쳣���쳣���ǽ������洦�����ﲶ������
//	// �����׳�ȥ��
//	int* arr = new int[10];
//	int a, b;
//	cin >> a >> b;
//	try
//	{
//		Division(a, b);
//	}
//	catch (...)//���ԭ��
//	{
//		delete[] arr;
//		cout << "delete[]" << arr << endl;//
//		throw;//
//	}
//	delete[]arr;//�п��ܳ����쳣ִ�в�����Щ���룬����Ҫ����������ڴ�й©��Ҫ���쳣
//				//��׽����Ҳд�ϣ���Ȼ�����Ĵ����Եú����࣬��������ָ��͵ǳ���
//	cout << "delete[]" << arr << endl;
//}
//
//int main()
//{
//	try
//	{
//		func();
//	}
//	catch (const string&& errmsg)
//	{
//		cout << "main():" << errmsg << endl;
//	}
//	catch (...)//...������������
//	{
//		cout << "δ֪����" << endl;
//	}
//	return 0;
//}

//#include <thread>
//// ������������ͨ��ʹ�õ��쳣�̳���ϵ
//class Exception
//{
//public:
//	Exception(const string& errmsg, int id)
//		:_errmsg(errmsg)
//		, _id(id)
//	{}
//	virtual string what() const
//	{
//		return _errmsg;
//	}
//protected:
//	string _errmsg;
//	int _id;
//};
//class SqlException : public Exception
//{
//public:
//	SqlException(const string& errmsg, int id, const string& sql)
//		:Exception(errmsg, id)
//		, _sql(sql)
//	{}
//	virtual string what() const
//	{
//		string str = "SqlException:";
//		str += _errmsg;
//		str += "->";
//		str += _sql;
//		return str;
//	}
//private:
//	const string _sql;
//};
//class CacheException : public Exception
//{
//public:
//	CacheException(const string& errmsg, int id)
//		:Exception(errmsg, id)
//	{}
//	virtual string what() const
//	{
//		string str = "CacheException:";
//		str += _errmsg;
//		return str;
//	}
//};
//class HttpServerException : public Exception
//{
//public:
//	HttpServerException(const string& errmsg, int id, const string& type)
//		:Exception(errmsg, id)
//		, _type(type)
//	{}
//	virtual string what() const
//	{
//		string str = "HttpServerException:";
//		str += _type;
//		str += ":";
//		str += _errmsg;
//		return str;
//	}
//private:
//	const string _type;
//};
//void SQLMgr()
//{
//	srand(time(0));
//	if (rand() % 7 == 0)
//	{
//		throw SqlException("Ȩ�޲���", 100, "select * from name = '����'");
//		//throw 1;
//	}
//	//throw "xxxxxx";
//}
//void CacheMgr()
//{
//	srand(time(0));
//	if (rand() % 5 == 0)
//	{
//		throw CacheException("Ȩ�޲���", 100);
//	}
//	else if (rand() % 6 == 0)
//	{
//		throw CacheException("���ݲ�����", 101);
//	}
//	SQLMgr();
//}
//void HttpServer()
//{
//	// ...
//	srand(time(0));
//	if (rand() % 3 == 0)
//	{
//		throw HttpServerException("������Դ������", 100, "get");
//	}
//	else if (rand() % 4 == 0)
//	{
//		throw HttpServerException("Ȩ�޲���", 101, "post");
//	}
//	CacheMgr();
//}
//int main()
//{
//	while (1)
//	{
//		this_thread::sleep_for(chrono::seconds(1));
//		try {
//			HttpServer();
//		}
//		catch (const Exception& e) // ���ﲶ�������Ϳ���
//		{
//			// ��̬
//			cout << e.what() << endl;
//		}
//		catch (...)
//		{
//			cout << "Unkown Exception" << endl;
//		}
//	}
//	return 0;
//}


//#include "RBTree.h"
//
//int main()
//{
//	hdm::RBTreeTest2();
//	return 0;
//}


/////////////////////////////////////////////////////////
// //C++11�ʼ�demo����
//
//
//class Date
//{
//public:
//	Date(int year, int month, int day)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{
//		cout << "Date(int year, int month, int day)" << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1(2022, 1, 1);
//	// C++11֧�ֵ��б��ʼ�����������ù��캯����ʼ��
//	Date d2{ 2022, 1, 2 };
//	Date d3 = { 2022, 1, 3 };
//	return 0;
//}

//int main()
//{
//	auto il = { 1,3,2,5 };
//	cout << typeid(il).name() << endl;//class std::initializer_list<int>
//	return 0;
//}

//int main()
//{
//	vector<int> v = { 1,2,3,4 };
//	list<int> lt = { 1,2 };
//	// ����{"sort", "����"}���ȳ�ʼ������һ��pair����
//	map<string, string> dict = { {"sort", "����"}, {"insert", "����"} };
//	// ʹ�ô����Ŷ�������ֵ
//	v = { 10, 20, 30 };
//	return 0;
//}
#include "vector.h"
//int main()
//{
//	hdm::test_vector1();
//	return 0;
//}


//int main()
//{
//	int i = 10;
//	auto p = &i; // �Ƶ�Ϊint*����
//	auto pf = "apple"; //�Ƶ�Ϊconst char* ����
//	cout << typeid(p).name() << endl;
//	cout << typeid(pf).name() << endl;
//	map<string, string> dict = { {"apple", "ƻ��"}, {"banana", "�㽶"} };
//	//map<string, string>::iterator it = dict.begin();
//	auto it = dict.begin();
//	return 0;
//}




// decltype��һЩʹ��ʹ�ó���
//template<class T1, class T2>
//void F(T1 t1, T2 t2)
//{
//	decltype(t1 * t2) ret;
//	cout << typeid(ret).name() << endl;
//}
//int main()
//{
//	const int x = 1;
//	double y = 2.2;
//	decltype(x * y) ret; // ret��������double
//	decltype(&x) p; // p��������int*
//	cout << typeid(ret).name() << endl;
//	cout << typeid(p).name() << endl;
//	F(1, 'a');//int �� char --��int
//	return 0;
//}



//int main()
//{
//	// ���µ�p��b��c��*p������ֵ
//	int* p = new int(0);
//	int b = 1;
//	const int c = 2;
//	// ���¼����Ƕ�������ֵ����ֵ����
//	int*& rp = p;
//	int& rb = b;
//	const int& rc = c;
//	int& pvalue = *p;
//	return 0;
//}

//int main()
//{
//	double x = 1.1, y = 2.2;
//	// ���¼������ǳ�������ֵ
//	10;
//	x + y;
//	fmin(x, y);
//	// ���¼������Ƕ���ֵ����ֵ����
//	int&& rr1 = 10;
//	double&& rr2 = x + y;
//	double&& rr3 = fmin(x, y);
//	// �������ᱨ��error C2106: ��=��: �����������Ϊ��ֵ
//	10 = 1;
//	x + y = 1;
//	fmin(x, y) = 1;
//	return 0;
//}

//
//int main()
//{
//	// ��ֵ����ֻ��������ֵ������������ֵ��
//	int a = 10;
//	int& ra1 = a; // raΪa�ı���
//	//int& ra2 = 10; // ����ʧ�ܣ���Ϊ10����ֵ
//	// const��ֵ���üȿ�������ֵ��Ҳ��������ֵ��
//	const int& ra3 = 10;
//	const int& ra4 = a;
//	return 0;
//}

int main()
{
	// ��ֵ����ֻ����ֵ������������ֵ��
	int&& r1 = 10;
	// error C2440: ����ʼ����: �޷��ӡ�int��ת��Ϊ��int &&��
	// message : �޷�����ֵ�󶨵���ֵ����
	int a = 10;
	int&& r2 = a;//��������ʼ����: �޷��ӡ�int��ת��Ϊ��int &&��
	// ��ֵ���ÿ�������move�Ժ����ֵ
	int&& r3 = std::move(a);
	return 0;
}

