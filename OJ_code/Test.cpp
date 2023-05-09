//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
////93. ��ԭ IP ��ַ
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
//90. �Ӽ� II
//����һ���������� nums �����п��ܰ����ظ�Ԫ�أ����㷵�ظ��������п��ܵ��Ӽ����ݼ�����
//�⼯ ���� �����ظ����Ӽ������صĽ⼯�У��Ӽ����԰� ����˳�� ���С�
//ʾ�� 1��
//���룺nums = [1, 2, 2]
//����� [[], [1], [1, 2], [1, 2, 2], [2], [2, 2]]
class Solution {
public:
    vector<vector<int>> reslut;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> path;
        vector<bool> used(nums.size(), false);//�����ж��Ƿ�ʹ�ù������
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