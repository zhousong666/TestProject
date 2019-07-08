#include <iostream>
using namespace std;

class A {
public:
	int a;

};

class B {
public:
	int a;

};
int main() {
	A * a = new A;
	a->a = 0;
	B * b = reinterpret_cast<B *>(a);
	b->a = 1;
	double d = 3.14159265;
	int    i = static_cast<int>(d);
	return 0;
}