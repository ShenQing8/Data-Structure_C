#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstring>
using namespace std;

void test1()
{
    // 先假定所有数都是素数
    vector<int> isPri(2025, 1);
    isPri[0] = isPri[1] = 0;
    for(int i = 2; i < 2024; ++i)
    {
        if(isPri[i])
        {
            for(int j = 2 * i; j <= 2024; j += i)
            {
                isPri[j] = 0;
            }
        }
    }
    for(int i = 2024; i > 1; --i)
    {
        if(isPri[i] && 2024 % i == 0)
        {
            cout << i;
            break;
        }
    }
}

void test2()
{
    int n = 2024;
    int m = 1024;
    for(int i = 2024; i <= 2024 * 1024; ++i)
    {
        if(i % n == 0 && i % m == 0)
        {    
            cout << i;
            break;
        }
    }
}

void test3()
{
    int n = 2024;
    int count = 0;
    for(int i = 1; i <= 2024; ++i)
    {
        int a = i ^ n;
        if((i ^ n) < 2024)
            ++count;
    }
    cout << count;
}

// int get_maxnum(int n)
// {
//     int ret = n % 10;
//     while(n)
//     {
//         n /= 10;
//         ret = max(n % 10, ret);
//     }
//     return ret;
// }
// void test4()
// {
//     vector<int> dp(2025, 0);
//     dp[0] = INT_MAX - 10;
//     dp[2] = 1;
//     dp[3] = 2;
//     dp[4] = 3;
//     for(int i = 4; i <= 2024; ++i)
//     {
//         int bin = 0;
//         if(i % 2 == 0)
//             int bin = i / 2;
//         dp[i] = min(min(dp[bin] + 10, dp[i - get_maxnum(i)] + 3), dp[i - 1] + 1);
//     }
//     cout << dp[2024];
// }

int maxDigit(int num) {
    int max_d = 0;
    while (num) {
        max_d = max(max_d, num % 10);
        num /= 10;
    }
    return max_d;
}

int test4() {
    const int N = 2025;
    int dp[N];
    memset(dp, 0x3f, sizeof(dp));
    dp[1] = 0;
    for (int i = 1; i < N - 1; ++i) {
        // 花费1的代价将整数增加1
        dp[i + 1] = min(dp[i + 1], dp[i] + 1);
        // 花费3的代价将整数增加数位中最大的那个
        int add_max = maxDigit(i);
        dp[i + add_max] = min(dp[i + add_max], dp[i] + 3);
        // 花费10的代价将整数变为原来的2倍
        if(2 * i < N)
            dp[2 * i] = min(dp[2 * i], dp[i] + 10);
    }
    cout << dp[2024] << endl;
}

void test5()
{
    vector<int> nums = {534, 386, 319, 692, 169, 338, 521, 713, 640, 692, 969, 362, 311, 349, 308, 357, 515, 140, 591, 216,
                        57, 252, 575, 630, 95, 274, 328, 614, 18, 605, 17, 980, 166, 112, 997, 37, 584, 64, 442, 495,
                        821, 459, 453, 597, 187, 734, 827, 950, 679, 78, 769, 661, 452, 983, 356, 217, 394, 342, 697, 878,
                        475, 250, 468, 33, 966, 742, 436, 343, 255, 944, 588, 734, 540, 508, 779, 881, 153, 928, 764, 703,
                        459, 840, 949, 500, 648, 163, 547, 780, 749, 132, 546, 199, 701, 448, 265, 263, 87, 45, 828, 634};
    sort(nums.begin(), nums.end());
    int sum = 0;
    for(int i = 0; i < nums.size(); ++i)
        sum += nums[i];
    cout << sum << endl;
    cout << sum % 24;
}

void test6()
{
    int friends = 2024;
    int n = 0;
    cin >> n;

    cout << 2024 / n + 1;
}

void test7()
{
    int min_bin = INT_MAX;
    int n = 0;
    cin >> n;
    vector<int> nums(n, 0);
    for(int i = 0; i < n; ++i)
    {
        cin >> nums[i];
        if(nums[i] % 2 == 0)
            min_bin = min(min_bin, nums[i]);
    }
    cout << min_bin;
}

void test8()
{
    string flag = "LANQIAO";
    string cur;
    cin >> cur;
    string cmp = "";
    int j = 0;
    for(int i = 0; i < cur.length(); ++i)
    {
        if(cur[i] == flag[j])
        {
            cmp.push_back(cur[i]);
            ++j;
        }
    }
    if(cmp == flag)
        cout << "YES";
    else
    cout << "NO";
}


int calculateSum(vector<vector<int>>& nums, int x1, int y1, int x2, int y2)
{
    int sum = 0;
    int i = x1;
    int j = y1;
    for(; i <= x2 && j <= y2; ++i, ++j)
    {
        // 左
        sum += nums[i][y1];
        // 右
        sum += nums[i][y2];
        // 上
        sum += nums[x1][j];
        // 下
        sum += nums[x2][j];
    }
    // 减去四个角
    sum -= nums[x1][y1];
    sum -= nums[x1][y2];
    sum -= nums[x2][y1];
    sum -= nums[x2][y2];
    return sum;
} 
void test9()
{
    int n = 0, m = 0;
    cin >> n >> m;
    vector<vector<int>> nums(n, vector<int>(m, 0));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            cin >> nums[i][j];

    int maxSum = -INT_MAX;  // 初始化最大和为一个较小值
    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < m; y1++) {
            for (int size = 1; x1 + size < n && y1 + size < m; size++) {
                int x2 = x1 + size;
                int y2 = y1 + size;
                int curSum = calculateSum(nums, x1, y1, x2, y2);
                maxSum = max(maxSum, curSum);
            }
        }
    }
    cout << maxSum << endl;
}

int main()
{
    //test1();
    //test2();
    //test3();
    //test4();
    //test5();
    //test6();
    //test7();
    //test8();
    test9();

    return 0;
}
