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


//class Solution {
//public:
//    vector<vector<int>> reslut;
//    vector<int> path;
//    vector<vector<int>> permute(vector<int>& nums) {
//
//        vector<bool> used(nums.size(), false);//记录已经使用过的数
//        backtracking(nums, used);
//        return reslut;
//    }
//
//    void backtracking(const vector<int>& nums, vector<bool>& used)
//    {
//        if (path.size() == nums.size())
//        {
//            reslut.push_back(path);
//            return;
//        }
//
//        for (int i = 0; i < nums.size(); ++i)
//        {
//            if (used[i] == true)//过滤已经选过的数
//                continue;
//            path.push_back(nums[i]);
//            used[i] = true;
//            backtracking(nums, used);
//            used[i] = false;
//            path.pop_back();
//        }
//    }
//};


//47. 全排列 II
//给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
//
//示例 1：
//输入：nums = [1, 1, 2]
//输出：
//[[1, 1, 2],
//[1, 2, 1],
//[2, 1, 1]]
//
//class Solution {
//public:
//    vector<vector<int>> reslut;
//    vector<int> path;
//    vector<vector<int>> permuteUnique(vector<int>& nums) {
//        vector<bool> used(nums.size(), false);//记录已经使用过的数
//        sort(nums.begin(), nums.end());//排序是让相同的元素堆在一起
//        backtracking(nums, used);
//        return reslut;
//
//    }
//    void backtracking(const vector<int>& nums, vector<bool>& used)
//    {
//        if (path.size() == nums.size())
//        {
//            reslut.push_back(path);
//            return;
//        }
//
//        for (int i = 0; i < nums.size(); ++i)
//        {
//            if ((used[i] == true) || (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == false))//过滤已经选过的数和相同的数--抽象成树层去重
//                continue;
//            path.push_back(nums[i]);
//            used[i] = true;
//            backtracking(nums, used);
//            used[i] = false;
//            path.pop_back();
//        }
//    }
//};


//51. N 皇后
//按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
//
//n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
//
//给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
//
//每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

//class Solution {
//public:
//    vector<vector<string>> reslut;
//    vector<vector<string>> solveNQueens(int n) {
//        vector<string> chessboard(n, string(n, '.'));
//        backtracking(n, 0, chessboard);
//        return reslut;
//    }
//
//    void backtracking(int n, int row, vector<string>& chessboard)
//    {
//        if (n == row)
//        {
//            reslut.push_back(chessboard);
//            return;
//        }
//
//        for (int col = 0; col < n; ++col)
//        {
//            if (!isvalid(chessboard, row, col, n))
//                continue;
//            chessboard[row][col] = 'Q';
//            backtracking(n, row + 1, chessboard);
//            chessboard[row][col] = '.';
//        }
//    }
//
//    bool isvalid(const vector<string>& chessboard, int row, int col, int n)
//    {
//        //检查列
//        for (int i = 0; i < row; ++i)
//        {
//            if (chessboard[i][col] == 'Q')
//                return false;
//        }
//
//        //检查45度
//        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
//        {
//            if (chessboard[i][j] == 'Q')
//                return false;
//        }
//
//        //检查135度
//        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
//        {
//            if (chessboard[i][j] == 'Q')
//                return false;
//        }
//
//        return true;
//    }
//};

//37. 解数独
//编写一个程序，通过填充空格来解决数独问题。
//
//数独的解法需 遵循如下规则：
//
//数字 1 - 9 在每一行只能出现一次。
//数字 1 - 9 在每一列只能出现一次。
//数字 1 - 9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
//数独部分空格内已填入了数字，空白格用 '.' 表示。
//
//class Solution {
//public:
//    void solveSudoku(vector<vector<char>>& board) {
//        backtracking(board);
//    }
//
//    bool backtracking(vector<vector<char>>& board)
//    {
//        for (int i = 0; i < board.size(); ++i)
//            for (int j = 0; j < board[0].size(); ++j)
//            {
//                if (board[i][j] != '.')
//                    continue;
//                for (char k = '1'; k <= '9'; ++k)
//                {
//                    if (isvalid(i, j, k, board))
//                    {
//                        board[i][j] = k;
//                        if (backtracking(board))
//                            return true;
//                        board[i][j] = '.';
//                    }
//                }
//                return false;
//            }
//
//        return true;
//    }
//
//    bool isvalid(int row, int col, char k, vector<vector<char>>& board)
//    {
//        //检查列
//        for (int i = 0; i < board.size(); ++i)
//        {
//            if (board[i][col] == k)
//                return false;
//        }
//
//        //检查行
//        for (int j = 0; j < board.size(); ++j)
//        {
//            if (board[row][j] == k)
//                return false;
//        }
//
//        int startRow = (row / 3) * 3;
//        int startCol = (col / 3) * 3;
//        for (int i = startRow; i < startRow + 3; ++i)
//        {
//            for (int j = startCol; j < startCol + 3; ++j)
//            {
//                if (board[i][j] == k)
//                    return false;
//            }
//        }
//        return true;
//    }
//};


//#include <iostream>
//#include <cstring>
//
//#define SEP " "
//#define SEP_LEN strlen(SEP) 
//#define LINE_SEP "\r\n"
//#define LINE_SEP_LEN strlen(LINE_SEP)
//
//
//
//int main()
//{
//	const char* str1 = SEP;
//	const char* str2 = LINE_SEP;
//
//	printf("SEP_LEN strlen:%d\n", SEP_LEN);
//	printf("SEP_LEN sizeof:%d\n", sizeof(SEP));
//
//	printf("LINE_SEP_LEN strlen:%d\n", LINE_SEP_LEN);
//	printf("LINE_SEP_LEN sizeof:%d\n", sizeof(LINE_SEP));
//
//	return 0;
//}
//





//三步问题
//三步问题。有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶或3阶。实现一种方法，计算小孩有多少种上楼梯的方式。结果可能很大，你需要对结果模1000000007。


//class Solution {
//public:
//    int waysToStep(int n) {
//        if (n == 1) return 1;
//        if (n == 2) return 2;
//        int mod = 1e9 + 7;
//        int a = 1, b = 1, c = 2;
//        int reslut = 0;
//        for (int i = 3; i <= n; ++i)
//        {
//            reslut = ((a + b) % mod + c) % mod;
//            a = b;
//            b = c;
//            c = reslut;
//        }
//        return reslut;
//
//    }
//};

//746. 使用最小花费爬楼梯
//给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
//
//你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
//
//请你计算并返回达到楼梯顶部的最低花费。

//class Solution {
//public:
//    int minCostClimbingStairs(vector<int>& cost) {
//
//        int n = cost.size();
//        vector<int> dp(cost.size() + 1);
//        dp[0] = 0, dp[1] = 0;
//        for (int i = 2; i <= n; ++i)
//        {
//            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
//        }
//        return dp[n];
//    }
//};
//




//62. 不同路径
//一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
//问总共有多少条不同的路径？

//class Solution {
//public:
//    int result = 0;
//    int uniquePaths(int m, int n) {
//        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
//        dp[0][1] = 1;
//        for (int i = 1; i < m + 1; ++i)
//            for (int j = 1; j < n + 1; ++j)
//            {
//                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
//            }
//        return dp[m][n];
//    }
//};


//63. 不同路径 II
//一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。
//现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
//网格中的障碍物和空位置分别用 1 和 0 来表示。

//class Solution {
//public:
//    int uniquePathsWithObstacles(vector<vector<int>>& ob) {
//
//        int m = ob.size(), n = ob[0].size();
//        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
//        dp[0][1] = 1;
//        for (int i = 1; i < m + 1; ++i)
//            for (int j = 1; j < n + 1; ++j)
//            {
//                if (ob[i - 1][j - 1] == 1) dp[i][j] = 0;
//                else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
//            }
//        return dp[m][n];
//    }
//};

//剑指 Offer 47. 礼物的最大价值
//在一个 m* n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {

        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i < m + 1; ++i)
            for (int j = 1; j < n + 1; ++j)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
            }

        return dp[m][n];
    }
};


//931. 下降路径最小和
//给你一个 n x n 的 方形 整数数组 matrix ，请你找出并返回通过 matrix 的下降路径 的 最小和 。
//
//下降路径 可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）。具体来说，位置(row, col) 的下一个元素应当是(row + 1, col - 1)、(row + 1, col) 或者(row + 1, col + 1) 。


//class Solution {
//public:
//    int minFallingPathSum(vector<vector<int>>& matrix) {
//
//        int n = matrix.size();
//        vector<vector<int>> dp(n + 1, vector<int>(n + 2, INT_MAX));
//        for (int i = 0; i < n + 2; ++i) dp[0][i] = 0;
//
//        for (int i = 1; i < n + 1; ++i)
//            for (int j = 1; j < n + 1; ++j)
//            {
//                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j + 1], dp[i - 1][j])) + matrix[i - 1][j - 1];
//            }
//
//        int result = INT_MAX;
//        for (int i = 1; i < n + 1; ++i)
//            result = min(result, dp[n][i]);
//        return result;
//    }
//};


//64. 最小路径和
//给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
//
//说明：每次只能向下或者向右移动一步。

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[0][1] = 0;
        for (int i = 1; i < m + 1; ++i)
            for (int j = 1; j < n + 1; ++j)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
            }
        return dp[m][n];
    }
};