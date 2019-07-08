#include <iostream>
#include <stack>
#include <vector>
#include <queue>

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
	vector<int> PrintFromTopToBottom(TreeNode* root) {
		if (!root) return vec;
		deque<TreeNode*> treeDeque;
		treeDeque.push_back(root);
		while (!treeDeque.empty()) {
			TreeNode* tmp = treeDeque.front();
			treeDeque.pop_front();
			vec.push_back(tmp->val);
			if (tmp->left) treeDeque.push_back(tmp->left);
			if (tmp->right) treeDeque.push_back(tmp->right);
		}
		return vec;
	}
private:
	vector<int> vec;


};

int main() {

	return 0;
}