#include<iostream>
#include<string>
#include <math.h>

using namespace std;

int main() {
	string input;
	
	while (getline(cin, input)) {
		int a = 0;
		for (int i = 2; i < input.size(); ++i) {
			int dishu = 0;
			if (input[i] >= 'A')
				dishu = input[i] - 'A' + 10;
			else dishu = input[i] - '0';
			a += dishu * pow(16, input.size() - i - 1);
			
		}
		cout << a <<endl;
	}
	
	return 0;
}