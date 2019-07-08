/*#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int in_num = 0;

	cin >> in_num;

	vector<string> str_push;
	vector<string> str_pop;
	for (int i = 0; i < in_num; ++i) {
		string tmp;
		string tmp2;
		cin >> tmp;
		str_push.push_back(tmp);
		cin >> tmp2;
		str_pop.push_back(tmp2);
		vector<char> temp;
		for (int j = 0, k = 0; j < tmp.size();) {
			temp.push_back(tmp[j++]);
			while (k < tmp2.size() && temp.back() == tmp2[k]) {
				temp.pop_back();
				k++;
			}
		}
		if (temp.empty() == true) {
			cout << "Y" << endl;
		}
		else
			cout << "N" << endl;
	}
	return 0;
}*/

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

int main() {
	int in_num = 0;

	cin >> in_num;

	for (int i = 0; i < in_num; ++i) {
		string tmp;
		long result = 0;
		cin >> tmp;
		reverse(tmp.begin(), tmp.end());
		for (int j = 0; j < tmp.size(); ++j) {
			if (int(tmp[j]) >= int('0') && int(tmp[j]) <= int('9')) {
				int num = int(tmp[j]) - int('0');
				result = result + num * pow(24, j);
			}else if (int(tmp[j]) >= int('a') && int(tmp[j]) <= int('z')) {
				int num = int(tmp[j]) - int('a');
				result = result + num * pow(24, j);
			}
		}
		cout << result << endl;
	}
	return 0;
}