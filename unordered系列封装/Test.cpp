//#include "HashTable.h"
#include <iostream>
#include <unordered_map>
#include "Unordered_set.h"
#include "Unordered_map.h"
using namespace std;
int main()
{
	//buckethash::TestHT2();
	unordered_map<int, int> umap;
	/*string arr[] = { "ƻ��", "����", "�㽶", "��ݮ", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };*/
	//int arr[] = { 3,1,2,3,4,6,7,8,3,4,12,13 };
	//for (auto& e : arr)
	//{
	//	umap[e]++;
	//}
	//for (auto& e : umap)
	//{
	//	cout << e.first << ":" << e.second << endl;
	//}
	hdm::test_unordered_set();
	hdm::test_unordered_map();
	return 0;
}



