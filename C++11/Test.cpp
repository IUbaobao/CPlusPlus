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

//#include <thread>
//// 服务器开发中通常使用的异常继承体系
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
//		throw SqlException("权限不足", 100, "select * from name = '张三'");
//		//throw 1;
//	}
//	//throw "xxxxxx";
//}
//void CacheMgr()
//{
//	srand(time(0));
//	if (rand() % 5 == 0)
//	{
//		throw CacheException("权限不足", 100);
//	}
//	else if (rand() % 6 == 0)
//	{
//		throw CacheException("数据不存在", 101);
//	}
//	SQLMgr();
//}
//void HttpServer()
//{
//	// ...
//	srand(time(0));
//	if (rand() % 3 == 0)
//	{
//		throw HttpServerException("请求资源不存在", 100, "get");
//	}
//	else if (rand() % 4 == 0)
//	{
//		throw HttpServerException("权限不足", 101, "post");
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
//		catch (const Exception& e) // 这里捕获父类对象就可以
//		{
//			// 多态
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
// //C++11笔记demo代码
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
//	// C++11支持的列表初始化，这里会调用构造函数初始化
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
//	// 这里{"sort", "排序"}会先初始化构造一个pair对象
//	map<string, string> dict = { {"sort", "排序"}, {"insert", "插入"} };
//	// 使用大括号对容器赋值
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
//	auto p = &i; // 推导为int*类型
//	auto pf = "apple"; //推导为const char* 类型
//	cout << typeid(p).name() << endl;
//	cout << typeid(pf).name() << endl;
//	map<string, string> dict = { {"apple", "苹果"}, {"banana", "香蕉"} };
//	//map<string, string>::iterator it = dict.begin();
//	auto it = dict.begin();
//	return 0;
//}




// decltype的一些使用使用场景
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
//	decltype(x * y) ret; // ret的类型是double
//	decltype(&x) p; // p的类型是int*
//	cout << typeid(ret).name() << endl;
//	cout << typeid(p).name() << endl;
//	F(1, 'a');//int 和 char --》int
//	return 0;
//}



//int main()
//{
//	// 以下的p、b、c、*p都是左值
//	int* p = new int(0);
//	int b = 1;
//	const int c = 2;
//	// 以下几个是对上面左值的左值引用
//	int*& rp = p;
//	int& rb = b;
//	const int& rc = c;
//	int& pvalue = *p;
//	return 0;
//}

//int main()
//{
//	double x = 1.1, y = 2.2;
//	// 以下几个都是常见的右值
//	10;
//	x + y;
//	fmin(x, y);
//	// 以下几个都是对右值的右值引用
//	int&& rr1 = 10;
//	double&& rr2 = x + y;
//	double&& rr3 = fmin(x, y);
//	// 这里编译会报错：error C2106: “=”: 左操作数必须为左值
//	10 = 1;
//	x + y = 1;
//	fmin(x, y) = 1;
//	return 0;
//}

//
//int main()
//{
//	// 左值引用只能引用左值，不能引用右值。
//	int a = 10;
//	int& ra1 = a; // ra为a的别名
//	//int& ra2 = 10; // 编译失败，因为10是右值
//	// const左值引用既可引用左值，也可引用右值。
//	const int& ra3 = 10;
//	const int& ra4 = a;
//	return 0;
//}

int main()
{
	// 右值引用只能右值，不能引用左值。
	int&& r1 = 10;
	// error C2440: “初始化”: 无法从“int”转换为“int &&”
	// message : 无法将左值绑定到右值引用
	int a = 10;
	int&& r2 = a;//报错：“初始化”: 无法从“int”转换为“int &&”
	// 右值引用可以引用move以后的左值
	int&& r3 = std::move(a);
	return 0;
}

