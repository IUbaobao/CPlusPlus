#pragma once 

#include "HashTable.h"
using namespace buckethash;

namespace hdm
{
	template<class K>
	struct KeyofK
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	template<class K>
	class unordered_set
	{
	public:
		typedef typename HashTable<K, K, KeyofK<K>>::const_iterator iterator;
		typedef typename HashTable<K, K, KeyofK<K>>::const_iterator const_iterator;

		std::pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end() 
		{
			return _ht.end();
		}
		const_iterator begin()const
		{
			return _ht.begin();
		}
		const_iterator end()const
		{
			return _ht.end();
		}
	private:
		HashTable<K, K, KeyofK<K>> _ht;
	};

	void test_unordered_set()
	{
		unordered_set<int> us;
		us.insert(13);
		us.insert(3);
		us.insert(23);
		us.insert(5);
		us.insert(5);
		us.insert(6);
		us.insert(15);
		us.insert(223342);
		us.insert(22);
		//for (int i = 0; i < 100; i++)
		//{

		//	us.insert(i);
		//}
		unordered_set<int>::const_iterator it = us.begin();
		while (it != us.end())
		{
			cout << *it << " ";
			++it;
			//(*it)++;
		}
		cout << endl;

		for (auto e : us)
		{
			cout << e << " ";
		}
		cout << endl;
	}

}
