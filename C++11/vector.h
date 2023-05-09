#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace hdm
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const  T* const_iterator;

		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}

		T& operator[](size_t pos)
		{
			return *(_start + pos);
		}

		const T& operator[](size_t pos) const
		{
			return *(_start + pos);
		}

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		vector(int n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		//当vector(10,1)的时候，会优先匹配迭代器的那个构造故又写了一个vector(int,const T&val)的构造
		vector(size_t n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}


		vector(std::initializer_list<T>&& il)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			for (const auto& e : il)
			{
				push_back(e);
			}
		}

		template <class InputIteraror>//加模板是为了同时适应const和非const迭代器的构造
		vector(InputIteraror first, InputIteraror last)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		//拷贝构造现代写法
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);
		}


		//赋值重载
		vector<T>& operator=(vector<T> tmp)
		{
			swap(tmp);
			return *this;
		}


		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}

			*_finish = x;
			++_finish;
		}

		void pop_back()
		{
			assert(!empty());
			--_finish;
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(_start <= pos && pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start; //记录pos的相对位置，防止迭代器失效
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
				//更新pos
				pos = _start + len;
			}
			//挪动数据
			iterator end = _finish;
			while (end != pos)
			{
				*end = *(end - 1);
				--end;
			}
			*pos = val;
			++_finish;
			return pos;
		}


		iterator earse(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			iterator begin = pos;
			while (begin + 1 != _finish)
			{
				*begin = *(begin + 1);
				begin++;
			}
			--_finish;

			return pos;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t oldsize = size();
				T* tem = new T[n];
				if (_start)
				{
					for (size_t i = 0; i < oldsize; i++)
					{
						tem[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tem;
				_finish = _start + oldsize;
				_end_of_storage = _start + n;
			}
		}

		void resize(size_t n, const T& x = T())
		{
			if (n >= size())
			{
				if (n > capacity())
				{
					reserve(n);
				}
				size_t oldsize = size();
				for (size_t i = 0; i < n - oldsize; i++)
				{
					push_back(x);
				}

			}
			_finish = _start + n;
		}

		bool empty() const
		{
			return _finish == _start;
		}
		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}


		void swap(vector<T>& tem)
		{
			std::swap(_start, tem._start);
			std::swap(_finish, tem._finish);
			std::swap(_end_of_storage, tem._end_of_storage);
		}

		void clear()
		{
			_start = _finish;
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;

	};


	void test_vector1()
	{
		vector<int> v={ 1,2,3,4 ,2,3,4,5};
		auto il= { 1, 2, 3, 4, 2, 3, 4, 5};
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;

		for (auto e : il)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}