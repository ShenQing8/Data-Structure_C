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
