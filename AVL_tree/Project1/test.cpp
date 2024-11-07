#include <iostream>
#include <vector>
using namespace std;

/* AVL 树节点类 */
struct TreeNode {
	int val{};          // 节点值
	int height = 0;     // 节点高度
	TreeNode* left{};   // 左子节点
	TreeNode* right{};  // 右子节点
	TreeNode() = default;
	explicit TreeNode(int x) : val(x) {}
};

/*获取节点高度*/
int height(TreeNode* node)
{
	// 空节点为 -1 ，叶节点为 0
	return node == nullptr ? -1 : node->height;
}
/*更新节点高度*/
void updateHeight(TreeNode* node)
{
	if (node == nullptr)
		return;
	node->height = max(height(node->left), height(node->right)) + 1;
}
/*获取节点平衡因子*/
int balanceFactor(TreeNode* node)
{
	// 平衡因子为左节点高度减去右节点高度，用来判断该节点是否平衡
	// 定义空节点的平衡高度为 0
	if (node == nullptr)
		return 0;
	return height(node->left) - height(node->right);
}

// 将平衡因子的绝对值大于 1 的节点称为失衡节点
// 根据失衡情况的不同，旋转操作分为：右旋、左旋、先右旋再左旋、先左旋再右旋

/*右旋*/
TreeNode* rightRotate(TreeNode* node)
{
	// 定义子节点：节点的左节点
	TreeNode* child = node->left;
	// 定义孙节点：子节点的右节点
	TreeNode* grandchild = child->right;

	// 以 node 为原点，向右旋转
	node->left = grandchild;
	child->right = node;

	// 更新节点高度
	updateHeight(node);
	updateHeight(child);

	// 返回旋转后子树的根节点
	return child;
}

/*左旋*/
TreeNode* leftRotate(TreeNode* node)
{
	TreeNode* child = node->right;
	TreeNode* grandchild = child->left;

	node->right = grandchild;
	child->left = node;

	updateHeight(node);
	updateHeight(child);

	return child;
}

/*旋转的选择*/
// 节点平衡因子   子节点的平衡因子    旋转类型
//   > 1(左偏树)       > 0              右旋 
//   > 1(左偏树)       < 0           先左旋再右旋
//  < -1(右偏树)       < 0              左旋
//  < -1(右偏树)       > 0           先右旋再左旋
TreeNode* rotate(TreeNode* node)
{
	// 获取平衡因子
	int _balanceFactor = balanceFactor(node);
	// 左偏树
	if (_balanceFactor > 1)
	{
		// 右旋
		if (balanceFactor(node->left) >= 0)
			return rightRotate(node);
		// 先左旋再右旋
		else
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
	}
	// 右偏树
	if (_balanceFactor < -1)
	{
		// 左旋
		if (balanceFactor(node->right) <= 0)
			return leftRotate(node);
		// 先右旋再左旋
		else
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}
	// 平衡树，无需旋转，直接返回
	return node;
}

/*查找结点*/
// 与二叉搜索树查找方法一致
TreeNode* search(TreeNode* root, int val)
{
	while (root)
	{
		if (val < root->val)
			root = root->left;
		else if (val > root->val)
			root = root->right;
		else
			break;
	}
	return root;
}

// 插入节点与删除节点操作和二叉搜索树类似
// 但是多了查询节点高度并平衡二叉树的操作

/*插入节点*/
TreeNode* insertHelper(TreeNode* root, int val)
{
	if (root == nullptr)// 遇到空节点，直接开辟空间并返回
		return new TreeNode(val);
	// 递归插入节点
	if (val < root->val)
		root->left = insertHelper(root->left, val);
	else if (val > root->val)
		root->right = insertHelper(root->right, val);
	else // 相同节点不添加，直接返回
		return root;

	// 自下而上查询节点平衡因子
	updateHeight(root);
	// 执行旋转操作，使子树恢复平衡
	root = rotate(root);
	return root;
}
void insert(TreeNode* root, int val)
{
	root = insertHelper(root, val);
}


/*删除节点*/
TreeNode* removeHelper(TreeNode* root, int val)
{
	if (root == nullptr)
		return nullptr;
	if (val < root->val)
		root->left = removeHelper(root->left, val);
	else if (val > root->val)
		root->right = removeHelper(root->right, val);
	else
	{
		// 要删除的节点度为 0 或 1
		if (root->left == nullptr || root->right == nullptr)
		{
			TreeNode* child = root->left == nullptr ? root->right : root->left;
			//delete root;
			//return child;
			if (child == nullptr)
			{
				delete root;
				return nullptr;
			}
			else
			{
				delete root;
				root = child;
			}
		}
		// 要删除的节点度为 2 
		else
		{
			TreeNode* tmp = root->right;
			while (tmp->left)
				tmp = tmp->left;

			int tmpVal = tmp->val;
			root->val = tmpVal;
			root->right = removeHelper(root->right, tmpVal);
		}
	}

	// 更新节点高度并查询平衡因子
	updateHeight(root);
	// 旋转子树，使其保持平衡
	return rotate(root);
}
void remove(TreeNode* root, int val)
{
	root = removeHelper(root, val);
}

TreeNode* buildAVLTree(vector<int>& inputNums)
{
	TreeNode* root = NULL;
	for (int data : inputNums)
		root = insertHelper(root, data);
	return root;
}

/*AVL 树*/
int main()
{
	vector<int> inputNums = { 2,1,5,9,6,3,4,18,16,1,35,51,23 };
	TreeNode* root = buildAVLTree(inputNums);

	return 0;
}
