#include <stdio.h>
char *returnStr()
{
	char p[] = "hello world!";
	//char *p = "hello world!";
	return p;
}
int main()
{
	char *str = NULL;//һ��Ҫ��ʼ������ϰ��
	str = returnStr();
	printf("%s\n", str);

	return 0;
}