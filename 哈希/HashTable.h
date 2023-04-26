#pragma once 

#include <iostream>
#include <vector>

using namespace std;

namespace hdm
{
	enum State
	{
		EMPTY,
		DELETE,
		EXIST,
	};
	template<class K,class V>
	class HashData
	{
	public:
		pair<K, V> _kv;
		State _state = EMPTY;
	};

	template<class K,class V>
	class HashTable
	{
	public:
		typedef HashData<K, V> Data;
		HashTable():_n(0),_tables(10){}


		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;
			if (_n * 10 / _tables.size() >= 7)
			{
				//¿©»›
				HashTable<K, V> newTable;
				newTable._tables.resize(_tables.size() * 2);
				for (auto e : _tables)
				{
					if (e._state == EXIST)
					{
						newTable.Insert(e._kv);
					}
				}
				_tables.swap(newTable._tables);
			}

			size_t hashi = kv.first % _tables.size();
			while (_tables[hashi]._state != EMPTY)
			{
				//œﬂ–‘ÃΩ≤‚
				++hashi;
				hashi %= _tables.size();
			}
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_n;
			return true;
		}

		Data* Find(const K&key)
		{
			size_t hashi = key % _tables.size();
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST
					&& _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}
				++hashi;
				hashi %= _tables.size();
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			size_t hashi = key % _tables.size();
			while (_tables[hashi]._state == EXIST)
			{
				if (_tables[hashi]._kv.first == key)
				{
					_tables[hashi]._state = DELETE;
					return true;
				}
				++hashi;
				hashi %= _tables.size();
			}
			return false;
		}

	private:
		vector<Data> _tables;
		size_t _n;
	};
		

	void TestHT1()
	{
		HashTable<int, int> ht;
		int a[] = { 18, 8, 7, 27, 57, 3, 38, 18 };
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Insert(make_pair(17, 17));
		ht.Insert(make_pair(5, 5));

		cout << ht.Find(7) << endl;
		cout << ht.Find(8) << endl;

		ht.Erase(7);
		cout << ht.Find(7) << endl;
		cout << ht.Find(8) << endl;
	}
}




