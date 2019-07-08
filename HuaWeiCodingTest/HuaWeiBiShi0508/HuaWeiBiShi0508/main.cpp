#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int line_num = 0;
	int rotate_num = 0;
	cin >> line_num;

	vector<vector<int>> arr(line_num);
	
	int tmp_in = 0;
	for (int i = 0; i < line_num; ++i) {
		for (int j = 0; j < line_num; ++j) {
			cin >> tmp_in;
			arr[i].push_back(tmp_in);
		}
	}
	vector<vector<int>> result(arr);
	while (cin>> rotate_num) {
		int rotate_num_last = rotate_num % 4;
		if (rotate_num_last == 1) {
			for (int i = 0; i < line_num; ++i) {
				for (int j = 0; j < line_num; ++j) {
					result[j][line_num - 1 - i] = arr[i][j];
				}
			}
		}
		else if (rotate_num_last == 2) {

		}
		else if (rotate_num_last == 3) {
			for (int i = 0; i < line_num; ++i) {
				for (int j = 0; j < line_num; ++j) {
					result[line_num - 1 - j][i] = arr[i][j];
				}
			}
		}
		else if (rotate_num_last == 4) {

		}
		cout << arr[0][0] << endl;

	}
	
	return 0;
}