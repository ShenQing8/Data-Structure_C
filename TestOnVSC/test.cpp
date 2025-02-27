#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

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
int main()
{
    vector<int> nums = {1,2,3,4,5,6};
    vector<int> ret = getAverages(nums, 2);
    return 0;
}
