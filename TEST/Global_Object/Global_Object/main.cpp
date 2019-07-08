#include <iostream>
#include <string>
using namespace std;

class global {
public:
	global() {
		cout << "before main function" << endl;
	}
	~global() {
		cout << "after main function" << endl;
	}
};

global g_o;

int main() {
	cout << "main function" << endl;
	SharedPtr<string> pstr(new string("abc"));
	return 0;
}