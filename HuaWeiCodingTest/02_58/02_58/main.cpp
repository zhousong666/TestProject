#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n = 0, k = 0;
	cin >> n >> k;
	vector<char> arr;
	int result = 0;
	for (int i = 0; i < n; ++i)
		arr.push_back('*');
	for (int i = 0; i < k - 1; ++i)
		arr.push_back('|');
	do {
		result++;
	}while(next_permutation(arr.begin(), arr.end()));
	cout << result << endl;
	do {
		for (int i = 0; i < k + n - 1; ++i) {
			cout << arr[i];
		}
		cout << endl;
		result++;
	} while (next_permutation(arr.begin(), arr.end()));

	


	return 0;
}