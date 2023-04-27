#pragma once 

#include <iostream>
#include <vector>
#include <string>
using namespace std;



template<class K>
class HashFunc
{
public:
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};
template<>
class HashFunc<string>
{
public:
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto e : str)
		{
			hash *= 131;
			hash += e;
		}
		return hash;
	}
};

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



	template<class K,class V,class Hash=HashFunc<K>>
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
				//扩容
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

			size_t hashi = Hash()(kv.first) % _tables.size();
			while (_tables[hashi]._state != EMPTY)
			{
				//线性探测
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
			size_t hashi = Hash()(key) % _tables.size();
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
			size_t hashi = Hash()(key) % _tables.size();
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

	void TestHT2()
	{
		string arr[] = { "苹果", "西瓜", "香蕉", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

		//HashTable<string, int, HashFuncString> countHT;
		HashTable<string, int> countHT;
		for (auto& e : arr)
		{
			HashData<string, int>* ret = countHT.Find(e);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				countHT.Insert(make_pair(e, 1));
			}
		}

		HashFunc<string> hf;
		cout << hf("abc") << endl;
		cout << hf("bac") << endl;
		cout << hf("cba") << endl;
		cout << hf("aad") << endl;
	}
}


namespace buckethash
{
	template<class K,class V>
	class HashNode
	{
	public:
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K,V>& kv)
			:_kv(kv),_next(nullptr)
			{}
	};

	template<class K,class V,class Hash=HashFunc<K> >
	class HashTable
	{
	public:
		typedef HashNode<K, V> Node;
		HashTable()
			:_n(0),_tables(10)
		{}


		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;
			if (_tables.size() ==_n)
			{
				//扩容
				//传统方式---有新建节点的开销
				//HashTable newHT;
				//newHT._tables.resize(_tables.size() * 2);
				//for (auto e : _tables)
				//{
				//	Node* cur = e;
				//	while (cur)
				//	{
				//		newHT.Insert(cur->_kv);
				//		cur = cur->_next;
				//	}
				//}
				//_tables.swap(newHT._tables);

				HashTable newHT;
				newHT._tables.resize(_tables.size() * 2);
				for (int i=0;i<_tables.size();++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						//重新计算哈希值，直接把节点连过去，减少新建节点的开销
						Node* next = cur->_next;
						size_t hashi = Hash()(cur->_kv.first) % newHT._tables.size();
						cur->_next = newHT._tables[hashi];
						newHT._tables[hashi] = cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newHT._tables);
			}

			size_t hashi = Hash()(kv.first) % _tables.size();
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return true;
		}

		Node* Find(const K& key)
		{
			size_t hashi = Hash()(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
					return cur;
				cur = cur->_next;
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			size_t hashi = Hash()(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = nullptr;
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
						_tables[hashi] = cur->_next;
					else
						prev->_next = cur->_next;
					delete cur;
					--_n;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n;
	};
	void TestHT1()
	{
		HashTable<int, int> ht;
		int a[] = { 18, 8, 7, 27, 57, 3, 38, 18,17,88,38,28 };
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}
		ht.Insert(make_pair(1, 1));
		ht.Insert(make_pair(11,11));
		ht.Insert(make_pair(5, 5));

		ht.Erase(17);
		ht.Erase(57);
	}

	void TestHT2()
	{
		string arr[] = { "苹果", "西瓜", "香蕉", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

		HashTable<string, int> countHT;
		for (const auto& e : arr)
		{
			auto it = countHT.Find(e);
			if (it)
			{
				it->_kv.second++;
			}
			else
			{
				countHT.Insert(make_pair(e, 1));
			}
		}
	}

}



