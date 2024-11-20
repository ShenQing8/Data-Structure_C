#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
using namespace std;

//class Solution
//{
//public:
//    int maxVowels(string s, int k)
//    {
//        int len = s.length();
//        int ans = 0, vowel = 0;
//        for (int i = 0; i < len; ++i)
//        {
//            // 入
//            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
//                ++vowel;
//            if (i < k - 1)// 若不满 k 个，则继续
//                continue;
//            // 更新
//            ans = max(ans, vowel);
//            // 出
//            char out = s[i - k + 1];
//            if (out == 'a' || out == 'e' || out == 'i' || out == 'o' || out == 'u')
//                --vowel;
//        }
//        return ans;
//    }
//};

//class Solution
//{
//public:
//    int binSearch(vector<int>& nums, int target)
//    {
//        int left = 0;
//        int right = nums.size() - 1;
//        while (left <= right)
//        {
//            int mid = left + (right - left) / 2;
//            if (nums[mid] < target)
//                left = mid + 1;
//            else
//                right = mid - 1;
//        }
//        return left;
//    }
//    vector<int> searchRange(vector<int>& nums, int target)
//    {
//        int left = binSearch(nums, target);
//        if (left == nums.size() || nums[left] != target)
//            return { -1, -1 }; // nums 中没有 target
//        int right = binSearch(nums, target + 1) - 1;
//        return { left, right };
//    }
//};

//class Solution
//{
//public:
//    int f(string& s)
//    {
//        sort(s.begin(), s.end());
//        int count = 0;
//        char w = s[0];
//        for (int i = 0; w == s[i]; ++i)
//            ++count;
//        return count;
//    }
//    int bin_search(vector<int>& arr, int target)
//    {
//        int left = 0;
//        int right = arr.size() - 1;
//        while (left <= right)
//        {
//            int mid = left + (right - left) / 2;
//            if (arr[mid] < target)
//                left = mid + 1;
//            else
//                right = mid - 1;
//        }
//        return left;
//    }
//    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words)
//    {
//        vector<int> w_nums(words.size(), 0);
//        vector<int> ret(queries.size(), 0);
//        for (int i = 0; i < words.size(); ++i)
//        {
//            w_nums[i] = f(words[i]);
//        }
//        sort(w_nums.begin(), w_nums.end());
//        for (int i = 0; i < queries.size(); ++i)
//        {
//            int ind = bin_search(w_nums, f(queries[i]) + 1);
//            if (ind >= words.size());
//            else
//                ret[i] = words.size() - ind;
//        }
//        return ret;
//    }
//};

//class RangeFreqQuery
//{
//public:
//    unordered_map<int, vector<int>> num_map;
//    RangeFreqQuery(vector<int>& arr)
//    {
//        for (int i = 0; i < arr.size(); ++i)
//            num_map[arr[i]].emplace_back(i);
//    }
//    int bin_search(vector<int>& arr, int target)
//    {
//        int left = 0;
//        int right = arr.size() - 1;
//        while (left <= right)
//        {
//            int mid = left + (right - left) / 2;
//            if (arr[mid] < target)
//                left = mid + 1;
//            else
//                right = mid - 1;
//        }
//        return left;
//    }
//    int query(int left, int right, int value)
//    {
//        int l = bin_search(num_map[value], left);
//        if (l >= num_map[value].size())
//            return 0;
//        int r = bin_search(num_map[value], right + 1);
//        return r - l;
//    }
//};

class Solution
{
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper)
    {
        sort(nums.begin(), nums.end());
        long long count = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto r = upper_bound(nums.begin(), nums.begin() + i, upper - nums[i]);
            auto l = lower_bound(nums.begin(), nums.begin() + i, lower - nums[i]);
            count += r - l;
        }
        return count;
    }
};

int digit(int num, int exp) // exp = 10^(k-1)
{
    return (num / exp) % 10;
}
void countingSortDigit(vector<int>& nums, int exp)
{
    // 由于是十进制数，所以最大数是9
    vector<int> counter(10, 0);
    for (int num : nums)
    {
        int n = digit(num, exp);
        ++counter[n];
    }
    // 计算前缀和
    for (int i = 1; i < 10; ++i)
        counter[i] += counter[i - 1];
    // 倒序遍历师数组
    int n = nums.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; --i)
    {
        int n = digit(nums[i], exp);
        res[counter[n] - 1] = nums[i];
        --counter[n];
    }
    // 排序后的数组覆盖原数组
    nums = res;
}
void radixSort(vector<int>& nums)
{
    // 获取数组中的最大元素
    int m = *max_element(nums.begin(), nums.end());
    // 从个位一直排序到最高位
    for (int exp = 1; exp <= m; exp *= 10)
    {
        // 按第 i 位数排序
        countingSortDigit(nums, exp);
    }
}

int main()
{
    //string s = "ibpbhixfiouhdljnjfflpapptrxgcomvnb";
    //Solution sl;
    //sl.maxVowels(s, 33);

    //vector<int> nums;
    //Solution sl;
    //sl.searchRange(nums, 8);

    //vector<string> queries = { "bba","abaaaaaa","aaaaaa","bbabbabaab","aba","aa","baab","bbbbbb","aab","bbabbaabb" };
    //vector<string> words = { "aaabbb","aab","babbab","babbbb","b","bbbbbbbbab","a","bbbbbbbbbb","baaabbaab","aa" };
    //Solution sl;
    //sl.numSmallerByFrequency(queries, words);

    // 第四个测试省略

    vector<int> rad_nums = { 202312345, 202313526, 202366789, 2134, 56789, 999999 };
    radixSort(rad_nums);

	return 0;
}
