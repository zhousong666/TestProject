#include <iostream>
#include <string>
using namespace std;

int main() {
	string str;

	while (cin >> str) {
		char direction;
		int x = 0, y = 0;
		int index = 0;
		for (int i = 0; i < str.size(); ++i) {
			switch (index)
			{
				case 0:
					if (str[i] == 'A' || str[i] == 'S' || str[i] == 'D' || str[i] == 'W') {
						if (i == 0) {
							index = 1;
							direction = str[i];
						}
						else if (str[i - 1] == ';'){
							index = 1;
							direction = str[i];
						}

						
					}
					else {
						index = 0;
					}
					break;
				case 1:
					if (str[i]>= '0' && str[i] <= '9') {
						index = 2;
					}
					else {
						index = 0;
					}
					break;
				case 2:
					if (str[i] >= '0' && str[i] <= '9') {
						index = 3;
					}
					else if (str[i] == ';') {
						if (direction == 'A') {
							x = x - int(str[i - 1] - '0');
						}
						else if (direction == 'S') {
							y = y - int(str[i - 1] - '0');
						}
						else if (direction == 'D') {
							x = x + int(str[i - 1] - '0');
						}
						else if (direction == 'W') {
							y = y + int(str[i - 1] - '0');
						}
						index = 0;
					}
					else {
						index = 0;
					}
					break;
				case 3:  //移动100以内步数
					if (str[i] == ';') {
						if (direction == 'A') {
							x = x - int(str[i - 2] - '0') * 10 - int(str[i - 1] - '0');
						}else if (direction == 'S') {
							y = y - int(str[i - 2] - '0') * 10 - int(str[i - 1] - '0');
						}
						else if (direction == 'D') {
							x = x + int(str[i - 2] - '0') * 10 + int(str[i - 1] - '0');
						}
						else if (direction == 'W') {
							y = y + int(str[i - 2] - '0') * 10 + int(str[i - 1] - '0');
						}
					
						index = 0;
					}
					break;
				default:
					break;
			}
		}
		cout << x << ',' << y <<endl;
	}
	return 0;
}