#pragma once 

#include <iostream>
#include <mutex>
using namespace std;


namespace hdm
{
	template<class T>
	class auto_ptr
	{
	public:
		//RAII
		//保存资源
		auto_ptr(T*ptr):_ptr(ptr){}

		//释放资源
		~auto_ptr()
		{
			delete _ptr;
			cout << _ptr << endl;
		}

		auto_ptr(auto_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			sp._ptr = nullptr;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
		T& operator[](size_t pos)
		{
			return _ptr[pos];
		}
	private:
		T* _ptr;
	};




	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr):_ptr(ptr){}

		~unique_ptr()
		{
			delete _ptr;
			cout << _ptr << endl;
		}

		unique_ptr(const unique_ptr<T>& sp) = delete;
		unique_ptr<T>& operator=(unique_ptr<T>& sp) = delete;
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T& operator[](size_t pos)
		{
			return _ptr[pos];
		}
	private:
		T* _ptr;
	};



	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr):_ptr(ptr),_pcount(new int(1)),_lock(new mutex)
		{}

		~shared_ptr()
		{
			Release();
		}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr),_pcount(sp._pcount),_lock(sp._lock)
		{
			_lock->lock();
			++(*_pcount);
			_lock->unlock();
		}

		void Release()
		{
			_lock->lock();
			if (--(*_pcount) == 0)
			{
				delete _ptr;
				delete _pcount;
			}
			_lock->unlock();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr!=sp._ptr)
			{
				Release();
				_ptr = sp._ptr;
				_pcount = sp._pcount; 
				_lock = sp._lock;
				_lock->lock();
				++(*_pcount);
				_lock->unlock();
			}
			return *this;
		}


		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T& operator[](size_t pos)
		{
			return _ptr[pos];
		}
		
		int use_count()
		{
			return *_pcount;
		}
	private:
		T* _ptr;
		int* _pcount;
		mutex* _lock;
	};

	int test()
	{
		//hdm::auto_ptr<int> ap1(new int);
		//hdm::auto_ptr<int> ap2(ap1);
		//cout << *ap2 << endl;
		////cout << *ap1 << endl;

		//hdm::unique_ptr<int> up1(new int(0));
		//hdm::unique_ptr<int> up2(new int(1));
		///*up2 = up1;*/
		//cout << *up1 << endl;
		//cout << *up2 << endl;

		//hdm::shared_ptr<int> sp1(new int(0));
		//hdm::shared_ptr<int> sp2(sp1);
		//hdm::shared_ptr<int> sp3(new int(10));
		//hdm::shared_ptr<int> sp4(sp3);
		//cout << *sp3 << endl;
		//sp3 = sp2;
		//cout << *sp3 << endl;
		//cout << *sp1 << endl;
		//cout << *sp2 << endl;


		hdm::shared_ptr<int> sp1(new int(0));
		int n = 100000;
		thread t1([&]()
			{
				for (int i = 0; i < n; ++i)
				{
					hdm::shared_ptr<int> sp2(sp1);
				}
			});

		thread t2([&]()
			{
				for (int i = 0; i < n; ++i)
				{
					hdm::shared_ptr<int> sp3(sp1);
				}
			});


		t1.join();
		t2.join();

		cout << sp1.use_count() << endl;

		return 0;
	}
}