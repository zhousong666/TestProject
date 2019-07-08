#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
	string LeftRotateString(string str, int n) {
		string resultStr = str;
		if (str.size() <= 1 || n == 0) return resultStr;
		int strLength = str.size();
		for (int i = 0; i < strLength; ++i) {
			if (i < strLength - n)
				resultStr[i] = str[i + n];
			else {
				resultStr[i] = str[i - strLength + n];
			}
		}
		return resultStr;
	}
};
int main() {
	return 0;
}