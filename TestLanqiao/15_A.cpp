#include <iostream>
#include <unordered_map>
//#include <bits/stdc++.h>
using namespace std;

/*A*/
int bihua(int x, int (&count2hua)[10])
{
    int ret = 0;
    if(x < 10)
        ret += count2hua[0];
    while(x)
    {
        ret += count2hua[x % 10];
        x /= 10;
    }
    return ret;
}
int BasketDays()
{
    int count2hua[10] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ans = 0;
    int y_bihua = 0;
    int m_bihua = 0;
    for(int year = 2000; year < 2025; ++year)
    {
        y_bihua = bihua(year, count2hua);// 计算当年年份的笔画
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)// 判断闰年
            days[2] = 29;
        for(int month = 1; month < 13; ++month)
        {
            m_bihua = bihua(month, count2hua);// 计算当月月份的笔画
            for(int day = 1; day <= days[month]; ++day)
            {
                if(bihua(day, count2hua) + y_bihua + m_bihua > 50)// 总笔画数相加与50比较
                    ++ans;
                if(day == 13 && month == 4 && year == 2024)
                    return ans;
            }
        }
        days[2] = 28;
    }
}

int main()
{
    /*A*/
    int bsk_days = BasketDays();
    cout << bsk_days << endl;
    return 0;
}
