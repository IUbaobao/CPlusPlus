#pragma once 
#include <bitset>
#include <string>
using namespace std;

namespace hdm
{
	struct BKDRHash
	{
		size_t operator()(const string& s)
		{
			// BKDR
			size_t value = 0;
			for (auto ch : s)
			{
				value *= 31;
				value += ch;
			}
			return value;
		}
	};


	struct APHash
	{
		size_t operator()(const string& s)
		{
			size_t hash = 0;
			for (long i = 0; i < s.size(); i++)
			{
				if ((i & 1) == 0)
				{
					hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
				}
				else
				{
					hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
				}
			}
			return hash;
		}
	};


	struct DJBHash
	{
		size_t operator()(const string& s)
		{
			size_t hash = 5381;
			for (auto ch : s)
			{
				hash += (hash << 5) + ch;
			}
			return hash;
		}
	};


	template<size_t N,
		class K = string,
		size_t x = 5,
		class HashFunc1 = BKDRHash,
		class HashFunc2 = APHash,
		class HashFunc3 = DJBHash>
		class BloomFilter
	{
	public:
		void set(const K& key)
		{
			size_t hash1 = HashFunc1()(key) % (N * x);
			size_t hash2 = HashFunc2()(key) % (N * x);
			size_t hash3 = HashFunc3()(key) % (N * x);

			_bs.set(hash1);
			_bs.set(hash2);
			_bs.set(hash3);
		}

		bool test(const K& key)
		{
			size_t hash1 = HashFunc1()(key) % (N * x);
			if (_bs.test(hash1) == 0)
				return false;

			size_t hash2 = HashFunc2()(key) % (N * x);
			if (_bs.test(hash2) == 0)
				return false;

			size_t hash3 = HashFunc3()(key) % (N * x);
			if (_bs.test(hash3) == 0)
				return false;

			return true;//可能存在误判
		}
		// 不支持删除，删除可能会影响其他值
		void reset(const K& key);
	private:
		std::bitset<N* x> _bs;
	};


	///////////////////////////////////////////////////////////
	//测试
	void test_bloomfilter1()
	{
		string str[] = { "猪八戒", "孙悟空", "沙悟净", "唐三藏", "白龙马1","1白龙马","白1龙马" };
		BloomFilter<10> bf;
		for (auto& str : str)
		{
			bf.set(str);
		}

		for (auto& s : str)
		{
			cout << bf.test(s) << endl;
		}
		cout << endl;

		srand(time(0));
		for (const auto& s : str)
		{
			cout << bf.test(s + to_string(rand())) << endl;
		}
	}

	void test_bloomfilter2()
	{
		srand(time(0));
		const size_t N = 100000;
		BloomFilter<N> bf;

		std::vector<std::string> v1;
		std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";

		for (size_t i = 0; i < N; ++i)
		{
			v1.push_back(url + std::to_string(i));
		}

		for (auto& str : v1)
		{
			bf.set(str);
		}

		// v2跟v1是相似字符串集，但是不一样
		std::vector<std::string> v2;
		for (size_t i = 0; i < N; ++i)
		{
			std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
			url += std::to_string(999999 + i);
			v2.push_back(url);
		}

		size_t n2 = 0;
		for (auto& str : v2)
		{
			if (bf.test(str))
			{
				++n2;
			}
		}
		cout << "相似字符串误判率:" << (double)n2 / (double)N << endl;

		// 不相似字符串集
		std::vector<std::string> v3;
		for (size_t i = 0; i < N; ++i)
		{
			string url = "zhihu.com";
			url += std::to_string(i + rand());
			v3.push_back(url);
		}

		size_t n3 = 0;
		for (auto& str : v3)
		{
			if (bf.test(str))
			{
				++n3;
			}
		}
		cout << "不相似字符串误判率:" << (double)n3 / (double)N << endl;
	}

}//namespace end