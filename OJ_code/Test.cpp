//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
////93. 复原 IP 地址
//class Solution {
//public:
//    vector<string> result;
//    vector<string> restoreIpAddresses(string s) {
//
//        backtracking(s, 0, 0);
//        return result;
//    }
//
//    void backtracking(string& s, int startIndex, int num)
//    {
//        if (num == 3)
//        {
//            if (ismeet(s, startIndex, s.size() - 1))
//            {
//                result.push_back(s);
//            }
//            return;
//        }
//
//        for (int i = startIndex; i < s.size(); ++i)
//        {
//            if (!ismeet(s, startIndex, i))
//                return;
//            s.insert(i + 1, ".");
//            backtracking(s, i + 2, num + 1);
//            s.erase(i + 1, 1);
//        }
//    }
//
//    bool ismeet(const string& s, int begin, int end)
//    {
//        if (begin > end)
//            return false;
//        if (end-begin+1!=1 && s[begin] == '0')
//            return false;
//        string sub = s.substr(begin, end - begin + 1);
//        if (sub.size() > 3)
//            return false;
//        int n = stoi(sub);
//        if (n < 0 || n>255)
//            return false;
//        return true;
//    }
//};
//
//int main()
//{
//    Solution().restoreIpAddresses("0279245587303");
//	return 0;
//}



//
//90. 子集 II
//给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
//解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
//示例 1：
//输入：nums = [1, 2, 2]
//输出： [[], [1], [1, 2], [1, 2, 2], [2], [2, 2]]
class Solution {
public:
    vector<vector<int>> reslut;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> path;
        vector<bool> used(nums.size(), false);//用来判断是否使用过这个数
        sort(nums.begin(), nums.end());
        backtracking(nums, path, 0, used);
        return reslut;
    }

    void backtracking(vector<int>& nums, vector<int>& path, int starti, vector<bool>& used)
    {
        reslut.push_back(path);
        if (starti >= nums.size())
            return;

        for (int i = starti; i < nums.size(); ++i)
        {
            if (i != 0 && nums[i - 1] == nums[i] && used[i - 1] == false)
                continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, path, i + 1, used);
            used[i] = false;
            path.pop_back();
        }
    }
//};