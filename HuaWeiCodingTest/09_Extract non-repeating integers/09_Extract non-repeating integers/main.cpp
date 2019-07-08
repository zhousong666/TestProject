#include <iostream>

using namespace std;

int main() {

	int tmp = 0;
	int result = 0;
	int arr[10] = { 0 };
	while (cin >> tmp) {
		while (tmp) {
			int diwei = tmp % 10;
			tmp = tmp / 10;
			if (arr[diwei] == 0) {
				++arr[diwei];
				result = result * 10 + diwei;
			}
		}
		cout << result;
	}
	return 0;
}