#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int main() {
	string s1;
	string s2;
	cin >> s1;
	cin >> s2;

	vector<char> vec_str;
	int len_s1_8bit = ceil(s1.size() / 8.0);
	int len_s2_8bit = ceil(s2.size() / 8.0);
	const char* c1 = s1.c_str();
	const char* c2 = s2.c_str();
	for (int i = 0; i < len_s1_8bit; ++i) {
		for (int j = 0; j < 8; ++j ) {
			if (c1[i * 8 + j] != '\0') {
				vec_str.push_back(c1[i * 8 + j]);
			}
			else {
				for (; j < 8; ++j)
					vec_str.push_back('0');
			}
		}
	}
	for (int i = 0; i < len_s2_8bit; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (c2[i * 8 + j] != '\0') {
				vec_str.push_back(c2[i * 8 + j]);
			}
			else {
				for (; j < 8; ++j)
					vec_str.push_back('0');
			}
		}
	}
	for (int i = 0; i < vec_str.size(); ++i) {
		cout << vec_str[i];
		if (i % 8 == 7) cout << endl;
	}
	return 0;
}