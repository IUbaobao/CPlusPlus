#pragma once

#include "RBTree.h"
#include <iostream>
using namespace std;
namespace hdm
{

	template<class K>
	class KeyofK
	{
	public:
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	template<class K>
	class set
	{
	public:
		typedef typename hdm::RBTree<K,K,KeyofK<K>>::const_iterator iterator;
		typedef typename hdm::RBTree<K, K, KeyofK<K>>::const_iterator const_iterator;

		std::pair<iterator,bool> insert(const K& key)
		{
			return _t.Insert(key);
		}

		iterator begin()const
		{
			return _t.begin();
		}
		iterator end()const
		{
			return _t.end();
		}
		bool empty()
		{
			return _t.empty();
		}
		size_t size()
		{
			return _t.size();
		}
	private:
		hdm::RBTree<K, K, KeyofK<K>> _t;
	};


	void test_set()
	{
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		set<int> s;
		for (auto e : a)
		{
			s.insert(e);
		}

		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			//(*it)++;
			//++(*it);
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}