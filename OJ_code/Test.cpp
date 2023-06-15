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
//
//class Solution {
//public:
//    int minPathSum(vector<vector<int>>& grid) {
//
//        int m = grid.size(), n = grid[0].size();
//
//        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
//        dp[0][1] = 0;
//        for (int i = 1; i < m + 1; ++i)
//            for (int j = 1; j < n + 1; ++j)
//            {
//                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
//            }
//        return dp[m][n];
//    }
//};

//174. 地下城游戏
//恶魔们抓住了公主并将她关在了地下城 dungeon 的 右下角 。地下城是由 m x n 个房间组成的二维网格。我们英勇的骑士最初被安置在 左上角 的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。
//
//骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。
//
//有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。
//
//为了尽快解救公主，骑士决定每次只 向右 或 向下 移动一步。
//
//返回确保骑士能够拯救到公主所需的最低初始健康点数。
//
//注意：任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。


//class Solution {
//public:
//    int calculateMinimumHP(vector<vector<int>>& dungeon) {
//
//        int m = dungeon.size(), n = dungeon[0].size();
//        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
//        //dp[i]:以i位置为起点到终点的最小健康值
//        dp[m][n - 1] = dp[m - 1][n] = 1;//保证它到右下角的值为1
//        for (int i = m - 1; i >= 0; --i)
//            for (int j = n - 1; j >= 0; --j)
//            {
//                dp[i][j] = max(min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j], 1);
//            }
//        return dp[0][0];
//    }
//};


//17.16.按摩师
//一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。在每次预约服务之间要有休息时间，因此她不能接受相邻的预约。给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。
//输入：[1, 2, 3, 1]
//输出： 4
//解释： 选择 1 号预约和 3 号预约，总时长 = 1 + 3 = 4。
//class Solution {
//public:
//    int massage(vector<int>& nums) {
//
//        int n = nums.size();
//        if (n == 0)    return 0;
//        vector<int> f(n);//f[i]表示接i位置的预约的最大值时间
//        auto g = f;//g[i]表示不接i位置的预约的最大值时间
//        f[0] = nums[0];
//        for (int i = 1; i < n; ++i)
//        {
//            f[i] = g[i - 1] + nums[i];
//            g[i] = max(f[i - 1], g[i - 1]);
//        }
//        return max(f[n - 1], g[n - 1]);
//    }
//};


//198. 打家劫舍
//你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
//
//给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0)    return 0;
        vector<int> f(n);//f[i]表示偷i位置的的最大值金额
        auto g = f;//g[i]表示不偷i位置的的最大值金额
        f[0] = nums[0];
        for (int i = 1; i < n; ++i)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }
        return max(f[n - 1], g[n - 1]);

    }
};


//213. 打家劫舍 II
//你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

//给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。
//
//class Solution {
//public:
//    int rob(vector<int>& nums) {
//
//        int n = nums.size();
//        if (n == 0) return 0;
//        return max(rob1(nums, 1, n - 1), nums[0] + rob1(nums, 2, n - 2));
//    }
//
//    int rob1(vector<int>& nums, int left, int right) {
//        if (left > right)  return 0;
//        int n = nums.size();
//        vector<int> f(n);//f[i]表示偷i位置的的最大值金额
//        auto g = f;//g[i]表示不偷i位置的的最大值金额
//        f[left] = nums[left];
//        for (int i = left + 1; i <= right; ++i)
//        {
//            f[i] = g[i - 1] + nums[i];
//            g[i] = max(f[i - 1], g[i - 1]);
//        }
//        return max(f[right], g[right]);
//    }
//};

//740. 删除并获得点数
// 给你一个整数数组 nums ，你可以对它进行一些操作。
//
//每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。
//
//开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。

//class Solution {
//public:
//    int deleteAndEarn(vector<int>& nums) {
//        const int N = 10001;
//        int arr[N] = { 0 };
//        //将相同的值映射到相应的数组下标--转化成打家劫舍问题
//        for (int i = 0; i < nums.size(); ++i)
//        {
//            arr[nums[i]] += nums[i];
//        }
//
//        vector<int> f(N);
//        auto g = f;
//        for (int i = 1; i < N; i++)
//        {
//            f[i] = g[i - 1] + arr[i];
//            g[i] = max(g[i - 1], f[i - 1]);
//        }
//        return max(f[N - 1], g[N - 1]);
//    }
//};

//
//剑指 Offer II 091. 粉刷房子
//假如有一排房子，共 n 个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
//当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。每个房子粉刷成不同颜色的花费是以一个 n x 3 的正整数矩阵 costs 来表示的。
//例如，costs[0][0] 表示第 0 号房子粉刷成红色的成本花费；costs[1][2] 表示第 1 号房子粉刷成绿色的花费，以此类推。
//请计算出粉刷完所有房子最少的花费成本。

//class Solution {
//public:
//    int minCost(vector<vector<int>>& costs) {
//        //状态表示
//        // dp[i][0]:表示第i个房子粉刷成红色花费的最小成本
//        // dp[i][1]:表示第i个房子粉刷成蓝色花费的最小成本
//        // dp[i][2]:表示第i个房子粉刷成绿色花费的最小成本
//        //状态转移方程
//        // dp[i][O]=min(dp[i-1][1],dp[i-1][2])+costs[i][0]
//        // dp[i][1]=min(dp[i-1][0],dp[i-1][2])+costs[i][1]
//        // dp[i][2]=min(dp[i-1][0],dpli-1][1])+costs[i][2]
//
//        int n = costs.size();
//        //多开一行虚拟节点，注意下标映射关系
//        vector<vector<int>> dp(n + 1, vector<int>(3));
//        for (int i = 1; i < n + 1; i++)
//        {
//            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i - 1][0];
//            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i - 1][1];
//            dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + costs[i - 1][2];
//        }
//        return min(dp[n][0], min(dp[n][1], dp[n][2]));
//    }
//};


//309. 最佳买卖股票时机含冷冻期
//class Solution {
//public:
//    int maxProfit(vector<int>& prices) {
//        int n = prices.size();
//
//        vector<vector<int>> dp(n, vector<int>(3));
//        dp[0][0] = -prices[0];
          //dp[i][0] 表示第天处于买入状态的最大利润
         //dp[i][1] 表示第i天处于 可交易状态的最大利润
          //dp[i][2] 表示第i天处于冷冻期状态的最大利润
//        for (int i = 1; i < n; ++i)
//        {
//            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
//            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]);
//            dp[i][2] = dp[i - 1][0] + prices[i];
//        }
//
//        return max(dp[n - 1][1], dp[n - 1][2]);
//    }
//};


//714. 买卖股票的最佳时机含手续费
//给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。
//
//你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
//
//返回获得利润的最大值。
//
//注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

//class Solution {
//public:
//    int maxProfit(vector<int>& prices, int fee) {
//        int n = prices.size();
//
//
//        //1.建表
//        vector<int> g(n), f(n);
//        //1.1状态表示
//        //g[i]表示第i天处于买入状态的最大利润
//        //f[i]表示第i天处于卖出状态的最大利润
//        //2.初始化
//        g[0] = -prices[0];
//
//        for (int i = 1; i < n; ++i)
//        {
//            //3.状态转移方程
//            g[i] = max(g[i - 1], f[i - 1] - prices[i]);
//            f[i] = max(g[i - 1] + prices[i] - fee, f[i - 1]);
//        }
//
//        return f[n - 1];
//    }
//};

//123. 买卖股票的最佳时机 III
//给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
//
//设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
//
//注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        const int INF = -0x3F3F3F3F;
        vector<vector<int>> g(n, vector<int>(3, INF));
        auto f = g;
        // f[i][k]:表示第i天处于第k 笔交易 买入状态的最大利润
        // g[i][k]: 表示第i天处于k 笔交易 卖出状态的最大利润

        f[0][0] = -prices[0];
        g[0][0] = 0;
        for (int i = 1; i < n; ++i)
        {
            for (int k = 0; k < 3; ++k)
            {
                f[i][k] = max(f[i - 1][k], g[i - 1][k] - prices[i]);
                g[i][k] = g[i - 1][k];
                if (k >= 1)
                    g[i][k] = max(g[i][k], f[i - 1][k - 1] + prices[i]);
            }
        }
        int ret = INF;
        for (int i = 0; i < 3; ++i)
        {
            ret = max(ret, g[n - 1][i]);
        }
        return ret;
    }
};


//188. 买卖股票的最佳时机 IV
//给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格，和一个整型 k 。
//
//设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。
//
//注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        const int INF = -0x3F3F3F3F;
        vector<vector<int>> g(n, vector<int>(k + 1, INF));
        auto f = g;
        // f[i][k]:表示第i天处于第k 笔交易 买入状态的最大利润
        // g[i][k]: 表示第i天处于k 笔交易 卖出状态的最大利润

        f[0][0] = -prices[0];
        g[0][0] = 0;
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < k + 1; ++j)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }
        }
        int ret = INF;
        for (int i = 0; i < k + 1; ++i)
        {
            ret = max(ret, g[n - 1][i]);
        }
        return ret;

    }
};


//152. 乘积最大子数组
//给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
//
//测试用例的答案是一个 32 - 位 整数。
//
//子数组 是数组的连续子序列。


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();

        vector<int> f(n + 1, 1), g(n + 1, 1);
        int result = nums[0];
        for (int i = 1; i <= n; ++i)
        {
            int a = f[i - 1] * nums[i - 1], b = g[i - 1] * nums[i - 1];
            f[i] = max(a, max(b, nums[i - 1]));
            g[i] = min(a, min(b, nums[i - 1]));
            result = max(result, f[i]);
        }
        return result;
    }
};


//1567. 乘积为正数的最长子数组长度
//给你一个整数数组 nums ，请你求出乘积为正数的最长子数组的长度。
//
//一个数组的子数组是由原数组中零个或者更多个连续数字组成的数组。
//
//请你返回乘积为正数的最长子数组长度。

class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();

        vector<int> f(n + 1), g(n + 1);
        int ret = 0;
       /* f[i] 表⽰：以 i 结尾的所有⼦数组中，乘积为「正数」的最⻓⼦数组的⻓度；
          g[i] 表⽰：以 i 结尾的所有⼦数组中，乘积为「负数」的最⻓⼦数组的⻓度。*/
        for (int i = 1; i <= n; ++i)
        {
            if (nums[i - 1] == 0) g[i] = f[i] = 0;
            else if (nums[i - 1] > 0) {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }
        return ret;
    }
};


//413. 等差数列划分
//如果一个数列 至少有三个元素 ，并且任意两个相邻元素之差相同，则称该数列为等差数列。
//
//例如，[1, 3, 5, 7, 9]、[7, 7, 7, 7] 和[3, -1, -5, -9] 都是等差数列。
//给你一个整数数组 nums ，返回数组 nums 中所有为等差数组的 子数组 个数。
//
//子数组 是数组中的一个连续序列

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();

        vector<int> dp(n);
        // dp[i] 表⽰必须以i 位置的元素为结尾的等差数列有多少种
        int sum = 0;
        for (int i = 2; i < n; ++i)
        {
            dp[i] = nums[i - 1] - nums[i - 2] == nums[i] - nums[i - 1] ? dp[i - 1] + 1 : 0;
            sum += dp[i];
        }
        return sum;
    }
};