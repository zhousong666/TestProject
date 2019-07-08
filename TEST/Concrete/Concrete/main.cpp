#include <iostream>

using namespace std;

class Point3d {
public:
	static Point3d origin;
	float x, y, z;
};
class Concrete1 {
public:
	int val;
	char bit1;
};

class Concrete2 :public Concrete1{
public:
	char bit2;
};

class Concrete3 :public Concrete2 {
public:
	char bit3;
};

int main() {
	Concrete2 *pc2;
	Concrete1 *pc1_1, *pc1_2;

	pc2 = new Concrete2;
	pc2->bit2 = '2';
	pc1_1 = new Concrete1;
	pc1_1->bit1 = '1_1';
	pc1_2 = new Concrete1;
	pc1_2->bit1 = '1_2';

	pc1_1 = pc2;
	Point3d adfa;

	cout << &Point3d::z << endl;
	cout << &Point3d::x << endl;
	cout << &Point3d::y << endl;

	cout << &adfa.z;
	return 0;
}