#include <iostream>
#include <string>
#include <vector>
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

class Solution
{
public:
    int binSearch(vector<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }
    vector<int> searchRange(vector<int>& nums, int target)
    {
        int left = binSearch(nums, target);
        if (left == nums.size() || nums[left] != target)
            return { -1, -1 }; // nums 中没有 target
        int right = binSearch(nums, target + 1) - 1;
        return { left, right };
    }
};

int main()
{
    //string s = "ibpbhixfiouhdljnjfflpapptrxgcomvnb";
    //Solution sl;
    //sl.maxVowels(s, 33);

    vector<int> nums;
    Solution sl;
    sl.searchRange(nums, 8);
	return 0;
}
