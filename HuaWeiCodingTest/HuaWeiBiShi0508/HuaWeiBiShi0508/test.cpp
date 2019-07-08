#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <limits>
using namespace std;

void split(char *p, vector<int> &v) {
	char *tmp = strtok(p, " ");
	while (tmp) {
		v.push_back(atoi(tmp));
		tmp = strtok(NULL, " ");
	}
}

int main() {
	int M = 0;
	int g = 0;
	cin >> g;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<vector<int> > matrix;
	vector<vector<int> > r_matrix;
	for (int i = 0; i < g; ++i) {
		string s;
		vector<int> v;
		getline(cin, s);
		split(const_cast<char*>(s.c_str()), v);
		matrix.push_back(v);
	}
	cin >> M;
	for (int i = 0; i < g; ++i) {
		vector<int> v;
		for (int j = 0; j < g; ++j) {
			v.push_back(0);
		}
		r_matrix.push_back(v);
	}
	for (int i = 0; i < g; ++i) {
		for (int j = 0; j < g; ++j) {
			r_matrix[i][j] = matrix[i][j];
		}
	}
	while (M != 0) {
		matrix = r_matrix;
		int num = 0;
		for (int col = 0; col < g; ++col) {
			for (int row = g - 1; row >= 0; --row) {
				int r_col = num % g;
				int r_row = num / g;
				r_matrix[r_row][r_col] = matrix[row][col];
				num++;
			}
		}
		M--;
	}
	for (auto v : r_matrix) {
		for (auto n : v) {
			cout << n << " ";
		}
		cout << endl;
	}
	return 0;

}