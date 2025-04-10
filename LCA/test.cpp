#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional> // 添加此头文件
using namespace std;

// 树节点结构
struct Node 
{
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

#pragma region 暴力算法
// // 查找从根到目标节点的路径
// bool findPath(Node* root, int target, vector<int>& path) 
// {
//     if (!root) return false;
    
//     // 记录当前路径
//     path.push_back(root->val);
    
//     if (root->val == target) return true;
    
//     // 在左右子树中查找
//     if ((root->left && findPath(root->left, target, path)) ||
//         (root->right && findPath(root->right, target, path))) {
//         return true;
//     }
    
//     // 没找到则回溯
//     path.pop_back();
//     return false;
// }

// // 查找LCA主函数
// int findLCA(Node* root, int n1, int n2) 
// {
//     vector<int> path1, path2;
    
//     if (!findPath(root, n1, path1) || !findPath(root, n2, path2)) {
//         return -1; // 节点不存在
//     }
    
//     // 比较两条路径
//     int i;
//     for (i = 0; i < path1.size() && i < path2.size(); i++) {
//         if (path1[i] != path2[i]) break;
//     }
//     return path1[i-1];
// }

#pragma endregion

#pragma region Tarjan算法(离线算法)
unordered_map<pair<Node*, Node*>, Node*> answers;
class TarjanLCA 
{
    unordered_map<Node*, Node*> parent;  // 并查集父指针
    unordered_map<Node*, int> rank;      // 并查集秩
    unordered_map<Node*, bool> visited;  // 访问标记
    unordered_map<Node*, Node*> ancestor;// 祖先记录
    
    // 并查集查找（带路径压缩）
    Node* find(Node* u) 
    {
        if (parent[u] != u) 
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }
    
    // 并查集合并（按秩合并）
    // void unionSet(Node* u, Node* v) 
    // {
    //     Node* rootU = find(u);
    //     Node* rootV = find(v);
    //     if (rootU != rootV) 
    //     {
    //         if (rank[rootU] > rank[rootV]) swap(rootU, rootV);
    //         parent[rootU] = rootV;
    //         if (rank[rootU] == rank[rootV]) rank[rootV]++;
    //     }
    // }
    void unionSet(Node* u, Node* v) 
    {
        parent[v] = u;
    }
    
public:
    void tarjanDFS(Node* u, unordered_map<Node*, vector<Node*>>& queries) 
    {
        parent[u] = u;
        rank[u] = 0;
        // ancestor[u] = u;
        visited[u] = true;
        
        // 递归处理子树
        if (u->left) 
        {
            tarjanDFS(u->left, queries);
            unionSet(u, u->left);
            // ancestor[find(u)] = u;
        }
        if (u->right) 
        {
            tarjanDFS(u->right, queries);
            unionSet(u, u->right);
            // ancestor[find(u)] = u;
        }
        
        // 处理当前节点的查询
        for (Node* v : queries[u]) 
        {
            if (visited[v]) 
            {
                // answers[{u, v}] = ancestor[find(v)];
                answers[{u, v}] = find(v);
            }
        }
    }
};
#pragma endregion


int main() 
{
    // 示例树结构
    //        1
    //      /   \.
    //     2     3
    //    / \   / \.
    //   4  5  6   7
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    
    /*暴力算法*/
    // cout << "LCA(4,5) = " << findLCA(root, 4,5) << endl; // 2
    // cout << "LCA(4,6) = " << findLCA(root, 4,6) << endl; // 1
    // cout << "LCA(3,4) = " << findLCA(root, 3,4) << endl; // 1

    /*Tarjan算法*/
    TarjanLCA tar;
    unordered_map<Node*, vector<Node*>> queries;
    queries[root->left->left].push_back(root->left->right);// 4 5
    queries[root->left->right].push_back(root->left->left);// 5 4
    queries[root->left->left].push_back(root->right->left);// 4 6
    queries[root->right->left].push_back(root->left->left);// 6 4

    tar.tarjanDFS(root, queries);
    cout << answers[{root->left->right, root->left->left}]->val;
    cout << answers[{root->right->left, root->left->left}]->val;

    

    return 0;
}
