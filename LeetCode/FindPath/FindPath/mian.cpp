#include <iostream>
#include <vector>

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
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
		if (root) {
			vector<int> eachPath;
			vector<vector<int>> allPath;
			int currSum = 0;
			dfs(root, expectNumber, eachPath, allPath, currSum);

			return allPath;
		}
	}
	void dfs(TreeNode* root, int expectNumber, vector<int> & eachPath, vector < vector<int >> &allPath, int currSum) {
		currSum += root->val;
		eachPath.push_back(root->val);

		if (root->left == NULL && root->right == NULL) {
			if (currSum == expectNumber)  allPath.push_back(eachPath);
		}

		if (root->left != NULL) {
			dfs(root->left, expectNumber, eachPath, allPath, currSum);
		}

		if (root->right != NULL) {
			dfs(root->right, expectNumber, eachPath, allPath, currSum);
		}

		eachPath.pop_back();
	}
};