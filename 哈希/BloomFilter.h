#pragma once 
#include <bitset>
#include <string>
using namespace std;
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
class K=string,
size_t x=5,
class HashFunc1= BKDRHash,
class HashFunc2= APHash,
class HashFunc3= DJBHash>
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

	bool test(const K& key )
	{
		size_t hash1 = HashFunc1()(key) % (N * x);
		size_t hash2 = HashFunc2()(key) % (N * x);
		size_t hash3 = HashFunc3()(key) % (N * x);

		if (_bs.test(hash1) == 0)
			return false;
		if (_bs.test(hash2) == 0)
			return false;
		if (_bs.test(hash3) == 0)
			return false;

		return true;//¿ÉÄÜ´æÔÚÎóÅĞ
	}

private:
	std::bitset<N* x> _bs;
};



void test_bloomfilter1()
{
	string str[] = { "Öí°Ë½ä", "ËïÎò¿Õ", "É³Îò¾»", "ÌÆÈı²Ø", "°×ÁúÂí1","1°×ÁúÂí","°×1ÁúÂí","°×11ÁúÂí","1°×ÁúÂí1" };
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

