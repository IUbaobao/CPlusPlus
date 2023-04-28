#pragma once 

#include <iostream>
#include <vector>
#include <string>
using namespace std;



template<class K>
class HashFunc//哈希函数
{
public:
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};
template<>//对string类型特化
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

namespace Close_Hash
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
			while (_tables[hashi]._state == EXIST)
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

		size_t size()const 
		{
			return _n;
		}
		bool empty()const
		{
			return _n == 0;
		}


		void swap(HashTable<K, V>& ht)
		{
			_tables.swap(ht._tables);
			swap(_n, ht._n);
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
	template<class T>
	class HashNode
	{
	public:
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data),_next(nullptr)
			{}
	};
	template<class K, class T, class KeyofT, class Hash = HashFunc<K>>
	class HashTable;

	//为什么const迭代器没有复用？---因为在构造的时候，const对象对应的this也是cosnt的，这就导致const迭代器在构造的时候给成const的指针，但是非const的时候，是不需要const指针的，这就注定要不能复用
	//注：非const迭代器---Node* _node,HashTable* _ht;
	//	  const迭代器--- const Node* _node,const HashTable* _ht;
	template<class K,class T,class KeyofT,class Hash=HashFunc<K>>
	class hash_iterator
	{
	public:
		typedef HashNode<T> Node; 
		typedef HashTable<K, T, KeyofT, Hash> HT;
		typedef hash_iterator<K, T, KeyofT, Hash> Self;
		hash_iterator(Node* node,HT* ht)
			:_node(node),_ht(ht)
		{}

		Self operator++()
		{
			Node* cur = _node;
			if (cur->_next)//不是桶的最后一个节点
			{
				cur = cur->_next;
			}
			else//桶的最后一个节点
			{
				//需要重新计算哈希映射的位置
				size_t hashi = Hash()(KeyofT()(cur->_data)) % _ht->_tables.size()+1;
				while(hashi< _ht->_tables.size()
					&&_ht->_tables[hashi]==nullptr)//找当前桶的下一个不为空的桶
				{++hashi;}

				if (hashi <  _ht->_tables.size())
					cur = _ht->_tables[hashi];
				else
					cur = nullptr;
			}
			_node = cur;
			return *this;
		}
		
		T& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& it)const
		{
			return it._node != _node;
		}

		bool operator==(const Self& it)const
		{
			return it._node == _node;
		}
		HT* _ht;
		Node* _node;
	};
	template<class K, class T, class KeyofT, class Hash = HashFunc<K>>
	class hash_const_iterator
	{
	public:
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyofT, Hash> HT;
		typedef hash_const_iterator<K, T, KeyofT, Hash> Self;
		typedef hash_iterator<K, T, KeyofT, Hash> iterator;
		hash_const_iterator(const Node* node,  const HT* ht)
			:_node(node), _ht(ht)
		{}
		hash_const_iterator(const iterator&it)
			:_node(it._node),_ht(it._ht)
		{}
		Self operator++()
		{
			const Node* cur = _node;
			if (cur->_next)//不是桶的最后一个节点
			{
				cur = cur->_next;
			}
			else//桶的最后一个节点
			{
				//需要重新计算哈希映射的位置
				size_t hashi = Hash()(KeyofT()(cur->_data)) % _ht->_tables.size() + 1;
				while (hashi < _ht->_tables.size()
					&& _ht->_tables[hashi] == nullptr)//找当前桶的下一个不为空的桶
				{
					++hashi;
				}

				if (hashi < _ht->_tables.size())
					cur = _ht->_tables[hashi];
				else
					cur = nullptr;
			}
			_node = cur;
			return *this;
		}

		const T& operator*()
		{
			return _node->_data;
		}

		const T* operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& it)const
		{
			return it._node != _node;
		}

		bool operator==(const Self& it)const
		{
			return it._node == _node;
		}

		const HT* _ht;
		const Node* _node;
	};

	template<class K, class T, class KeyofT, class Hash >
	class HashTable
	{
	public:
		typedef HashNode<T> Node;

		typedef hash_iterator<K, T,  KeyofT, Hash> iterator;
		typedef hash_const_iterator<K, T, KeyofT, Hash> const_iterator;

		friend class iterator;
		friend class const_iterator;

		HashTable()
			:_n(0),_tables(__stl_next_prime(10))
		{}

		iterator begin()
		{
			Node* cur = nullptr;
			for (auto e : _tables)
			{
				cur = e;
				if (cur != nullptr)
					break;
			}
			return iterator(cur, this);
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		const_iterator begin()const
		{
			Node* cur = nullptr;
			for (auto e : _tables)
			{
				cur = e;
				if (cur != nullptr)
					break;
			}
			return const_iterator(cur, this);
		}

		const_iterator end()const
		{
			return const_iterator(nullptr, this);
		}

		std::pair<iterator,bool> Insert(const T& data)
		{
			Node* cur = Find(KeyofT()(data));
			if (cur)
				return make_pair(iterator(cur,this),false);
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
				newHT._tables.resize(__stl_next_prime(_tables.size()));
				for (int i=0;i<_tables.size();++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						//重新计算哈希值，直接把节点连过去，减少新建节点的开销
						Node* next = cur->_next;
						size_t hashi = Hash()(KeyofT()(cur->_data)) % newHT._tables.size();
						cur->_next = newHT._tables[hashi];
						newHT._tables[hashi] = cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newHT._tables);
			}

			size_t hashi = Hash()(KeyofT()(data)) % _tables.size();
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return make_pair(iterator(newnode,this),true);
		}

		Node* Find(const K& key)
		{
			size_t hashi = Hash()(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (KeyofT()(cur->_data) == key)
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
				if (Hash()(cur->_data) == key)
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

		bool empty()const 
		{
			return _n == 0;
		}

		size_t size()const 
		{
			return _n;
		}
	private:
		inline unsigned long __stl_next_prime(unsigned long n)
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};

			for (int i = 0; i < __stl_num_primes; ++i)
			{
				if (__stl_prime_list[i] > n)
				{
					return __stl_prime_list[i];
				}
			}

			return __stl_prime_list[__stl_num_primes - 1];
		}
	private:
		vector<Node*> _tables;
		size_t _n;
	};
}



