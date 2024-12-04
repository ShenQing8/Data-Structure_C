#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*物品*/
class Item
{
public:
    int weight;
    int val;

    Item(int w, int v): weight(w), val(v) {}
};
/*分数背包*/
double fractionalKnapsack(vector<int>& wgt, vector<int>& val, int cap)
{
    // 初始化物品栏
    vector<Item> items;
    for(int i = 0; i < wgt.size(); ++i)
        items.emplace_back(Item(wgt[i], val[i]));
    // 按照 val / wgt 的顺序排序
    sort(items.begin(), items.end(), [](Item& a, Item& b){return (double)a.val / a.weight > (double)b.val / b.weight;});
    // 贪心
    double res = 0;
    for(Item& item: items)
    {
        // 背包容量充足
        if(item.weight <= cap)
        {
            res += item.val;
            cap -= item.weight;
        }
        // 背包容量不足
        else
        {
            res += (double)cap / item.weight * item.val;
            break;
        }
    }
    return res;
}

/*最大容量问题*/
int maxCapacity(vector<int>& ht)
{
    int left = 0;
    int right = ht.size() - 1;
    int max_cap = min(ht[left], ht[right]) * right;
    while(left < right)
    {
        // 取高度较小的一边，使其向对面移动
        ht[left] < ht[right] ? ++left : --right;
        int new_cap = min(ht[left], ht[right]) * (right - left);
        // 更新最大容量
        max_cap = max(max_cap, new_cap);
    }
    return max_cap;
}

/*最大切分乘积问题*/
int maxProductCutting(int n)
{
    if(n < 3)
        return n - 1;
    int count_3 = n / 3;// n 中含有 3 的个数
    int re_3 = n % 3;// 将 n 切分成 count_3 个 3 后的余数
    if(re_3 == 1)
    {
        return (int)pow(3, count_3 - 1) * 2 * 2;
    }
    else if(re_3 == 2)
    {
        return (int)pow(3, count_3) * 2;
    }
    return (int)pow(3, count_3);
}

int main()
{
    /*分数背包*/
    vector<int> wgt = {10, 20, 30, 40, 50};
    vector<int> val = {50, 120, 150, 210, 240};
    int cap = 50;
    double res = fractionalKnapsack(wgt, val, cap);
    cout << "不超过背包容量的最大物品价值为 " << res << endl;

    /*最大容量问题*/
    vector<int> ht = {3,8,5,2,7,7,3,4};
    int max_cap = maxCapacity(ht);
    cout << "最大容量为：" << max_cap << endl;

    /*最大切分乘积问题*/
    int max_cut = maxProductCutting(10);
    cout << max_cut << endl;

    return 0;
}
