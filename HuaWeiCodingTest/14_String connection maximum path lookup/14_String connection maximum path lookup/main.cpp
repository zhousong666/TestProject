#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main() {
	int length = 0;
	vector<string> vec_str;
	while (cin >> length) {

		for (int i = 0; i < length; ++i) {
			string tmp;
			cin >> tmp;
			vec_str.push_back(tmp);
		}
		sort(vec_str.begin(), vec_str.end());
		for (vector<string>::iterator it = vec_str.begin(); it != vec_str.end(); ++it) {
			cout << *it << endl;
		}
		system("pause");
	}
	return 0;
}