#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <unordered_set>
using namespace std;

ostream &operator<<(ostream& out, vector<int>& values)
{
    for(int i = 0; i < values.size() - 1; ++i)
    {
        cout << values[i] << " ";
    }
    return out << values[values.size() - 1];
}

/*2090. 半径为 k 的子数组平均值*/
vector<int> getAverages(vector<int>& nums, int k) 
{
    vector<int> ret(nums.size(), -1);
    int sum = 0;
    for(int i = 0; i < 2 * k; ++i)
        sum += nums[i];
    for(int i = k; i < nums.size() - k; ++i)
    {
        // 入
        sum += nums[i + k];
        // 更新
        ret[i] = sum / (2 * k + 1);
        // 出
        sum -= nums[i - k];
    }
    return ret;
}

#pragma region 单调栈
class RegularStack
{
private:
    /* data */
public:
    RegularStack(/* args */);
    ~RegularStack();
    #pragma region 1475
    vector<int> finalPrices(vector<int>& prices) 
    {
        int n = prices.size();
        vector<int> ans(n);
        ans = prices;
        stack<int> tmp;
        for(int i = 0; i < n; ++i)
        {
            while(!tmp.empty() && prices[tmp.top()] >= prices[i])
            {
                ans[tmp.top()] = prices[tmp.top()] - prices[i];
                tmp.pop();
            }
            tmp.push(i);
        }
        return ans;
    }
    #pragma endregion

    #pragma region 853
    int carFleet(int target, vector<int>& position, vector<int>& speed) 
    {
        int n = position.size();
        //unordered_map<int, int> inf;
        map<int, int> inf;
        int ans = 1;
        for(int i = 0; i < n; ++i)
        {
            inf.insert(make_pair(position[i], speed[i]));
        }
        stack<int> tmp;
        // for(int i = 0; i <= target; ++i)
        // {
        //     if(inf.find(i) != inf.end())
        //     {
        //         if(!tmp.empty() && ((double)(target - i) / (double)inf[i]) < tmp.top())
        //         {
        //             while(!tmp.empty())
        //                 tmp.pop();
        //             ++ans;
        //         }
        //         tmp.push((double)(target - i) / (double)inf[i]);
        //     }
        // }
        for(auto& [s, t] : inf)
        {
            double time = (double)(target - s) / t;
            while(!tmp.empty() && time >= tmp.top())
            {
                tmp.pop();
            }
            tmp.push(time);
        }
        return tmp.size();
    }
    #pragma endregion

};
RegularStack::RegularStack(/* args */)
{
}
RegularStack::~RegularStack()
{
}
#pragma endregion

#pragma region 网络图(DFS,BFS)
#pragma region 面试题 16.19. 水域大小
class WaterSquare
{
public:
    vector<int> pondSizes(vector<vector<int>>& land) 
    {
        m = land.size();
        n = land[0].size();
        vector<int> water_num;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(land[i][j] == 0)
                {
                    tmp = 0;
                    dfs(land, i, j);
                    water_num.push_back(tmp);
                }
            }
        }
        sort(water_num.begin(), water_num.end());
        return water_num;

    }
    void dfs(vector<vector<int>>& land, int x, int y)
    {
        if(x < 0 || x >= m || y < 0 || y >= n || land[x][y] != 0)
            return;
        land[x][y] = 1;
        ++tmp;
        dfs(land, x, y - 1);
        dfs(land, x, y + 1);
        dfs(land, x - 1, y - 1);
        dfs(land, x - 1, y + 1);
        dfs(land, x + 1, y - 1);
        dfs(land, x + 1, y + 1);
        dfs(land, x - 1, y);
        dfs(land, x + 1, y);
    }
    int m;
    int n;
    int tmp;
};
#pragma endregion

#pragma endregion

int main()
{
    /*2090. 半径为 k 的子数组平均值*/
    // vector<int> nums = {1,2,3,4,5,6};
    // vector<int> ret = getAverages(nums, 2);

    /*单调栈*/
    //RegularStack regular_stack = RegularStack();
    // 1475
    // vector<int> prices = {8,4,6,2,3};
    // vector<int> ans = regular_stack.finalPrices(prices);
    // cout << ans << '\n';
    // cout << prices;
    // 853
    // vector<int> position = {10,8,0,5,3};
    // vector<int> speed = {2,4,1,1,3};
    // int target = 12;
    // cout << regular_stack.carFleet(target, position, speed) << endl;

    /*网络图*/
    // 面试题 16.19
    WaterSquare wat;
    vector<vector<int>> land =  {{0,2,1,0},{0,1,0,1},{1,1,0,1},{0,1,0,1}};
    vector<int> ret = wat.pondSizes(land);
    cout << ret << endl;



    // cout << __cplusplus << endl;
    return 0;
}

