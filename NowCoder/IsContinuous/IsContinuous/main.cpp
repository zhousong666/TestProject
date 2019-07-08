#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
	bool IsContinuous(vector<int> numbers) {
		if (numbers.size() < 5) return false;
		int count[14] = {0};
		int maxNum = -1;
		int minNum = 14;
		for (int i = 0; i < numbers.size(); ++i) {
			count[numbers[i]]++;
			if (numbers[i] == 0) continue;
			if (count[numbers[i]] > 1) return false;
			if (numbers[i] > maxNum) maxNum = numbers[i];
			if (numbers[i] < minNum) minNum = numbers[i];
		}
		if ((maxNum - minNum) < 5) return true;
		return false;
	}
};
int main() {
	Solution s;
	vector<int> test = { 0,3,2,6,4 };
	bool result = s.IsContinuous(test);
	return 0;
}