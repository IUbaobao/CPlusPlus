#include <iostream>
#include <string>
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

#include <thread>
// ������������ͨ��ʹ�õ��쳣�̳���ϵ
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{}
	virtual string what() const
	{
		return _errmsg;
	}
protected:
	string _errmsg;
	int _id;
};
class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{}
	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const string _sql;
};
class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{}
	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};
class HttpServerException : public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		, _type(type)
	{}
	virtual string what() const
	{
		string str = "HttpServerException:";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
private:
	const string _type;
};
void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("Ȩ�޲���", 100, "select * from name = '����'");
		//throw 1;
	}
	//throw "xxxxxx";
}
void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("Ȩ�޲���", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("���ݲ�����", 101);
	}
	SQLMgr();
}
void HttpServer()
{
	// ...
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("������Դ������", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("Ȩ�޲���", 101, "post");
	}
	CacheMgr();
}
int main()
{
	while (1)
	{
		this_thread::sleep_for(chrono::seconds(1));
		try {
			HttpServer();
		}
		catch (const Exception& e) // ���ﲶ�������Ϳ���
		{
			// ��̬
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}
