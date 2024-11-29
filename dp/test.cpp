#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 经典问题：给定一个共有 n 阶的楼梯，你每步可以上 1 阶或者 2 阶，请问有多少种方案可以爬到楼顶？
// dp[i] = dp[i-1] + dp[i-2]
// 常用术语：将数组dp称为表，，dp[i] 表示状态 i 对应子问题的解
// 将最小子问题对应的状态(例如：上述经典问题中的dp[1]和dp[2])称为初始状态
// 将递推公式 de[i] = dp[i-1] + dp[i-2] 称为状态转移方程

// 动态规划常用来求解最优化问题，它们不仅包含重叠子问题，还具有另外两大特性：最优子结构、无后效性。
/*最优子结构*/
/*爬楼梯最小代价*/
int minCostClimbingStairsDP(vector<int>& cost)
{
    // 状态转移方程：cost(n) = min(cost(n-1), cost(n2)) + cost(n)
    int n = cost.size() - 1;
    if(n == 1 || n == 2)
        return cost[n];
    int costA = cost[1];
    int costB = cost[2];
    int minCost = 0;
    for(int i = 3; i <= n; ++i)
    {
        int tmp = costB;
        costB = min(costA, costB) + cost[i];
        costA = tmp;
    }
    return costB;
}
/*无后效性*/
/*带约束爬楼梯*/ // 对 K 神的解法进行空间优化
int climbingStairsConstraintDP1(int n)
{
    // dp(n) = onlyOnestep(dp(n-1)) + dp(n-2)
    // onlyOnestep(dp(n-1)) = dp(n-3)
    // 所以dp(n) = dp(n-2) + dp(n-3)
    // dp(1) = 1, dp(2) = 1
    if(n == 1 || n == 2)
        return 1;
    if(n == 3)
        return 2;
    int dpA = 1;// dp(1)
    int dpB = 1;// dp(2)
    int dpC = 2;// dp(3)
    for(int i = 4; i <= n; ++i)
    {
        int tmp = dpC;
        dpC = dpA + dpB;// dp(4),dp(5),dp(6)…………,dp(n)
        dpA = dpB;
        dpB = tmp;
    }
    return dpC;
}
// K 神解法
int climbingStairsConstraintDP2(int n) 
{
    if (n == 1 || n == 2) {
        return 1;
    }
    // 初始化 dp 表，用于存储子问题的解
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    // 初始状态：预设最小子问题的解
    dp[1][1] = 1;
    dp[1][2] = 0;
    dp[2][1] = 0;
    dp[2][2] = 1;
    // 状态转移：从较小子问题逐步求解较大子问题
    for (int i = 3; i <= n; i++) {
        dp[i][1] = dp[i - 1][2];
        dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
    }
    return dp[n][1] + dp[n][2];
}

/*0-1背包问题*/
int knapsackDP(vector<int>& wgt, vector<int>& val, int cap)
{
    // 状态转移方程：dp[i][j] = max(dp[i-1][j], dp[i-1][j-wgt[i-1]] + val[i-1])
    int n = wgt.size();
    // 初始化dp表
    // vector<vector<int>> dp(n + 1, vector<int>(cap+1, 0));

    // 空间优化dp表
    vector<int> dp(cap+1, 0);

    // 状态转移
    // for(int i = 1; i <= n; ++i)// 前 i 件物品
    // {
    //     for(int j = 1; j <= cap; ++j)// 背包剩余容量
    //     {
    //         if(j - wgt[i-1] < 0)
    //             dp[i][j] = dp[i-1][j];
    //         else
    //             dp[i][j] = max(dp[i-1][j], dp[i-1][j-wgt[i-1]] + val[i-1]);
    //     }
    // }
    // return dp[n][cap];

    // 空间优化后   状态转移方程：dp[j] = max(dp[j], dp[j - wgt[ i-1 ]] + val[ i-1 ])
    // 需要采用倒序遍历，如采用正序，进行转移时左上角的值可能已被覆盖
    for(int i = 1; i <= n; ++i)
    {
        for(int j = cap; j > 0; --j)
        {
            if(j >= wgt[i-1])
                dp[j] = max(dp[j], dp[j - wgt[ i-1 ]] + val[ i-1 ]);
        }
    }
    return dp[cap];
}

/*完全背包问题*/
// 状态转移方程变成了：dp[i][j] = max(dp[i-1][j], dp[i][j - wgt[i-1]] + val[i-1])
int unboundedKnapsackDPComp(vector<int>& wgt, vector<int>& val, int cap)
{
    int n = wgt.size();

    vector<int> dp(cap+1, 0);
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= cap; ++j)
        {// 此处与0-1背包不同，因为当前状态不与左上角状态有关，而与左边状态有关，所以需要正序遍历
            if(j >= wgt[i-1])
                dp[j] = max(dp[j], dp[j - wgt[ i-1 ]] + val[ i-1 ]);
        }
    }

    return dp[cap];
}

/*编辑距离问题*/
// int editDistanceDP(string& s, string& t)// s 转为 t 所需要的最小操作步骤数
// {
//     int n = s.length();
//     int m = t.length();
//     // 初始化dp表
//     vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
//     for(int i = 1; i <= n; ++i)
//         dp[i][0] = i;
//     for(int j = 1; j <= m; ++j)
//         dp[0][j] = j;
//     // 状态转移方程为：
//     // 当s[i-1] != t[j-1]时：dp[i][j] = min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1
//     //                                    添加            删除           替换
//     // 当s[i-1] == t[j-1]时：dp[i][j] = dp[i-1][j-1]
//     for(int i = 1; i <= n; ++i)
//     {
//         for(int j = 1; j <= m; ++j)
//         {
//             if(s[i - 1] == t[j - 1])
//                 dp[i][j] = dp[i - 1][j -1];
//             else
//                 dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
//         }
//     }
//     return dp[n][m];
// }
// 空间优化后
int editDistanceDP(string s, string t)// s 转为 t 所需要的最小操作步骤数
{
    int n = s.length();
    int m = t.length();
    // 初始化dp表
    vector<int> dp(m + 1, 0);
    for(int j = 1; j <= m; ++j)
        dp[j] = j;
    // 定义一个变量暂存左上角的值，方便正序遍历
    for(int i = 1; i <= n; ++i)
    {
        int leftup = dp[0];
        dp[0] = i;
        for(int j = 1; j <= m; ++j)
        {
            int tmp = dp[j];

            if(s[i - 1] == t[j - 1])
                dp[j] = leftup;
            else
                dp[j] = min(min(leftup, dp[j - 1]), dp[j]) + 1;
           
            leftup = tmp;
        }
    }
    return dp[m];
}
/* 编辑距离：空间优化后的动态规划 */
// int editDistanceDPComp(string s, string t) 
// {
//     int n = s.length(), m = t.length();
//     vector<int> dp(m + 1, 0);
//     for (int j = 1; j <= m; j++) 
//     {
//         dp[j] = j;
//     }
//     for (int i = 1; i <= n; i++) 
//     {
//         int leftup = dp[0];
//         dp[0] = i;
//         for (int j = 1; j <= m; j++) 
//         {
//             int temp = dp[j];
//             if (s[i - 1] == t[j - 1]) 
//             {
//                 dp[j] = leftup;
//             } else {
//                 dp[j] = min(min(dp[j - 1], dp[j]), leftup) + 1;
//             }
//             leftup = temp;
//         }
//     }
//     return dp[m];
// }


int main()
{
    // int steps1 = climbingStairsConstraintDP1(100);
    // cout << steps1 << endl;

    // int steps2 = climbingStairsConstraintDP2(100);
    // cout << steps2 << endl;

    /*0-1背包*/
    vector<int> wgt = {1,2,3,4,5,6,7};
    vector<int> val = {5,11,15,16,20,25,29};
    int cap = 7;
    int max_val = knapsackDP(wgt, val, cap);
    cout << max_val << endl;

    /*完全背包*/
    int max_val_un = unboundedKnapsackDPComp(wgt, val, cap);
    cout << max_val_un << endl;

    /*编辑距离问题*/
    string s = "kitten";
    string t = "sitting";
    int min_len = editDistanceDP(s, t);
    cout << min_len << endl;

    return 0;
}
