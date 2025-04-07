#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
using namespace std;

#pragma region 幸运数
int Solution_A()
{
    // 10 - 100
    // 1000 - 10000
    // 100000 - 1000000
    int beg = 10;
    int end = 100;
    int l = 0, r = 0;
    int tmp,tmp2;
    int ans = 0;
    for(int i = 0; i < 4; ++i)
    {
        tmp2 = beg;
        for(;tmp2 < end; ++tmp2)
        {
            tmp = tmp2;
            for(int j = 0; j < 1 + i; ++j)
            {
                r += tmp % 10;
                tmp /= 10;
            }
            for(int j = 0; j < 1 + i; ++j)
            {
                l += tmp % 10;
                tmp /= 10;
            }
            if(l == r)
                ++ans;
            r = l = 0;
        }
        beg *= 100;
        end *= 100;
    }
    return ans;
}
#pragma endregion


#pragma region 更小的数
long long Sloution_D(char* num, int n)
{
    // int n = num.size();
    string tmp;
    long long ans = 0;
    int o,p;
    for(int i = 0; i < n - 1; ++i)
    {
        for(int j = i + 1; j < n; ++j)
        {
            if(num[j] < num[i])
                ++ans;
            else if(num[j] == num[i])
            {
                o = i + 1;
                p = j - 1;
                while(o < p)
                {
                    if(num[p] < num[o])
                    {
                        ++ans;
                        break;
                    }
                    else if(num[p] > num[i])
                    {
                        break;
                    }
                    ++o;
                    --p;
                }
            }
        }
    }
    return ans;
}
#pragma endregion

int main()
{
    /*A*/
    // cout << Solution_A() << '\n';



    /*D*/
    
    // string num;
    char num[5000];
    scanf("%s", &num);
    int n = strlen(num);
    cout << Sloution_D(num, n);

    return 0;
}
