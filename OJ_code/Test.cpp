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
//class Solution {
//public:
//    vector<vector<int>> reslut;
//    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
//        vector<int> path;
//        vector<bool> used(nums.size(), false);//用来判断是否使用过这个数
//        sort(nums.begin(), nums.end());
//        backtracking(nums, path, 0, used);
//        return reslut;
//    }
//
//    void backtracking(vector<int>& nums, vector<int>& path, int starti, vector<bool>& used)
//    {
//        reslut.push_back(path);
//        if (starti >= nums.size())
//            return;
//
//        for (int i = starti; i < nums.size(); ++i)
//        {
//            if (i != 0 && nums[i - 1] == nums[i] && used[i - 1] == false)
//                continue;
//            path.push_back(nums[i]);
//            used[i] = true;
//            backtracking(nums, path, i + 1, used);
//            used[i] = false;
//            path.pop_back();
//        }
//    }
////};



//491. 递增子序列
//给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中 至少有两个元素 。你可以按 任意顺序 返回答案。
//数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。
//示例 1：
//输入：nums = [4, 6, 7, 7]
//输出： [[4, 6], [4, 6, 7], [4, 6, 7, 7], [4, 7], [4, 7, 7], [6, 7], [6, 7, 7], [7, 7]]
//
//class Solution {
//public:
//    vector<vector<int>> reslut;
//    vector<int> path;
//    vector<vector<int>> findSubsequences(vector<int>& nums) {
//        backtracking(nums, 0);
//        return reslut;
//    }
//
//    void backtracking(vector<int>& nums, int stari)
//    {
//        if (path.size() > 1)
//        {
//            reslut.push_back(path);
//        }
//        unordered_set<int> s;//本层去重
//        for (int i = stari; i < nums.size(); ++i)
//        {
//            if ((path.size() > 0 && nums[i] < path.back()) || s.find(nums[i]) != s.end())
//                continue;
//            s.insert(nums[i]);
//            path.push_back(nums[i]);
//            backtracking(nums, i + 1);
//            path.pop_back();
//        }
//    }
//};


//46. 全排列
//给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
//
//示例 1：
//输入：nums = [1, 2, 3]
//输出： [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]


class Solution {
public:
    vector<vector<int>> reslut;
    vector<int> path;
    vector<vector<int>> permute(vector<int>& nums) {

        vector<bool> used(nums.size(), false);//记录已经使用过的数
        backtracking(nums, used);
        return reslut;
    }

    void backtracking(const vector<int>& nums, vector<bool>& used)
    {
        if (path.size() == nums.size())
        {
            reslut.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if (used[i] == true)//过滤已经选过的数
                continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
};


//47. 全排列 II
//给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
//
//示例 1：
//输入：nums = [1, 1, 2]
//输出：
//[[1, 1, 2],
//[1, 2, 1],
//[2, 1, 1]]

class Solution {
public:
    vector<vector<int>> reslut;
    vector<int> path;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size(), false);//记录已经使用过的数
        sort(nums.begin(), nums.end());//排序是让相同的元素堆在一起
        backtracking(nums, used);
        return reslut;

    }
    void backtracking(const vector<int>& nums, vector<bool>& used)
    {
        if (path.size() == nums.size())
        {
            reslut.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if ((used[i] == true) || (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == false))//过滤已经选过的数和相同的数--抽象成树层去重
                continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
};