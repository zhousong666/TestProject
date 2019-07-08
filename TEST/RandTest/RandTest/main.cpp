#include <iostream>
#include <stdlib.h>
#include <time.h> 

using namespace std;

int main()
{
	int bRandCount = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++) {
		cout << rand() << endl;
		bRandCount++;
	}
		

	cout << endl;
	return 0;
}

