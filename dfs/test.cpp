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

/*构建树*/
TreeNode* dfsTree(vector<int> &preorder, unordered_map<int, int> inordermap, int i, int l, int r)
{
    // 当节点数不足 1 时，返回空指针
    if(r < l)
        return nullptr;
    // 初始化根节点
    TreeNode* root = new TreeNode(preorder[i]);
    // 在 inorder 中找到根节点
    int m = inordermap[preorder[i]];
    // 构建左子树
    root->left = dfsTree(preorder, inordermap, i + 1, l, m - 1);
    // 构建右子树
    root->right = dfsTree(preorder, inordermap, i + 1 + m - l, m + 1, r);
    // 返回根节点
    return root;
}
TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder)
{// 根据前序遍历和中序遍历构建树
    // 初始化哈希表，存储 inorder 中的映射
    unordered_map<int, int> inordermap;
    for(int i = 0; i < inorder.size(); ++i)
        inordermap[inorder[i]] = i;
    TreeNode* root = dfsTree(preorder, inordermap, 0, 0, preorder.size() - 1);
    return root;
}

/*汉诺塔*/
void move(vector<int>& scr, vector<int>& tar)
{
    tar.emplace_back(scr.back());
    scr.pop_back();
}
void dfsHanota(int n, vector<int>& scr, vector<int>& buf, vector<int>& tar)
{
    if(n == 1)
    {
        move(scr, tar);
        return;
    }
    // 子问题一：借助 tar 将 scr 上的圆盘移到 buf 上
    dfsHanota(n-1, scr, tar, buf);
    move(scr, tar);
    // 子问题二：借助 scr 将 buf 上的圆盘移到 tar 上
    dfsHanota(n-1, buf, scr, tar);

}
void solveHanota(vector<int>& A, vector<int>& B, vector<int>& C)
{
    int n = A.size();
    // 借助B将A的n个圆盘移到C
    dfsHanota(n, A, B, C);
}

int main()
{
    /*构建树*/
    vector<int> preorder = {3,9,2,1,7};
    vector<int> inorder = {9,3,1,2,7};
    TreeNode* root = buildTree(preorder, inorder);

    /*汉诺塔*/
    // vector<int> A = {5,4,3,2,1};
    // vector<int> B;
    // vector<int> C;
    // solveHanota(A, B, C);

    return 0;
}
