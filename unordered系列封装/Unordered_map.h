#pragma once 

#include "HashTable.h"
using namespace buckethash;
namespace hdm
{
	template<class K,class V>
	struct KeyofT
	{
		const K& operator()(const std::pair<K, V>& kv)
		{
			return kv.first;
		}
	};
	template<class K,class V>
	class unordered_map
	{
	public:
		typedef typename HashTable<K, std::pair<const K, V>, KeyofT<K, V> >::iterator iterator;
		typedef typename HashTable<K, std::pair<const K, V>, KeyofT<K, V> >::const_iterator const_iterator;

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

		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		V& operator[](const K&key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		HashTable<K, std::pair<const K, V>, KeyofT<K,V> > _ht;
	};

	void Func(const unordered_map<string, int>& countMap)
	{
		for (const auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
	}
	void test_unordered_map()
	{
		string arr[] = { "Æ»¹û", "Î÷¹Ï", "Ïã½¶", "²ÝÝ®", "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Ïã½¶", "Æ»¹û", "Ïã½¶" };

		unordered_map<string, int> countMap;
		for (auto& e : arr)
		{
			countMap[e]++;
		}
		unordered_map<string, int>::const_iterator it= countMap.begin();
		//it->second++;
		for (const auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
		cout << endl;
		Func(countMap);
	}
}
