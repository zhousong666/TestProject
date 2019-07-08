#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};

class SolutionSerialize {
public:
	char* Serialize(TreeNode *root) {
		if (root == NULL)    return NULL;
		char* tmpChar = new char();

	}
	TreeNode* Deserialize(char *str) {

	}
};
TreeNode* CreatTreeNode() {
	TreeNode* Tree1 = new TreeNode(10);
	TreeNode* Tree2 = new TreeNode(6);
	TreeNode* Tree4 = new TreeNode(8);
	TreeNode* Tree3 = new TreeNode(4);
	TreeNode* Tree5 = new TreeNode(14);
	TreeNode* Tree6 = new TreeNode(12);
	TreeNode* Tree7 = new TreeNode(16);
	Tree1->left = Tree2;
	Tree2->left = Tree3;
	Tree2->right = Tree4;
	Tree1->right = Tree5;
	Tree5->left = Tree6;
	Tree5->right = Tree7;

	return Tree1;
}

class SolutionConvert {
public:

	TreeNode* Convert(TreeNode* pRootOfTree)
	{
		if (pRootOfTree == nullptr) return nullptr;
		TreeNode* pre = nullptr;

		convertHelper(pRootOfTree, pre);

		TreeNode* res = pRootOfTree;
		while (res->left)
			res = res->left;
		return res;
	}

	void convertHelper(TreeNode* cur, TreeNode*& pre)
	{
		if (cur == nullptr) return;

		convertHelper(cur->left, pre);

		cur->left = pre;
		if (pre) pre->right = cur;
		pre = cur;

		convertHelper(cur->right, pre);
	}
};

struct RandomListNode {
int label;
struct RandomListNode *next, *random;
RandomListNode(int x) :
label(x), next(NULL), random(NULL) {
}
};

RandomListNode* CreatList() {
	RandomListNode *Node1 = new RandomListNode(1);
	RandomListNode *Node2 = new RandomListNode(2);

	RandomListNode *Node3 = new RandomListNode(3);

	RandomListNode *Node4 = new RandomListNode(4);
	Node1->next = Node2;
	Node1->random = Node3;
	Node2->next = Node3;
	Node3->next = Node4;

	return Node1;
}

class SolutionCloneNode {
public:
	void CloneNode(RandomListNode* pHead) {
		RandomListNode* pNode = pHead;
		while (pNode != NULL) {
			RandomListNode* pCloned = new RandomListNode(pNode->label);
			pCloned->label = pNode->label;
			pCloned->next = pNode->next;
			pCloned->random = NULL;

			pNode->next = pCloned;
			pNode = pCloned->next;
		}
	}

	void ConnectRandomNodes(RandomListNode* pHead) {
		RandomListNode* pNode = pHead;
		while (pNode != NULL) {
			RandomListNode* pCloned = pNode->next;
			if (pNode->random != NULL) {
				pCloned->random = pNode->random->next;
			}
			pNode = pCloned->next;
		}
	}

	RandomListNode* ReconnectNodes(RandomListNode* pHead) {
		RandomListNode* pNode = pHead;
		RandomListNode* pClonedHead = NULL;
		RandomListNode* pClonedNode = NULL;

		if (pNode != NULL) {
			pClonedHead = pClonedNode = pNode->next;
			pNode->next = pClonedNode->next;
			pNode = pNode->next;
		}

		while (pNode != NULL) {
			pClonedNode = pNode->next;
			pNode->next = pClonedNode->next;
			pNode = pNode->next;
		}
		return pClonedHead;
	}
	RandomListNode* Clone(RandomListNode* pHead)
	{
		CloneNode(pHead);
		ConnectRandomNodes(pHead);
		return ReconnectNodes(pHead);
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

class X {
private:
	int x;
};

class Point2D {
public:

protected:
	float x, y;
};

class Point3D : public virtual Point2D {
public:

protected:
	float z;
};

class Vertex :public virtual Point2D {
public:

protected:
	Vertex *next;
};

class Vertex3D : public Point3D, public Vertex {
public:

protected:
	float numble;
};

class solution {
public:
	double Power(double base, int exponent) {
		if(exponent == 0) return 1;
		if (exponent == 1) return base;
		double result = Power(base, exponent >> 1);
		result *= result;

		if(exponent & 0x01 == 1)
			result *= base;

		return result;
	}
};


class Y : public  virtual X {};
class Z : public virtual X {};
class A : public Y, public Z {};

int main() {
	/*int sizeX = 0, sizeY = 0, sizeZ = 0, sizeA = 0;
	sizeX = sizeof(X);
	cout << "sizeof(x) = " << sizeX << endl;
	sizeY = sizeof(Y);
	cout << "sizeof(y) = " << sizeY << endl;
	sizeZ = sizeof(Z);
	cout << "sizeof(z) = " << sizeZ << endl;
	sizeA = sizeof(A);
	cout << "sizeof(A) = " << sizeA << endl;

	vector<int> test(10, 8);

	vector<int>::iterator iterStart = test.begin();
	vector<int>::iterator iterEnd = test.end();

	solution s;
	double result = s.Power(2, 10);
	Vertex3D v3d;
	Vertex *pv;
	Vertex3D *pv3d;
	Point2D *p2d;
	Point3D *p3d;

	p2d = &v3d;


	pv = &v3d;

	vector <vector<int>> path;
	vector <int> eachPath;
	TreeNode* root = new TreeNode(10);
	root->left = new TreeNode(5);
	root->right = new TreeNode(12);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(7);

	Solution s2;
	path = s2.FindPath(root, 22);*/

	/*SolutionCloneNode SCN;
	RandomListNode* pHead = CreatList();
	RandomListNode* pCloned;
	pCloned = SCN.Clone(pHead);

	int ia[9] = { 0, 1, 2, 3, 4, 8, 9, 3, 5 };
	vector<int> ivec(ia, ia + 9);
	
	make_heap(ivec.begin(), ivec.end());
	for (int i = 0; i < ivec.size(); ++i)
		cout << ivec[i] << "-";*/
	/*SolutionConvert SCT;
	TreeNode* pTree = CreatTreeNode();
	SCT.Convert(pTree);*/
	return 0;

}