#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	char input[100];
	
	std::cin.getline(input, 100);
	
	int konggeNum = 0;
	vector<char> newChar;
	for (int i = 0; i < 100; ++i) {
		if (int(input[i]) > 0 && int(input[i]) < 128)  newChar.push_back(input[i]);
		if (input[i] == ' ')  ++konggeNum;
	}
	int N = 0; 
	N = int(newChar[0]) - 48;
	vector<vector<char>>  twoChar(konggeNum);
	int charIndex = 0;
	for (int i = 2; i < newChar.size(); ++i) {
		if (newChar[i] == ' ')  ++charIndex;
		else twoChar[charIndex].push_back(newChar[i]);
	}
	char zero = '0';
	int resultLines = 0;
		
	for (int i = 0; i < konggeNum; ++i) {
		sort(twoChar[i].begin(), twoChar[i].end());
		int zeroNum = 8 - (twoChar[i].size() % 8);
		if (twoChar[i].size() % 8 == 0) --zeroNum;
		
		while (zeroNum--)  twoChar[i].push_back(zero);
		resultLines += twoChar[i].size() / 8;
		
	}
	vector<vector<char>>  result(resultLines);
	sort(twoChar.begin(), twoChar.end());
	int resultIndex = 0;
	for (int i = 0; i < N; ++i) {
		int eightSize = twoChar[i].size() / 8 ;
		for (int j = 0; j < eightSize; ++j) {
			for (int k = 0; k < 8; ++k) {
				result[resultIndex].push_back(twoChar[i][j * 8 + k]);
			}
			++resultIndex;		
		}
	}
	sort(result.begin(), result.end());
	for (int i = 0; i < resultIndex; ++i) {
		for (int j = 0; j < 8; ++j){ 
			cout << result[i][j]; 
		}
		if(i < resultIndex -1)
			cout << ' ';
	}
	return 0;
}