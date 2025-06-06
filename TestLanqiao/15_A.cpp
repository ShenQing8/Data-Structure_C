#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <limits>
#include <stack>
//#include <bits/stdc++.h>
using namespace std;

#pragma region 艺术与篮球
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
#pragma endregion

#pragma region 五子棋对弈
class FiveChess
{
public:
    FiveChess()
    {
        board = vector<vector<bool>>(5, vector<bool>(5,0));
    }
    void check()
    {
        int r_sum = 0;
        int c_sum = 0;
        // 横 竖
        for(int i = 0; i < 5; ++i)
        {
            for(int j = 0; j < 5; ++j)
            {
                r_sum += board[i][j];
                c_sum += board[j][i];
            }
            if(r_sum % 5 == 0 || c_sum % 5 == 0)
                return;
            r_sum = c_sum = 0;
            // r_sum = 0;
            // c_sum = 0;
        }
        // 主对角线 副对角线
        for(int i = 0; i < 5; ++i)
        {
            r_sum += board[i][i];
            c_sum += board[i][4 - i];
        }
        if(r_sum % 5 == 0 || c_sum % 5 == 0)
            return;
        // 无人获胜
        ++ans;
    }
    void dfs(int num, int w_num)
    {
        if(w_num > 13) // 剪枝
            return;
        if(num == 25)
        {
            if(w_num == 13)
                check();
            return;
        }
        board[num / 5][num % 5] = 1;// 在此处下白棋
        dfs(num + 1, w_num + 1);
        board[num / 5][num % 5] = 0;// 在此处下黑棋
        dfs(num + 1, w_num);
    }

    // int num = 0;
    // int w_num = 0;
    int ans = 0;
    vector<vector<bool>> board;
};
#pragma endregion

#pragma region 训练士兵
struct  solder
{
    long long p,c;
};

long long TrainSolder()
{
    long long sum = 0;// 所需金币数
    long long n = 0;
    long long S = 0;
    cin >> n >> S;
    solder a[n];
    // vector<long long> p(n, 0);// 单次训练所需金币
    // vector<long long> c(n, 0);// 每个士兵所需训练的次数
    long long sig_sum = 0;// 单次需要训练总和

    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].p >> a[i].c;
    }
    sort(a, a+n, [](solder &n1, solder &n2) {
        return n1.c < n2.c;
      });

    int min_index = 1;
    for(int i = n - 1; i > -1; --i)
    {
        sig_sum += a[i].p;
        if(sig_sum >= S)
        {
            min_index = i;
            break;
        }
    }

    sum += a[min_index].c * S;
    for(int i = min_index + 1; i < n; ++i)
    {
        sum += (a[i].c - a[min_index].c) * a[i].p;
    }

    // 返回结果
    return sum;
}
#pragma endregion

#pragma region 团建
struct TreeNode
{
    int num;
    vector<TreeNode*> sons;
    TreeNode(){}
    TreeNode(int n) : num(n){}
    TreeNode(int n, int x) : num(n)
    {
        sons = vector<TreeNode*>(x, nullptr);
    }
};
class DSolution
{
public:
    void TuanJian()
    {
        int n, m;
        cin >> n >> m;
        int input = 0;
        for(int i = 1; i < n + 1; ++i)
        {
            cin >> input;
            t1[i] = TreeNode(input);
        }
        for(int i = 1; i < m + 1; ++i)
        {
            cin >> input;
            t2[i] = TreeNode(input);
        }

        int k, v;
        for(int i = 0; i < n - 1; ++i)
        {
            cin >> k >> v;
            t1[min(k,v)].sons.emplace_back(&t1[max(k,v)]);
        }
        for(int i = 0; i < m - 1; ++i)
        {
            cin >> k >> v;
            t2[min(k,v)].sons.emplace_back(&t2[max(k,v)]);
        }
        dfs(t1[1], t2[1], 0);
    }
    void dfs(TreeNode& tt1, TreeNode& tt2, int count)
    {
        if(tt1.num != tt2.num)
            return;
        ans = max(ans, count + 1);
        for(int i = 0; i < tt1.sons.size(); ++i)
        {
            for(int j = 0; j < tt2.sons.size(); ++j)
            {
                dfs(*tt1.sons[i], *tt2.sons[j], count + 1);
            }
        }
    }

    int count = 0;
    int ans = 0;
    TreeNode t1[200005];
    TreeNode t2[200005];
};
#pragma endregion

#pragma region 成绩统计（未成功）
// 求平均数
// 排序当前数组，并用 二分查找 找到最接近平均数的数
// 从这个数开始 向两边遍历 ，取接近平均数的那个数作为下一个数

// 二分查找
int bin_search(vector<int>& scor, int length, double pingjun)
{
    double chazhi1;
    double chazhi2;
    int left = 0;
    int right = length;
    int mid = left + (right - left) / 2;
    while(left < right)
    {
        mid = left + (right - left) / 2;
        if(scor[mid] < pingjun)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    chazhi1 = scor[left] - pingjun;
    chazhi2 = pingjun - scor[left - 1];
    return chazhi1 < chazhi2 ? left : left - 1;
}
int ESolution(vector<int>& scor, int n, int k, int T)
{
    double pingjun = 0;
    double tmp;
    double fangcha;
    int mid, l, r;
    for(int i = 0; i < k - 1; ++i)
    {
        pingjun += (double)((scor[i] - pingjun) / (i + 1));// 求前k个数的平均数
    }
    for(int i = k - 1; i < n; ++i)
    {
        pingjun += (double)((scor[i] - pingjun) / (i + 1));// 求平均数

        // for(int j = 0; j <= i; ++j)
        // {
        //     tmp += (scor[j] - revo) * (scor[j] - revo);
        // }
        // fangcha = tmp / (i + 1);// 方差
        sort(scor.begin(), scor.begin() + i + 1);// 排序，方便二分查找
        l = bin_search(scor, i, pingjun);// 二分查找
        r = l + 1;
        // revo_k = 0;
        // for(int m = 0; m < k; ++m)
        // {
        //     chazhi1 = fangcha - scor[l];
        //     chazhi2 = scor[r] - fangcha;
        //     if(chazhi1 < chazhi2)
        //     {
        //         mid = l;
        //         --l;
        //     }
        //     else
        //     {
        //         mid = r;
        //         ++r;
        //     }
        //     // revo_k += (double)((scor[fangcha - scor[l] < scor[r] - fangcha ? l-- : r++] - revo_k) / (m + 1));
        //     revo_k += (double)((scor[mid] - revo_k) / (m + 1));
        // }

        // 求方差
        tmp = 0;
        for(int m = 0; m < k; ++m)
        {
            if(l >= 0 && pingjun - scor[l] < scor[r] - pingjun)
            {
                mid = l;
                --l;
            }
            else if(r <= i && pingjun - scor[l] >= scor[r] - pingjun)
            {
                mid = r;
                ++r;
            }
            tmp += (scor[mid] - pingjun) * (scor[mid] - pingjun);
        }
        fangcha = tmp / k;

        if(fangcha < T)
        {
            return i + 1;
        }
    }
    return -1;
}
#pragma endregion



#pragma region 零食采购：离线算法
struct TreeNode_G
{
    int kind;
    bool is_came = false;
    vector<TreeNode_G*> sons;
};

class LCA
{
    TreeNode_G* find(TreeNode_G* u)
    {
        if(u == parent[u])
            return u;
        return find(u);
    }
    void marge(TreeNode_G* u, TreeNode_G* v)
    {
        parent[v] = u;
    }
public:
    // bool dfs_g(TreeNode_G& root, TreeNode_G& target, vector<TreeNode_G*>& path)
    // {
    //     if(root.is_came)
    //         return false;
    //     // 记录路径
    //     path.push_back(&root);
    //     root.is_came = true;
    //
    //     if(&root == &target)
    //     {
    //         root.is_came = false;
    //         return true;
    //     }
    //
    //     for(int i = 0; i < root.sons.size(); ++i)
    //     {
    //         if(dfs_g(*root.sons[i], target, path))
    //         {
    //             root.is_came = false;
    //             return true;
    //         }
    //     }
    //
    //     // 删除路径
    //     path.pop_back();
    //     root.is_came = false;
    //
    //     return false;
    // }
    
    unordered_map<TreeNode_G*, bool> vis;
    unordered_map<TreeNode_G*, TreeNode_G*> parent;
    vector<int> ans;

    int LCA_G(TreeNode_G* root, unordered_map<TreeNode_G*, pair<vector<TreeNode_G*>, int>>& beg_end)
    {
        parent[root] = root;// 将父节点设为自己
        vis[root] = true;// 记录已访问

        for(TreeNode_G* v : root->sons)
        {
            if(!v->is_came)
            {
                LCA_G(v, beg_end);
                marge(root, v);
            }
        }

        for(TreeNode_G* v : beg_end[root].first)
        {
            if(v->is_came)
            {
                cout << find(v)->kind;
            }
        }
        
        // vector<TreeNode_G*> path1, path2;
        // unordered_map<int, int> tmp;
        // // 找不到公共节点
        // if(!dfs_g(root, n1, path1) || !dfs_g(root, n2, path2))
        //     return 0;
        //
        // int i = 0;
        // for(i = 0; i < path1.size() && i < path2.size(); ++i)
        // {
        //     if(!(path1[i] == path2[i]))
        //         break;
        // }
        // int coparent_index = i - 1;
        //
        // for(i = coparent_index; i < path1.size(); ++i)
        // {
        //     ++tmp[path1[i]->kind];
        // }
        // for(i = coparent_index + 1; i < path2.size(); ++i)
        // {
        //     ++tmp[path2[i]->kind];
        // }
        //
        // return tmp.size();
    }
};

#pragma endregion

#pragma region 零食采购：倍增算法
int snacks[100005][21];
int fa[100005][21];
int dep[100005];
vector<int> sons[100005];

void dfs_beizeng(int s, int f)
{
    // 将从根节点到父节点能买到的零食都加到子结点上
    for(int i = 1; i < 21; ++i)
    {
        snacks[s][i] += snacks[f][i];
    }

    dep[s] = dep[f] + 1;
    fa[s][0] = f;
    for(int i = 1; (1<<i) < dep[s] && i <= 20; ++i)
    {
        fa[s][i] = fa[ fa[s][i-1] ][i-1];// 找到s的2的i次方祖先
    }

    // 继续dfs
    for(int i = 0; i < sons[s].size(); ++i)
    {
        if(sons[s][i] != f)// 因为建立了双向边
        {
            dfs_beizeng(sons[s][i], s);
        }
    }
}

int lca_beizeng(int u, int v)
{
    // 保证v的深度更大
    if(dep[u] > dep[v])
        swap(u, v);
    // 将v的深度跳到和u一样
    for(int i = 20; i >= 0; --i)
    {
        if(dep[fa[v][i]] >= dep[u])
        {
            v = fa[v][i];
        }
    }
    // 若为相同节点，则直接返回
    if(u == v)
        return u;
    // 找到lca的子节点
    for(int i = 20; i >= 0; --i)
    {
        if(fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
#pragma endregion

int main()
{
#pragma region 
    /*A*/
    // int bsk_days = BasketDays();
    // cout << bsk_days << endl;

    /*B*/
    // FiveChess chess;
    // chess.dfs(0, 0);
    // cout << chess.ans << endl;

    /*C*/
    // cout << TrainSolder() << endl;

    /*D*/
    // DSolution ddd;
    // ddd.TuanJian();
    // cout << ddd.ans << endl;

    /*E*/
    // int n, k, T;
    // cin >> n >> k >> T;
    // vector<int> scor(n);
    // for(int i = 0; i < n; ++i)
    //     cin >> scor[i];
    // int ans = ESolution(scor, n, k, T);
    // cout << ans;

    /*F*/
#pragma endregion
    /*G : 离线算法*/
    // LCA lca;
    // int n,q;
    // int u,v;
    // cin >> n >> q;
    // vector<TreeNode_G> planets(n + 1);// 行星
    // lca.ans = vector<int>(q, 0);
    // unordered_map<TreeNode_G*, pair<vector<TreeNode_G*>, int>> beg_end;// 起点和终点
    // for(int i = 1; i <= n; ++i)
    // {
    //     cin >> planets[i].kind;
    //     lca.vis[&planets[i]] = false;
    // }
    // for(int i = 1; i < n; ++i)
    // {
    //     cin >> u >> v;
    //     planets[u].sons.emplace_back(&planets[v]);
    //     planets[v].sons.emplace_back(&planets[u]);
    // }
    // for(int i = 0; i < q; ++i)
    // {
    //     cin >> u >> v;
    //     beg_end[&planets[u]].first.emplace_back(&planets[v]);
    //     beg_end[&planets[u]].second = i;
    //
    //     beg_end[&planets[v]].first.emplace_back(&planets[u]);
    //     beg_end[&planets[u]].second = i;
    // }
    //
    // // for(int i = 0; i < q; ++i)
    // // {
    // //     cout << LCA_G(planets[1], planets[beg_end[i][0]], planets[beg_end[i][1]]) << '\n';
    // // }
    // lca.LCA_G(&planets[1], beg_end);

    /*G : 倍增算法*/

    /*G : 倍增算法*/
    int n, q;
    int x, u, v;
    int ans = 0;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
    {
        cin >> x;
        snacks[i][x] = 1;
    }
    for(int i = 1; i < n; ++i)
    {
        cin >> u >> v;
        sons[u].emplace_back(v);
        sons[v].emplace_back(u);
    }

    // 初始化
    dfs_beizeng(1, 0);

    while(q--)
    {
        cin >> u >> v;
        // 最短线路能买到的零食数量最多 = 从根节点到u节点能买到的数量 + 从根节点到v节点能买到的数量
        //                            - 从根节点到lca能买到的数量 - 从根节点到lca的父节点能买到的数量
        int sotest = lca_beizeng(u, v);
        for(int i = 1; i <= 20; ++i)
        {
            if(snacks[u][i] + snacks[v][i] - snacks[sotest][i] - snacks[fa[sotest][0]][i])
                ++ans;
        }
        cout << ans << '\n';
        ans = 0;
    }
    
    return 0;
}
