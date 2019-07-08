#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int num_of_lines = 0;
	

	while(cin >> num_of_lines){
		vector<int> vec_int(num_of_lines);
		for (int i = 0; i < num_of_lines; ++i) {
			cin  >>  vec_int[i];
		}
		sort(vec_int.begin(), vec_int.end());
		int unique_num_of_lines = unique(vec_int.begin(), vec_int.end()) - vec_int.begin();//unique函数返回一个指向区间的尾端
		for (int i = 0; i < unique_num_of_lines; ++i) {
			cout << vec_int[i] << endl;
		}
	}
	
	return 0;
}