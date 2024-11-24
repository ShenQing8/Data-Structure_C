#pragma once
#include <iostream>
#include <vector>
using namespace std;

// #ifndef AVLtree_H
// #define AVLtree_H

/* AVL ���ڵ��� */
struct TreeNode {
	int val{};          // �ڵ�ֵ
	int height = 0;     // �ڵ�߶�
	TreeNode* left{};   // ���ӽڵ�
	TreeNode* right{};  // ���ӽڵ�
	TreeNode() = default;
	explicit TreeNode(int x) : val(x) {}
};

int height(TreeNode* node);

void updateHeight(TreeNode* node);

int balanceFactor(TreeNode* node);

TreeNode* rightRotate(TreeNode* node);

TreeNode* leftRotate(TreeNode* node);

TreeNode* rotate(TreeNode* node);

TreeNode* search(TreeNode* root, int val);

TreeNode* insertHelper(TreeNode* root, int val);
void insert(TreeNode* root, int val);

TreeNode* removeHelper(TreeNode* root, int val);
void remove(TreeNode* root, int val);

TreeNode* buildAVLTree(vector<int>& inputNums);

// #endif