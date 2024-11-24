#include "AVLtree.h"


/*AVL ��*/
int main()
{
	vector<int> inputNums = { 2,1,5,9,6,3,4,18,16,1,35,51,23 };
	TreeNode* root = buildAVLTree(inputNums);

	return 0;
}
