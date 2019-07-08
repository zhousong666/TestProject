#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		//if(input.size() == 0 || k <= 0) return NULL;
		sort(input.begin(), input.end());
		vector<int> result;
		int pre_num = input[0];
		result.push_back(input[0]);
		int countK = 1;
		vector<int>::iterator iter = input.begin();
		++iter;
		for (; iter != input.end(); ++iter) {
			if (*iter != pre_num) {
				pre_num = *iter;
				++countK;
				result.push_back(*iter);
			}
			if (countK == 3) return result;
		}
		return result;
	}
};
int main() {
	vector<int> vec = {  };
	vector<int> result;
	Solution S;
	result = S.GetLeastNumbers_Solution(vec, 3);
	return 0;
}