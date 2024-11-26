#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
// #include "../AVL_tree/Project1/AVLtree.h"
using namespace std;

struct TreeNode {
	int val{};
	TreeNode* left{};
	TreeNode* right{};
	TreeNode() = default;
	explicit TreeNode(int x) : val(x) {}
};

/*回溯算法框架*/
// 在以下框架代码中，state 表示问题的当前状态，choices 表示当前状态下可以做出的选择
// void backtrack(State* state, vector<Choice*> choices, vector<State*>& res)
// {
//     // 判断是否为解
//     if(isSolution(state))
//     {
//         // 记录解
//         recordeSolution(state, res);
//         // 不再继续搜索（按需保留或删除）
//         return;
//     }
//     // 遍历所有选择
//     for(Choice* choice: choices)
//     {
//         // 剪枝：判断选择是否合法
//         if(isValid(choice))
//         {
//             // 尝试：做出选择，更新状态
//             makeChoice(state, choice);
//             // 继续下一轮循环
//             bacetrack(state, choice, res);
//             // 回退：撤销选择，恢复到之前的状态
//             undoChioce(state, choice);
//         }
//     }
// }

/*回溯算法：在二叉树中搜索所有值为 7 的节点，请返回根节点到这些节点的路径，并要求路径中不包含值为 3 的节点。*/
// 状态 state 为节点遍历路径，选择 choices 为当前节点的左子节点和右子节点，结果 res 是路径列表
bool isSolution(vector<TreeNode*>& state){
    return !state.empty() && state.back()->val == 7;
}

void resortSolution(vector<TreeNode*>& state, vector<vector<TreeNode*>>& res){
    res.emplace_back(state);
}

bool isValid(TreeNode* choice){
    return choice != nullptr && choice->val != 3;
}

void makeChoice(vector<TreeNode*>& state, TreeNode* choice){
    state.emplace_back(choice);
}

void undoChoice(vector<TreeNode*> state){
    state.pop_back();
}

void backtrack_schNode(vector<TreeNode*>& state, vector<TreeNode*>& choices, vector<vector<TreeNode*>>& res)
{
    // 判断是否为解
    if(isSolution(state))
    {
        // 记录解
        resortSolution(state, res);
        // 此处题目不需要return，查到一个解后可继续向下查找
    }
    // 遍历所有选择
    for(TreeNode* choice: choices)
    {
        // 剪枝：判断选择是否合法
        if(isValid(choice))
        {
            // 尝试：做出选择，更新状态
            makeChoice(state, choice);
            // 继续下一轮循环
            vector<TreeNode*> nextChoices = {choice->left, choice->right};
            backtrack_schNode(state, nextChoices, res);
            // 回退：撤销选择，恢复之前的状态
            undoChoice(state);
        }
    }
}

/*全排列Ⅰ：无重复元素*/
void backtrack_pl1(vector<int>& state, vector<int>& choices, vector<bool>& selected, vector<vector<int>>& res)
{
    // 判断是否为解
    if(state.size() == choices.size())
    {
        res.emplace_back(state);
        return;
    }
    // 遍历所有选择
    for(int i = 0; i < choices.size(); ++i)
    {
        // 剪枝
        if(!selected[i])
        {
            // 尝试
            selected[i] = true;
            state.emplace_back(choices[i]);
            // 继续下一轮循环
            backtrack_pl1(state, choices, selected, res);
            // 回溯
            selected[i] = false;
            state.pop_back();
        }
    }
}
vector<vector<int>> permutations1(vector<int> &nums)
{
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack_pl1(state, nums, selected, res);
    return res;
}



/*全排列Ⅱ：有重复元素*/
void backtrack_pl2(vector<int>& state, vector<int>& choices, vector<bool>& selected, vector<vector<int>>& res)
{
    // 判断是否为解
    if(state.size() == choices.size())
    {
        res.emplace_back(state);
        return;
    }
    // 遍历所有选择
    unordered_set<int> duplicated;
    for(int i = 0; i < choices.size(); ++i)
    {
        // 剪枝
        if(!selected[i] && duplicated.find(choices[i]) == duplicated.end())
        {
            // 尝试
            selected[i] = true;
            duplicated.emplace(choices[i]);
            state.emplace_back(choices[i]);
            // 继续下一轮循环
            backtrack_pl2(state, choices, selected, res);
            // 回溯
            selected[i] = false;
            state.pop_back();
        }
    }
}
vector<vector<int>> permutations2(vector<int> &nums)
{
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack_pl2(state, nums, selected, res);
    return res;
}



/*子集和Ⅰ：无重复元素*/
void backtrack_zj1(vector<int>& state, vector<int>& choices, vector<vector<int>>& res, int start, int target)
{
    // 判断是否为解
    if(target == 0)
    {
        res.emplace_back(state);
        return;
    }
    // 遍历所有选择
    // 剪枝1：从start开始遍历，避免重复数组
    for(int i = start; i < choices.size(); ++i)
    {
        // 剪枝2：若子集超过target，则不再继续
        if(target - choices[i] < 0)
            break;
        
        // 尝试
        state.emplace_back(choices[i]);
        // 进行下一轮循环
        backtrack_zj1(state, choices, res, i, target - choices[i]);
        // 回溯
        state.pop_back();
    }
}
vector<vector<int>> subsetSumINaive1(vector<int>& nums, int target)
{
    vector<int> state;
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    int start = 0;
    backtrack_zj1(state, nums, res, start, target);
    return res;
}


/*子集和Ⅱ：有重复元素*/
void backtrack_zj2(vector<int>& state, vector<int>& choices, vector<vector<int>>& res, int start, int target)
{
    // 判断是否为解
    if(target == 0)
    {
        res.emplace_back(state);
        return;
    }
    // 遍历所有选择, 剪枝Ⅰ：剪去顺序不同但元素相同的子集
    for(int i = start; i < choices.size(); ++i)
    {
        // 剪枝Ⅱ：若子集超过target，则直接跳出循环
        // 因为数组已经排过序，若当前已超过target，则之后必然也超过
        if(target - choices[i] < 0)
            break;
        // 剪枝Ⅲ：剪去重复元素
        if(i > start && choices[i] == choices[i-1])
            continue;
        // 尝试
        state.emplace_back(choices[i]);
        // 进行下一轮循环
        // 剪枝Ⅳ：（i + 1 操作）不允许重复选择同一元素
        backtrack_zj2(state, choices, res, i + 1, target - choices[i]);
        // 回溯
        state.pop_back();
    }
}
vector<vector<int>> subsetSumINaive2(vector<int>& nums, int target)
{
    vector<int> state;
    sort(nums.begin(), nums.end());// 排序，防止重复子集
    int start = 0;// 定义起始位置
    vector<vector<int>> res;
    backtrack_zj2(state, nums, res, start, target);
    return res;
}


/*N皇后问题*/
void backtrack_nQueens(vector<vector<string>>& state, vector<vector<vector<string>>>& res, vector<bool>& cols, 
vector<bool>& digs1, vector<bool>& digs2, int row, int n)
{
    // 判断是否为解
    if(row == n)
    {
        res.emplace_back(state);
        return;
    }
    // 遍历所有选择
    for(int i = 0; i < n; ++i)// i为列， row为行
    {
        // 剪枝
        if(cols[i] || digs1[row - i + n - 1] || digs2[row + i])
            continue;
        // 尝试
        state[row][i] = "Q";
        cols[i] = digs1[row - i + n - 1] = digs2[row + i] = true;
        // 进行下一轮循环
        backtrack_nQueens(state, res, cols, digs1, digs2, row + 1, n);
        // 回溯
        state[row][i] = "#";
        cols[i] = digs1[row - i + n - 1] = digs2[row + i] = false;
    }
}
vector<vector<vector<string>>> nQueens(int n)
{
    // 初始化棋盘：‘Q’代表皇后，‘#’代表棋盘
    vector<vector<string>> state(n, vector<string>(n, "#"));
    vector<bool> cols(n, false);// 列
    vector<bool> digs1(2 * n - 1, false);// row - col = k 的对角线
    vector<bool> digs2(2 * n - 1, false);// row + col = k 的对角线
    vector<vector<vector<string>>> res;
    backtrack_nQueens(state, res, cols, digs1, digs2, 0, n);
    return res;
}
void print_chessboard(vector<vector<vector<string>>>& board)
{
    int n = board.size();// 层数
    int m = board[0].size();// 行、列数
    for(int i = 0; i < n; ++i)
    {
        // 打印一层
        for(int r = 0; r < m; ++r)
        {
            // 打印一行
            for(int c = 0; c < m; ++c)
            {
                // 打印此行中的 c 列
                cout << board[i][r][c] << ' ';
            }
            cout << endl;
        }
        cout << "\n\n";
    }
}



int main()
{
    // TreeNode n1(1);
    // TreeNode n2(7);
    // TreeNode n3(3);
    // n1.left = &n2;
    // n1.right = &n3;
    // TreeNode n4(4);
    // TreeNode n5(5);
    // n2.left = &n4;
    // n2.right = &n5;
    // TreeNode n6(6);
    // TreeNode n7(7);
    // n3.left = &n6;
    // n3.right = &n7;
    // TreeNode n8(7);
    // n4.left = &n8;
    // vector<TreeNode*> state;
    // vector<TreeNode*> choices = {&n1};
    // vector<vector<TreeNode*>> res;
    // backtrack_schNode(state, choices, res);

    /*全排列Ⅰ：无重复元素*/
    vector<int> pl_nums1 = {1,2,3};
    vector<vector<int>> pl_res1 = permutations1(pl_nums1);

    /*全排列Ⅱ：有重复元素*/
    vector<int> pl_nums2 = {1,3,2,3};
    vector<vector<int>> pl_res2 = permutations2(pl_nums2);

    /*子集和Ⅰ：无重复元素*/
    vector<int> zj_nums1 = {3,4,5};
    vector<vector<int>> zj_res1 = subsetSumINaive1(zj_nums1, 9);

    /*子集和Ⅱ：有重复元素*/
    vector<int> zj_nums2 = {4,4,5,3};
    vector<vector<int>> zj_res2 = subsetSumINaive2(zj_nums2, 9);

    /*N皇后问题*/
    vector<vector<vector<string>>> nQ_res = nQueens(4);
    print_chessboard(nQ_res);

    return 0;
}
