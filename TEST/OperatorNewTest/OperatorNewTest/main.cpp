#include <iostream>

using namespace std;

int main() {
	int data = 123456;
	int *pa = new(&data) int;//paָ�뽫ָ��data���������������data����һ�£�û�н��и��ǡ�
	int *pb = new(&data) int(123);//pbָ��ͬ��ָ��data������������ݽ���123���и��ǡ�
	return 0;
}