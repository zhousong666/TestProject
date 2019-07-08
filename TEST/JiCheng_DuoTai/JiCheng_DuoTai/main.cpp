#include<iostream>
#include <vector>
using namespace std;
//C实现动态，用到函数指针

typedef void(*FUN)();//重定义一个函数指针类型

					 //父类
struct Base
{
	FUN _f;
};

//子类
struct Derived
{
	Base _b;//在子类中定义一个基类的对象即可实现对父类的继承
};


void FunB()
{
	printf("%s\n", "Base::fun()");
}
void FunD()
{
	printf("%s\n", "Derived::fun()");
}

class X {
};

class A :virtual  public X {
	static const int ix = 0;
};

class B :virtual  public X {

};

class C : public A, public B {

};

int  main()
{


	vector<int> ie;
	ie.push_back(1);
	A * aa = new A;
	B * bb = new B;
	C * cc = new C;
	ie.erase(ie.begin());
	int x = sizeof(X);
	int a = sizeof(A);
	int b = sizeof(B);
	int c = sizeof(C);
	A aaa;
	const int *bbbb = &aaa.ix;
	return 0;
}