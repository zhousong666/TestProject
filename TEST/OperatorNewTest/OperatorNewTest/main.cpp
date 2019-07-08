#include <iostream>

using namespace std;

int main() {
	int data = 123456;
	int *pa = new(&data) int;//pa指针将指向data对象，里面的内容与data保持一致，没有进行覆盖。
	int *pb = new(&data) int(123);//pb指针同样指向data对象，里面的内容将用123进行覆盖。
	return 0;
}