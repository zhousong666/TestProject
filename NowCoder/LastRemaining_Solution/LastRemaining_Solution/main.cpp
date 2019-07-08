#include <iostream>

using namespace std;

class Solution {
public:
	int LastRemaining_Solution(int n, int m)
	{
		int count = n;
		int doom = m;
		int alive = count;
		int number = 0;
		int index = 0;
		bool *circle = NULL;
		circle = (bool *)calloc(sizeof(bool *), count);
		while (alive > 0) {
			number += 1 - circle[index];
			if (number == doom) {
				circle[index] = 1;
				--alive;
				number = 0;
			}
			index = (index + 1) % count;
		}
		return index - 1;
	}
};

int main() {
	return 0;
}