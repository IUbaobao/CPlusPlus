//#include "HashTable.h"
#include <iostream>
#include <unordered_map>
#include "bitset.h"
#include "BloomFilter.h"
using namespace std;
int main()
{
	//buckethash::TestHT2();
	unordered_map<int, int> umap;
	/*string arr[] = { "Æ»¹û", "Î÷¹Ï", "Ïã½¶", "²ÝÝ®", "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Ïã½¶", "Æ»¹û", "Ïã½¶" };*/
	//int arr[] = { 3,1,2,3,4,6,7,8,3,4,12,13 };
	//for (auto& e : arr)
	//{
	//	umap[e]++;
	//}
	//for (auto& e : umap)
	//{
	//	cout << e.first << ":" << e.second << endl;
	//}
	//test_bitset1();
	//test_twobitset();
	test_bloomfilter1();

	return 0;
}



