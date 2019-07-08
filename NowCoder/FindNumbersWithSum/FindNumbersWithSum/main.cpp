#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum) {
		vector<int> result;
		if (array.size() <= 1) return result;
		int product = INT_MAX;
		int numA = 0, numB = 0;
		bool isResult = false;
		for (int i = 0; i < array.size() - 1; ++i) {
			for (int j = i + 1; j < array.size(); ++j) {
				if ((array[i] + array[j]) == sum) {
					if ((array[i] * array[j]) < product) {
						numA = array[i];
						numB = array[j];
						product = numA * numB;
						isResult = true;
					}
				}
			}
		}
		if (isResult) {
			result.push_back(numA);
			result.push_back(numB);
		}
		return result;
	}
};
int main() {
	Solution temSolution;
	vector<int> testVec = { 1,4,5,6,7,8,9 };
	vector<int> resultVec;
	resultVec = temSolution.FindNumbersWithSum(testVec, 10);
	return 0;
}