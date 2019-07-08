#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int lineNum;
	while (scanf("%d", &lineNum) != EOF) {
		vector<int> emptyBottleNum(lineNum);
		vector<int> result(lineNum);
		
		for (int i = 0; i < lineNum; ++i) {
			cin >> emptyBottleNum[i];
		}

		std::sort(emptyBottleNum.begin(), emptyBottleNum.end());

		int pre_num = emptyBottleNum[0];
		result[0] = pre_num;
		int resultCount = 1;
		for (int i = 1; i < lineNum; ++i) {
			if (emptyBottleNum[i] == pre_num) continue;
			else {
				result[resultCount] = emptyBottleNum[i];
				pre_num = emptyBottleNum[i];
				++resultCount;
			}
		}
		for (int i = 0; i < resultCount; ++i) {
			cout << result[i] << endl;
		}
	}
	

	
	return 0;
}