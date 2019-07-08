#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

struct even {
	bool operator() (int x) const
	{
		return x % 2 ? false : true; 
	}
};

int main() {
	int ia[] = { 12,17,20,22,23,30,33,40 };
	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));
	
	return 0;
}
