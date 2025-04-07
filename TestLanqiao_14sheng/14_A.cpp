#include <iostream>
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

int main()
{
    /*A*/
    cout << Solution_A() << '\n';


    return 0;
}
