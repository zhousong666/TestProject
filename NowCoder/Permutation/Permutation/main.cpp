#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<string> Permutation(string str) {
		vector<string> answer;
		if (str.empty())
			return answer;
		sort(str.begin(), str.end());
		cout << str.c_str() << endl;
		do {
			answer.push_back(str);
			cout << str.c_str() << endl;
		} while (next_permutation(str.begin(), str.end()));
		return answer;
	}
};

int main() {
	string str = "abcd";
	vector<string> answer;
	Solution S1;
	answer = S1.Permutation(str);
	return 0;
}