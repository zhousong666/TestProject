#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

void spliteByFenhao(vector<string> &vec_str, string str)
{
	string temp;
	auto it = str.begin();
	while (*it) {
		auto iter = it;
		for (; iter != str.end(); iter++)
		{
			if (*iter == ';') {
				it = iter + 1;
				break;
			}
			temp += *iter;
		}
		vec_str.push_back(temp);
		temp.clear();
		if (iter == str.end())break;
	}
}

typedef struct {
	int x;
	int y;
}Point2D;

int main()
{
	string inStr;
	while (cin >> inStr) {
		vector<string > vec_str;
		spliteByFenhao(vec_str, inStr);
		Point2D point = { 0,0 };
		for (auto e : vec_str) {
			//A5;
			if (e.length() == 2) {
				switch (e[0]) {
				case 'A':
					point.x -= strtol(e.substr(1, 1).c_str(), NULL, 10); break;
				case 'D':
					point.x += strtol(e.substr(1, 1).c_str(), NULL, 10); break;
				case 'W':
					point.y += strtol(e.substr(1, 1).c_str(), NULL, 10); break;
				case 'S':
					point.y -= strtol(e.substr(1, 1).c_str(), NULL, 10); break;
				default:
					break;
				}
			}
			//A10;
			if (e.length() == 3) {
				switch (e[0]) {
				case 'A':
					point.x -= strtol(e.substr(1, 2).c_str(), NULL, 10); break;
				case 'D':
					point.x += strtol(e.substr(1, 2).c_str(), NULL, 10); break;
				case 'W':
					point.y += strtol(e.substr(1, 2).c_str(), NULL, 10); break;
				case 'S':
					point.y -= strtol(e.substr(1, 2).c_str(), NULL, 10); break;
				default:
					break;
				}
			}
		}
		cout << point.x << ',' << point.y << endl;
	}
}