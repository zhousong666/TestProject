#include <iostream>
#include <memory>
using namespace std;

class HasPtr {
private:
	string * ps;    //ָ���Ӧ�Ķ���
	int i;          //���ݳ�Ա��û��ʵ�����壩
	size_t * use;   //����
public:
	//������ݵ���һ��ָ��string��ָ��
	HasPtr(string * _ps) :ps(_ps), i(0), use(new size_t(1)) {}

	//������ݵ���һ��string����
	//s=string() ��ʾ����һ��Ĭ�ϵĲ���
	HasPtr(const string & s = string()) :ps(new string(s)), i(0), use(new size_t(1)) {}
	HasPtr(const HasPtr &p) :ps(p.ps), use(p.use) { (*use)++; }

	HasPtr & operator=(const HasPtr & p) {
		(*(p.use))++; //���Ҳ�Ķ���ļ���++
		(*use)--;     //�����Ķ���ļ���--
		if (*use == 0) {
			delete ps;
			delete use;
		}
		ps = p.ps;
		i = p.i;
		use = p.use;
		return *this;
	}
	~HasPtr() {
		(*use)--;
		if (*use == 0) {
			delete use;
			delete ps;
		}
	}
};

int main()
{
	//demo1
	string * s = new string("hello");
	HasPtr p1_1(s);      //����Ϊ1
	p1_1.~HasPtr();
	//cout << *s << endl;  //s�Ѿ���delete��

						 //demo2
	HasPtr p1("hi ya");
	HasPtr p2;         //����Ϊ1
	HasPtr p3(p1);     //���ÿ������캯��������Ϊ2
	HasPtr p4("world");         //����Ϊ1
	p4 = p3;           //��ֵ���캯��������Ϊ3


					   //question
	p3.~HasPtr();
	//p4�ļ����Ƕ��٣� ������ 2


	shared_ptr<int> p_share_ptr_test = make_shared<int>(42);
	auto p = make_shared<int>(43);
	auto q(p);

	return 0;
}