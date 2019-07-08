#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string str;
	while (getline(cin, str)) {
		reverse(str.begin(), str.end());
		string::iterator it_begin = str.begin();
		string::iterator it_end = str.begin();
		for (; it_end != str.end(); ++it_end) {
			if (*it_end == ' ') {
				reverse(it_begin, it_end);
				it_begin = ++(it_end);
			}
		}
		reverse(it_begin, str.end());
		cout << str;
	}
	return 0;
}