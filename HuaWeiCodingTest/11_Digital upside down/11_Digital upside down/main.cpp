#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
	int num = 0;
	while (cin >> num) {
		stringstream sfs;
		string str;
		sfs << num;
		sfs >> str;
		reverse(str.begin(), str.end());
		str = str;
		cout << str;

	}
	return 0;
}