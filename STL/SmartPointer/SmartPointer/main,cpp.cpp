#include <iostream>
#include <memory>
using namespace std;

class HasPtr {
private:
	string * ps;    //指向对应的对象
	int i;          //数据成员（没有实际意义）
	size_t * use;   //计数
public:
	//如果传递的是一个指向string的指针
	HasPtr(string * _ps) :ps(_ps), i(0), use(new size_t(1)) {}

	//如果传递的是一个string对象
	//s=string() 表示的是一个默认的参数
	HasPtr(const string & s = string()) :ps(new string(s)), i(0), use(new size_t(1)) {}
	HasPtr(const HasPtr &p) :ps(p.ps), use(p.use) { (*use)++; }

	HasPtr & operator=(const HasPtr & p) {
		(*(p.use))++; //给右侧的对象的计数++
		(*use)--;     //给左侧的对象的计数--
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
	HasPtr p1_1(s);      //计数为1
	p1_1.~HasPtr();
	//cout << *s << endl;  //s已经被delete掉

						 //demo2
	HasPtr p1("hi ya");
	HasPtr p2;         //计数为1
	HasPtr p3(p1);     //调用拷贝构造函数，计数为2
	HasPtr p4("world");         //计数为1
	p4 = p3;           //赋值构造函数，计数为3


					   //question
	p3.~HasPtr();
	//p4的计数是多少？ 计数是 2


	shared_ptr<int> p_share_ptr_test = make_shared<int>(42);
	auto p = make_shared<int>(43);
	auto q(p);

	return 0;
}