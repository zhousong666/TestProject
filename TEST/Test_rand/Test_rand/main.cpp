#include <iostream>
using namespace std;
#include   <stdlib.h>    
#include   <time.h> 
#define MIN 1    //����������ķ�Χ    
#define MAX 10

int main()
{
	int i;
	srand((unsigned)time(0));
	cout << "Ten random numbers from " << MIN <<
		" to " << MAX << " :/n" << endl;
	for (i = 0; i<10; i++)          //���������
	{
		cout << MIN + (int)MAX * rand() / (RAND_MAX + 1) << "/t";
	}
	cout << endl;
	return   0;
}