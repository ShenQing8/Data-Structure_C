#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode():left(nullptr), right(nullptr){}
    TreeNode(int a):val(a), left(nullptr), right(nullptr){}
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

int main()
{
    
    return 0;
}
