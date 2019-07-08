#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:

	bool IsPopOrder(vector<int> pushV, vector<int> popV) {
		
		stack<int> s1;
		for (size_t i = 0; i < pushV.size(); ++i) {
			s1.push(pushV[i]);
			difajofji(s1, popV);
		}
		return result;
	}
	void difajofji(stack<int> &s1, vector<int> popV) {
		if (s1.top() == popV[popVIndex]) {
			s1.pop();
			popVIndex++;
			if (s1.size() == 0) {
				result = true;
				return;
			}
			if (s1.size() != 0) {
				if (s1.top() == popV[popVIndex]) difajofji(s1, popV);
			}
			
		}
	}
private:
	int popVIndex = 0;
	bool result = false;
};

int main() {
	vector<int> v1 = { 1,2,3,4,5 };
	vector<int> v2 = { 4,5,3,2,1 };
	Solution s1;
	bool r = s1.IsPopOrder(v1, v2);
	return 0;
}
