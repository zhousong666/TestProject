#include<iostream>
#include <vector>
using namespace std;
//Cʵ�ֶ�̬���õ�����ָ��

typedef void(*FUN)();//�ض���һ������ָ������

					 //����
struct Base
{
	FUN _f;
};

//����
struct Derived
{
	Base _b;//�������ж���һ������Ķ��󼴿�ʵ�ֶԸ���ļ̳�
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