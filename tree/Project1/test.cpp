#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
};

/*层序遍历*//* 时间复杂度：O(n)  空间复杂度：O(n)*/
// 层序遍历本质上属于广度优先遍历（breadth-first traversal）
// 也称广度优先搜索（breadth-first search, BFS），它体现了一种“一圈一圈向外扩展”的逐层遍历方式。
vector<int> levelOrder(TreeNode* root)
{
	queue<TreeNode*> node;
	node.push(root);// 入队
	vector<int> val;
	while (!node.empty())
	{
		TreeNode* n = node.front();// 读取
		node.pop();                // 出队
		val.push_back(n->val);
		// 入队
		if (n->left)
			node.push(n->left);
		if (n->right)
			node.push(n->right);
	}
	return val;
}

// 相应地，前序、中序和后序遍历都属于深度优先遍历（depth-first traversal）
// 也称深度优先搜索（depth-first search, DFS），它体现了一种“先走到尽头，再回溯继续”的遍历方式。

/*前序遍历*//* 时间复杂度：O(n)  空间复杂度：O(n)*/
vector<int> pre_vec;
void preOrder(TreeNode* node)
{
	if (node)
	{
		// 遍历顺序：根节点-->左子树-->右子树
		pre_vec.push_back(node->val);
		preOrder(node->left);
		preOrder(node->right);
	}
}
/*中序遍历*/
vector<int> in_vec;
void inOrder(TreeNode* node)
{
	if (node)
	{
		// 遍历顺序：左子树-->根节点-->右子树
		inOrder(node->left);
		in_vec.push_back(node->val);
		inOrder(node->right);
	}
}
/*后序遍历*/
vector<int> post_vec;
void postOrder(TreeNode* node)
{
	if (node)
	{
		// 遍历顺序：左子树-->右子树-->根节点
		postOrder(node->left);
		postOrder(node->right);
		post_vec.push_back(node->val);
	}
}
int main()
{
	TreeNode n1(1);
	TreeNode n2(2);
	TreeNode n3(3);
	TreeNode n4(4);
	TreeNode n5(5);
	TreeNode n6(6);
	TreeNode n7(7);

	n1.left = &n2;
	n1.right = &n3;
	n2.left = &n4;
	n2.right = &n5;
	n3.left = &n6;
	n3.right = &n7;

	vector<int> tree_val = levelOrder(&n1);
	preOrder(&n1);
	inOrder(&n1);
	postOrder(&n1);

	return 0;
}
