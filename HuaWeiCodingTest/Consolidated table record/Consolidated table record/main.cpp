#include <iostream>
//#include <vector>
#include <map>
using namespace std;

int main() {
	int lineNum = 0;
	int key, value;
	map<int, int> Table;
	while(cin >> lineNum) {
		for (int i = 0; i < lineNum; ++i) {
			cin >> key >> value;
			if (!Table[key]) Table[key] = value;
			else Table[key] += value;
		}
		map<int, int>::iterator it = Table.begin();
		for (; it != Table.end(); ++it) {
			cout << it->first << ' ' << it->second << endl;
		}

		
	}
	
	return 0;
}