#include <iostream>

using namespace std;

class Base {
public:
	virtual  ~Base() {
		cout << "~Base()" << endl;
	}
private:
	static  int a;
};

class Derived1 : public Base {
public:
	Derived1() :name_(new string("NULL")) {}
	Derived1(const string& n) :name_(new string(n)) {}

	~Derived1() {
		delete name_;
		cout << "~Derived1(): name_ has been deleted." << endl;
	}

private:
	string* name_;
};

class Derived2 : public Base {
public:
	Derived2() :name_(new string("NULL")) {}
	Derived2(const string& n) :name_(new string(n)) {}

	~Derived2() {
		delete name_;
		cout << "~Derived2(): name_ has been deleted." << endl;
	}

private:
	string* name_;
};


int Base::a = 0;
int main() {
	
	/*int(*p)[4];
	int a[3][4] = { 0 };
	p = a;

	int * p2[4];
	int a2[3][4];

	char a3[5] = { 'A','B','C','D' };
	char(*p3)[5] = &a3;
	//char(*p4)[5] = a3;*/
	

	return 0;
}