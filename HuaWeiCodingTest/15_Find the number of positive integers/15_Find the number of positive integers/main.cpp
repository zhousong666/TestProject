#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	int num = 0;
	while (cin >> num) {
		int result = 0;
		while (num) {
			if (num & 0x01) ++result;
			num = num >> 1;
		}
		cout << result;
	}
	return 0;
}