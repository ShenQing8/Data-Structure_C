#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
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

class RangeFreqQuery
{
public:
    unordered_map<int, vector<int>> num_map;
    RangeFreqQuery(vector<int>& arr)
    {
        for (int i = 0; i < arr.size(); ++i)
            num_map[arr[i]].emplace_back(i);
    }
    int bin_search(vector<int>& arr, int target)
    {
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }
    int query(int left, int right, int value)
    {
        int l = bin_search(num_map[value], left);
        if (l >= num_map[value].size())
            return 0;
        int r = bin_search(num_map[value], right + 1);
        return r - l;
    }
};

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

	return 0;
}
