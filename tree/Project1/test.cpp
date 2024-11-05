#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*�������Ľڵ�*/
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
};


/*�������*//* ʱ�临�Ӷȣ�O(n)  �ռ临�Ӷȣ�O(n)*/
// ����������������ڹ�����ȱ�����breadth-first traversal��
// Ҳ�ƹ������������breadth-first search, BFS������������һ�֡�һȦһȦ������չ������������ʽ��
vector<int> levelOrder(TreeNode* root)
{
	queue<TreeNode*> node;
	node.push(root);// ���
	vector<int> val;
	while (!node.empty())
	{
		TreeNode* n = node.front();// ��ȡ
		node.pop();                // ����
		val.push_back(n->val);
		// ���
		if (n->left)
			node.push(n->left);
		if (n->right)
			node.push(n->right);
	}
	return val;
}

// ��Ӧ�أ�ǰ������ͺ������������������ȱ�����depth-first traversal��
// Ҳ���������������depth-first search, DFS������������һ�֡����ߵ���ͷ���ٻ��ݼ������ı�����ʽ��

/*ǰ�����*//* ʱ�临�Ӷȣ�O(n)  �ռ临�Ӷȣ�O(n)*/
vector<int> pre_vec;
void preOrder(TreeNode* node)
{
	if (node)
	{
		// ����˳�򣺸��ڵ�-->������-->������
		pre_vec.push_back(node->val);
		preOrder(node->left);
		preOrder(node->right);
	}
}
/*�������*/
vector<int> in_vec;
void inOrder(TreeNode* node)
{
	if (node)
	{
		// ����˳��������-->���ڵ�-->������
		inOrder(node->left);
		in_vec.push_back(node->val);
		inOrder(node->right);
	}
}
/*�������*/
vector<int> post_vec;
void postOrder(TreeNode* node)
{
	if (node)
	{
		// ����˳��������-->������-->���ڵ�
		postOrder(node->left);
		postOrder(node->right);
		post_vec.push_back(node->val);
	}
}

/*������*/
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


/*����������������*/
TreeNode* search(TreeNode* root, int num)
{
	// ����ֲ�������
	TreeNode* cur = root;
	while (cur)
	{
		if (num < cur->val)
			cur = cur->left;
		else if (num > cur->val)
			cur = cur->right;
		else
			// �ҵ�������ѭ��
			break;
	}
	// �ҵ��򷵻ص�ַ��û�ҵ��򷵻� NULL
	return cur;
}
/*����������������*/
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
		if (cur->val == num)// �����������в�������ֵͬ�Ľڵ�
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
/*������������ɾ��*/
void remove(TreeNode* root, int num)
{
	if (root == nullptr)
		return;
	TreeNode* cur = root, * pre = nullptr;
	// �ҵ���ɾ���Ľڵ�
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
	// ���޴�ɾ���Ľڵ㣬ֱ�ӷ���
	if (cur == nullptr)
		return;
	// Ҫɾ���Ľڵ�������������Ϊ0��1��2
	// ��Ϊ0��1
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
		else// ��ɾ���Ľڵ��Ǹ��ڵ�
		{
			root = child;
		}
		// �ͷ��ڴ�
		delete cur;
	}
	// ��Ϊ2
	// ����ɾ���ڵ�Ķ�Ϊ 2 ʱ�������޷�ֱ��ɾ����������Ҫʹ��һ���ڵ��滻�ýڵ�
	// ����Ҫ���ֶ����������������� < ���ڵ� < ��������������
	// �������ڵ����������������С�ڵ�������������ڵ㡣
	else
	{
		// �ҵ���ɾ������������ҵ���һ��ֵ
		TreeNode* tmp = cur->right;
		while (tmp->left)
			tmp = tmp->left;
		// ����ɾ�����滻�ڵ�
		int tmpVal = tmp->val;
		remove(tmp, tmpVal);
		// �滻��ɾ������ֵ
		cur->val = tmpVal;
	}
}

/*����������*/
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
