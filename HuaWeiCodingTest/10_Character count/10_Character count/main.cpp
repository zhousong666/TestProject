#include <iostream>
#include <string>
using namespace std;

int main() {
	string str;
	int arr[128] = {0};
	int result = 0;
	while (getline(cin, str)) {
		for (int i = 0; i < str.size(); ++i) {
			++arr[int(str[i])];
		}
		for (int i = 0; i < 128; ++i) {
			if (arr[i]) ++result;
		}
		cout << result;
	}
	return 0;
}