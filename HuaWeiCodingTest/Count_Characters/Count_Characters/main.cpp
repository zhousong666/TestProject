#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {

	string str;
	char singlechar;
	getline(cin, str);
	cin >> singlechar;
	int result = 0;
	singlechar = toupper(singlechar);
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == singlechar) ++result;
	}
	cout << result;
	return 0;
}

