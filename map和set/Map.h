#pragma once

#include "RBTree.h"

namespace hdm
{
	template<class K,class V>
	class keyofV
	{
	public:
		const K& operator()(const std::pair<K, V>& kv)
		{
			return kv.first;
		}
	};

	template<class K,class V>
	class map
	{
	public:
		typedef typename hdm::RBTree<K,std::pair<const K, V>, keyofV<K, V>>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}

		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _t.Insert(std::make_pair(key, V()));
			return ret.first->second;
		}
		size_t size()
		{
			return _t.size();
		}

		void clear()
		{
			_t.clear();
		}

		bool empty()
		{
			return _t.empty();
		}

	private:
		hdm::RBTree<K,std::pair<const K, V>, keyofV<K,V>> _t;
	};

	void test_map()
	{
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		map<int, int> m;
		for (auto e : a)
		{
			if(e == 14)
				int i = 14;
			m.insert(std::make_pair(e, e));
		}
		//for (auto& e : m)
		//{
		//	cout << e.first << ":" << e.second << endl;
		//}
		auto it = m.begin();
		while (it != m.end())
		{
			std::cout << it->first << ":" << it->second << std::endl;
			++it;
		}

		it = m.end();
		while (it != m.begin())
		{
			--it;
			std::cout << it->first << ":" << it->second << std::endl;
		}
		cout << "总数" << m.size() << endl;
		cout << "empty:" << m.empty() << endl;
		m.clear();
		cout << "clear().." << endl;
		cout << "empty:" << m.empty() << endl;

		cout << "总数" << m.size() << endl;

	}


	void TestMap()
	{
		//统计水果出现的次数
		std::string arr[] = { "苹果", "西瓜", "香蕉", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
		map<string, int> mapcount;
		for (auto& e : arr)
		{
			mapcount[e]++;
		}

		for (auto& e : mapcount)
		{
			cout << e.first << ":" << e.second << endl;
		}
	}

}//namespace end


