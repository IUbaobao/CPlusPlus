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
//	catch (const string&& errmsg)//最近原则
//	{
//		//cout <<"fun():" << errmsg << endl;
//		throw errmsg;//也可以抛给下一层
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
//	catch (...)//...捕获任意类型
//	{
//		cout << "未知错误" << endl;
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
//	// 这里可以看到如果发生除0错误抛出异常，另外下面的array没有得到释放。
//	// 所以这里捕获异常后并不处理异常，异常还是交给外面处理，这里捕获了再
//	// 重新抛出去。
//	int* arr = new int[10];
//	int a, b;
//	cin >> a >> b;
//	try
//	{
//		Division(a, b);
//	}
//	catch (...)//最近原则
//	{
//		delete[] arr;
//		cout << "delete[]" << arr << endl;//
//		throw;//
//	}
//	delete[]arr;//有可能出现异常执行不到这些代码，所以要解决这样的内存泄漏，要在异常
//				//捕捉哪里也写上，当然这样的代码显得很冗余，后续智能指针就登场了
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
//	catch (...)//...捕获任意类型
//	{
//		cout << "未知错误" << endl;
//	}
//	return 0;
//}

#include <thread>
// 服务器开发中通常使用的异常继承体系
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
		throw SqlException("权限不足", 100, "select * from name = '张三'");
		//throw 1;
	}
	//throw "xxxxxx";
}
void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不足", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}
	SQLMgr();
}
void HttpServer()
{
	// ...
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("请求资源不存在", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("权限不足", 101, "post");
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
		catch (const Exception& e) // 这里捕获父类对象就可以
		{
			// 多态
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}
