#include <set>
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
	int i = 0;
	int ia[5] = { 0, 5, 2, 3, 4 };
	set<int> iset(ia, ia + 5);
	map<string, int> sampleMap;
	sampleMap[string("zhousong")] = 1;
	sampleMap[string("wang")] = 2;

	pair<string, int> value(string("ss"), 3);
	sampleMap.insert(value);
	map<string, int>::iterator iter = sampleMap.begin();

	int number = sampleMap[string("zhousong")];
	return 0;
}