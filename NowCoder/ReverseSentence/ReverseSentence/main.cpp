#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class Solution {
public:
	string ReverseSentence(string str) {
		auto size = str.size();
		if (size == 0) return "";
		int mark = 0;
		str += ' ';
		for (int i = 0; i < size + 1; ++i) {
			if (str[i] == ' ') {
				ReverseWord(str, mark, i - 1);
				mark = i + 1;
			}
		}
		str = str.substr(0, size);
		ReverseWord(str, 0, size - 1);
		return str;
	}
	void ReverseWord(string &str, int l, int r) {
		while (l < r) {
			swap(str[l], str[r]);
			++l;
			--r;
		}
	}
};
int main() {
	Solution s;
	s.ReverseSentence("hello world i am a boy");
	return 0;
}