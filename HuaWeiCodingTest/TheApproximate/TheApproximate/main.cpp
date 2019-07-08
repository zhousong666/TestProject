#include <iostream>

using namespace std;

int main() {

	float tmp;
	cin >> tmp;
	int result = 0;
	if ((tmp * 10 - int(tmp) * 10) < 5) result = int(tmp);
	else result = int(tmp) + 1;
	cout << result;
	return 0;
}