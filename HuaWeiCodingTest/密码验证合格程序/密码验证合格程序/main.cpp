#include<iostream>
#include<string>

using namespace std;

int main() {
	string str;

	while (cin >> str) {
		if (str.length() < 8) {
			cout << "NG" << endl;
			continue;
		}
		int count_daxie = 0, count_xiaoxie = 0, count_num = 0, count_other_char = 0;
		for (int i = 0; i < str.size(); ++i) {
			if (int(str[i]) >= int('a') && int(str[i]) <= int('z')) count_xiaoxie = 1;
			else if (int(str[i]) >= int('A') && int(str[i]) <= int('Z')) count_daxie = 1;
			else if (int(str[i]) >= int('0') && int(str[i]) <= int('9')) count_num = 1;
			else count_other_char = 1;

		}
		if ((count_daxie + count_xiaoxie + count_num + count_other_char) >=3) {
			for (int i = 0; i < str.size() - 2; ++i) {
				string sub_str = str.substr(i, 3);
				string other_str = str.substr(i + 3);
				string::size_type position;
				position = other_str.find(sub_str);
				if(position != str.npos){
					cout << "NG" << endl;
					break;
				}

			}
			cout << "OK" << endl;
			continue;
		}else {
			cout << "NG" << endl;
			continue;
		}
		
	}
	return 0;
}