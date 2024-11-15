#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
//@kkk.cyz.7892
void test1()
{
	vector<int> pre;
	int count = 0;
	for (int i = 2; i < 2025; ++i)
	{
		int j = 2;
		for (j = 2; j <= i; ++j)
		{
			if (i % j == 0)
				break;
		}
		if (j == i)
			pre.emplace_back(j);
	}
	for (int val : pre)
	{
		if (2024 % val == 0)
			++count;
	}
	cout << count;
}

void test2()
{
	int count = 0;
	int num = 2024;
	while (num > 1)
	{
		num = (int)sqrt(double(num));
		++count;
	}
	cout << count << endl;
}

void test3()
{
	int num = 2024;
	cout << cbrt(double(num)) << endl;
}

void test4()
{
	int month[13] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int cur_w = 2;
	int ans = 0;
	for (int y = 1901; y <= 2024; ++y)
	{
		for (int m = 1; m <= 12; ++m)
		{
			int d = 1;
			for (d = 1; d <= days[m]; d += 10)
			{
				if (cur_w == 1)
					++ans;
				cur_w = (cur_w + 10) % 7;
			}
			cur_w = (cur_w + days[m] - d + 11) % 7;
		}
		cur_w = (cur_w + 1) % 7;
	}
	cout << ans << endl;
}

void test6()
{
	int n = 0;
	cin >> n;
	cout << (n / 15) * 2 << endl;
}

void test7()
{
	int n = 0;
	cin >> n;
	int max_ind = 0;
	while (n)
	{
		max_ind = max(n % 10, max_ind);
		n /= 10;
	}
	cout << max_ind;
}

void test8()
{
	string s;
	cin >> s;
	int val[2] = { 0 };
	int i = 0;
	for (char a : s)
	{
		if (a == '-')
			i = 1;
		val[i] = val[i] * 10 + atoi(&a);
	}
	cout << val[0] - val[1];
}

void test9()
{
	vector<int> nums;
	int n = 0;
	cin >> n;
	nums.resize(n, 0);
	int i = 0;
	while (i < nums.size() && cin >> nums[i])
		++i;
	int k = 0;
	cin >> k;
	long long ans1 = 0;
	for (int i = 0; i < 2 * k; i += 2)
	{
		ans1 += nums[i];
	}
	for (int i = 2; i < nums.size() - 2 * k + 2; i += 2)
	{
		long long tmp = ans1 - nums[i - 2] + nums[i + 2 * (k - 1)];
		ans1 = max(ans1, tmp);
	}
	long long ans2 = 0;
	for (int i = 1; i < 1 + 2 * k; i += 2)
	{
		ans2 += nums[i];
	}
	for (int i = 3; i < nums.size() - 2 * k + 2; i += 2)
	{
		long long tmp = ans2 - nums[i - 2] + nums[i + 2 * (k - 1)];
		ans2 = max(ans2, tmp);
	}
	cout << max(ans1, ans2);
}

int test10(vector<int>& nums)
{
	unordered_map<int, vector<int>> min_hook;
	int ans = 0;
	for (int i = 0; i < nums.size(); ++i)
	{
		min_hook[nums[i]].emplace_back(i);
	}
	sort(nums.begin(), nums.end());


	return nums.size();
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test6();
	//test7();
	//test8();
	//test9();

	return 0;
}
