#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.size() == 0) return false;
		vector<int> leftVec;
		vector<int> rightVec;
		int root = sequence[sequence.size() - 1];
		int i = 0;
		for (i = 0; i < sequence.size() - 1; ++i) {
			if (sequence[i] > root) break;
			else leftVec.push_back(sequence[i]);
		}

		for (int j = i; j < sequence.size() - 1; ++j) {
			if (sequence[j] < root) return false;
			else rightVec.push_back(sequence[j]);
		}

		bool left = true;
		if (i > 0)
			left = VerifySquenceOfBST(leftVec);

		bool right = true;
		if (i < sequence.size() - 1)
			right = VerifySquenceOfBST(rightVec);

		return (left&&right);


	}
};

int main() {
	vector<int> testVec = { 7, 4, 6, 5};
	Solution s;
	bool result = s.VerifySquenceOfBST(testVec);
	return 0;
}