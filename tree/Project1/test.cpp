#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*二叉树的节点*/
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

/*二叉树*/
//int main()
//{
//	TreeNode n1(1);
//	TreeNode n2(2);
//	TreeNode n3(3);
//	TreeNode n4(4);
//	TreeNode n5(5);
//	TreeNode n6(6);
//	TreeNode n7(7);
//
//	n1.left = &n2;
//	n1.right = &n3;
//	n2.left = &n4;
//	n2.right = &n5;
//	n3.left = &n6;
//	n3.right = &n7;
//
//	vector<int> tree_val = levelOrder(&n1);
//	preOrder(&n1);
//	inOrder(&n1);
//	postOrder(&n1);
//
//	return 0;
//}


/*二叉搜索树：查找*/
TreeNode* search(TreeNode* root, int num)
{
	// 与二分查找类似
	TreeNode* cur = root;
	while (cur)
	{
		if (num < cur->val)
			cur = cur->left;
		else if (num > cur->val)
			cur = cur->right;
		else
			// 找到则跳出循环
			break;
	}
	// 找到则返回地址，没找到则返回 NULL
	return cur;
}
/*二叉搜索树：插入*/
void insert(TreeNode* root, int num)
{
	if (root == nullptr)
	{
		root = new TreeNode(num);
		return;
	}
	TreeNode* cur = root, *pre = nullptr;
	while (cur)
	{
		if (cur->val == num)// 二叉搜索树中不存在相同值的节点
			return;
		pre = cur;
		if (num < cur->val)
			cur = cur->left;
		else if (num > cur->val)
			cur = cur->right;
	}

	TreeNode* node = new TreeNode(num);
	if (num < pre->val)
		pre->left = node;
	else
		pre->right = node;
}
/*二叉搜索树：删除*/
void remove(TreeNode* root, int num)
{
	if (root == nullptr)
		return;
	TreeNode* cur = root, * pre = nullptr;
	// 找到待删除的节点
	while(cur)
	{
		if (num == cur->val)
			break;
		pre = cur;
		if (num < cur->val)
			cur = cur->left;
		else
			cur = cur->right;
	}
	// 若无待删除的节点，直接返回
	if (cur == nullptr)
		return;
	// 要删除的节点分三种情况：度为0、1、2
	// 度为0或1
	if (cur->left == nullptr || cur->right == nullptr)
	{
		TreeNode* child = cur->left != nullptr ? cur->left : cur->right;
		if (cur != root)
		{
			if (pre->left == cur)
				pre->left = child;
			else
				pre->right = child;
		}
		else// 若删除的节点是根节点
		{
			root = child;
		}
		// 释放内存
		delete cur;
	}
	// 度为2
	// 当待删除节点的度为 2 时，我们无法直接删除它，而需要使用一个节点替换该节点
	// 由于要保持二叉搜索树“左子树 < 根节点 < 右子树”的性质
	// 因此这个节点可以是右子树的最小节点或左子树的最大节点。
	else
	{
		// 找到待删除结点的中序查找的下一个值
		TreeNode* tmp = cur->right;
		while (tmp->left)
			tmp = tmp->left;
		// 迭代删除被替换节点
		int tmpVal = tmp->val;
		remove(tmp, tmpVal);
		// 替换待删除结点的值
		cur->val = tmpVal;
	}
}

/*二叉搜索树*/
int main()
{
	//TreeNode n1(1);
	//TreeNode n2(2);
	//TreeNode n3(3);
	TreeNode n4(4);
	//TreeNode n5(5);
	//TreeNode n6(6);
	//TreeNode n7(7);

	TreeNode* root = &n4;
	insert(root, 2);
	insert(root, 3);
	insert(root, 1);
	insert(root, 6);
	insert(root, 5);
	insert(root, 7);


	return 0;
}
