#include <iostream>
#include <deque>

using namespace std;


struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};

class Solution {
public:
	int index = 0;
	TreeNode* KthNode(TreeNode* pRoot, int k)
	{
		if (pRoot != NULL) {
			TreeNode* node = KthNode(pRoot->left, k);
			if (node != NULL)
				return node;
			index++;
			if (index == k)
				return pRoot;
			node = KthNode(pRoot->right, k);
			if (node != NULL)
				return node;
		}
		return NULL;
	}

};

int main() {

	TreeNode *tree1 = new TreeNode(5);
	TreeNode *tree2 = new TreeNode(3);
	TreeNode *tree3 = new TreeNode(7);
	TreeNode *tree4 = new TreeNode(2);
	TreeNode *tree5 = new TreeNode(4);
	TreeNode *tree6 = new TreeNode(6);
	TreeNode *tree7 = new TreeNode(8);
	tree1->left = tree2;
	tree1->right = tree3;
	tree2->left = tree4;
	tree2->right = tree5;
	tree3->left = tree6;
	tree3->right = tree7;

	Solution s;
	TreeNode *result;
	result = s.KthNode(tree1, 3);
	return 0;
}