#include <iostream>

using namespace std;

class Point                                       //����������
{
public:
	Point(int xVal = 0, int yVal = 0) :x(xVal), y(yVal) { }
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int xVal) { x = xVal; }
	void setY(int yVal) { y = yVal; }

private:
	int x, y;
};
class RefPtr                                  //������
{    //�����Ա����Ȩ��ȫ��Ϊprivate����Ϊ�������û�ֱ��ʹ�ø���
	friend class SmartPtr;                                  //��������ָ����Ϊ��Ԫ����Ϊ����ָ������Ҫֱ�Ӳ��ݸ�����
	RefPtr(Point *ptr) :p(ptr), count(1) { }
	~RefPtr() { delete p; }
	int count;                                                     //���ü���
	Point *p;                                                      //��������ָ��
};
class SmartPtr                                             //����ָ����
{
public:
	SmartPtr(Point *ptr) :rp(new RefPtr(ptr)) { }                                 //���캯��
	SmartPtr(const SmartPtr &sp) :rp(sp.rp) { ++rp->count; }            //���ƹ��캯��
	SmartPtr& operator=(const SmartPtr& rhs) {                              //���ظ�ֵ������
		++rhs.rp->count;                                                                        //���Ƚ��Ҳ��������ü�����1��
		if (--rp->count == 0)                                                                     //Ȼ�����ü�����1������Ӧ���Ը�ֵ
			delete rp;
		rp = rhs.rp;
		return *this;
	}
	~SmartPtr() {                                            //��������
		if (--rp->count == 0)                                  //�����ü�����Ϊ0ʱ��ɾ�����������ָ�룬�Ӷ�ɾ����������
			delete rp;
	}
private:
	RefPtr *rp;                                                //���������ָ��
};
int main()
{
	Point *p1 = new Point(10, 8);
	SmartPtr sp1(p1);
	SmartPtr sp2(sp1);
	Point *p2 = new Point(5, 5);
	SmartPtr sp3(p2);
	sp3 = sp1;
	return 0;
}