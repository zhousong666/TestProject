#include <iostream>
#include <string>

using namespace std;

int main() {
	string str;
	int result = 0;
	getline(cin, str);
	//cout << str << endl;
	//cout << str.size();
	for (int i = str.size() - 1; i >= 0; --i) {
		if (str[i] != ' ') ++result;
		else break;
	}
	cout << result;
	return 0;
}