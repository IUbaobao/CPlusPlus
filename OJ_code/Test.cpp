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
//class Solution {
//public:
//    vector<vector<int>> reslut;
//    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
//        vector<int> path;
//        vector<bool> used(nums.size(), false);//�����ж��Ƿ�ʹ�ù������
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



//491. ����������
//����һ���������� nums ���ҳ����������и������в�ͬ�ĵ��������У������������� ����������Ԫ�� ������԰� ����˳�� ���ش𰸡�
//�����п��ܺ����ظ�Ԫ�أ����������������ȣ�Ҳ���������������е�һ�����������
//ʾ�� 1��
//���룺nums = [4, 6, 7, 7]
//����� [[4, 6], [4, 6, 7], [4, 6, 7, 7], [4, 7], [4, 7, 7], [6, 7], [6, 7, 7], [7, 7]]
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
//        unordered_set<int> s;//����ȥ��
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


//46. ȫ����
//����һ�������ظ����ֵ����� nums �������� ���п��ܵ�ȫ���� ������� ������˳�� ���ش𰸡�
//
//ʾ�� 1��
//���룺nums = [1, 2, 3]
//����� [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]


class Solution {
public:
    vector<vector<int>> reslut;
    vector<int> path;
    vector<vector<int>> permute(vector<int>& nums) {

        vector<bool> used(nums.size(), false);//��¼�Ѿ�ʹ�ù�����
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
            if (used[i] == true)//�����Ѿ�ѡ������
                continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
};


//47. ȫ���� II
//����һ���ɰ����ظ����ֵ����� nums ��������˳�� �������в��ظ���ȫ���С�
//
//ʾ�� 1��
//���룺nums = [1, 1, 2]
//�����
//[[1, 1, 2],
//[1, 2, 1],
//[2, 1, 1]]

class Solution {
public:
    vector<vector<int>> reslut;
    vector<int> path;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size(), false);//��¼�Ѿ�ʹ�ù�����
        sort(nums.begin(), nums.end());//����������ͬ��Ԫ�ض���һ��
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
            if ((used[i] == true) || (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == false))//�����Ѿ�ѡ����������ͬ����--���������ȥ��
                continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
};