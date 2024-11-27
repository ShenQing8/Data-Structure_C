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
/*带约束爬楼梯*/
int climbingStairsConstraintDP1(int n)
{
    // dp(n) = onlyOnestep(dp(n-1)) + dp(n-2)
    // onlyOnestep(dp(n-1)) = dp(n-3)
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
/* 带约束爬楼梯：动态规划 */
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

int main()
{
    int steps1 = climbingStairsConstraintDP1(100);
    cout << steps1 << endl;

    int steps2 = climbingStairsConstraintDP2(100);
    cout << steps2 << endl;

    return 0;
}
