#include "AVLtree.h"

/*��ȡ�ڵ�߶�*/
int height(TreeNode* node)
{
	// �սڵ�Ϊ -1 ��Ҷ�ڵ�Ϊ 0
	return node == nullptr ? -1 : node->height;
}
/*���½ڵ�߶�*/
void updateHeight(TreeNode* node)
{
	if (node == nullptr)
		return;
	node->height = max(height(node->left), height(node->right)) + 1;
}
/*��ȡ�ڵ�ƽ������*/
int balanceFactor(TreeNode* node)
{
	// ƽ������Ϊ��ڵ�߶ȼ�ȥ�ҽڵ�߶ȣ������жϸýڵ��Ƿ�ƽ��
	// ����սڵ��ƽ��߶�Ϊ 0
	if (node == nullptr)
		return 0;
	return height(node->left) - height(node->right);
}

// ��ƽ�����ӵľ���ֵ���� 1 �Ľڵ��Ϊʧ��ڵ�
// ����ʧ������Ĳ�ͬ����ת������Ϊ����������������������������������������

/*����*/
TreeNode* rightRotate(TreeNode* node)
{
	// �����ӽڵ㣺�ڵ����ڵ�
	TreeNode* child = node->left;
	// ������ڵ㣺�ӽڵ���ҽڵ�
	TreeNode* grandchild = child->right;

	// �� node Ϊԭ�㣬������ת
	node->left = grandchild;
	child->right = node;

	// ���½ڵ�߶�
	updateHeight(node);
	updateHeight(child);

	// ������ת�������ĸ��ڵ�
	return child;
}

/*����*/
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

/*��ת��ѡ��*/
// �ڵ�ƽ������   �ӽڵ��ƽ������    ��ת����
//   > 1(��ƫ��)       > 0              ���� 
//   > 1(��ƫ��)       < 0           ������������
//  < -1(��ƫ��)       < 0              ����
//  < -1(��ƫ��)       > 0           ������������
TreeNode* rotate(TreeNode* node)
{
	// ��ȡƽ������
	int _balanceFactor = balanceFactor(node);
	// ��ƫ��
	if (_balanceFactor > 1)
	{
		// ����
		if (balanceFactor(node->left) >= 0)
			return rightRotate(node);
		// ������������
		else
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
	}
	// ��ƫ��
	if (_balanceFactor < -1)
	{
		// ����
		if (balanceFactor(node->right) <= 0)
			return leftRotate(node);
		// ������������
		else
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}
	// ƽ������������ת��ֱ�ӷ���
	return node;
}

/*���ҽ��*/
// ��������������ҷ���һ��
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

// ����ڵ���ɾ���ڵ�����Ͷ�������������
// ���Ƕ��˲�ѯ�ڵ�߶Ȳ�ƽ��������Ĳ���

/*����ڵ�*/
TreeNode* insertHelper(TreeNode* root, int val)
{
	if (root == nullptr)// �����սڵ㣬ֱ�ӿ��ٿռ䲢����
		return new TreeNode(val);
	// �ݹ����ڵ�
	if (val < root->val)
		root->left = insertHelper(root->left, val);
	else if (val > root->val)
		root->right = insertHelper(root->right, val);
	else // ��ͬ�ڵ㲻���ӣ�ֱ�ӷ���
		return root;

	// ���¶��ϲ�ѯ�ڵ�ƽ������
	updateHeight(root);
	// ִ����ת������ʹ�����ָ�ƽ��
	root = rotate(root);
	return root;
}
void insert(TreeNode* root, int val)
{
	root = insertHelper(root, val);
}


/*ɾ���ڵ�*/
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
		// Ҫɾ���Ľڵ��Ϊ 0 �� 1
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
		// Ҫɾ���Ľڵ��Ϊ 2 
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

	// ���½ڵ�߶Ȳ���ѯƽ������
	updateHeight(root);
	// ��ת������ʹ�䱣��ƽ��
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
