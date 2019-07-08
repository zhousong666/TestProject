#include <string>
#include <iostream>
using namespace std;
class BOOK  //������һ������
{
private:
	string _bookISBN;  //���ISBN��
	float _price;    //��ļ۸�

public:
	//������һ����Ա������������������Ǹ����ڴ�һ��ʵ��Ϊ�����͵ĺ�����
	//����������ڱȽ��������ISBN���Ƿ���ͬ
	bool isSameISBN(const BOOK & other) {
		return other._bookISBN == _bookISBN;
	}

	//��Ĺ��캯�������Ǹ����ܹ���һ���������е��õĹ��캯��������Ȼ���������βΣ�������һ����Ĭ��ʵ�Σ�ֻ��һ������Ҳ�ܽ��е��ã�
	//explicit BOOK(string ISBN, float price = 0.0f) :_bookISBN(ISBN), _price(price) {}

	BOOK(string ISBN, float price = 0.0f) :_bookISBN(ISBN), _price(price) {}
};

int main()
{
	BOOK A("A-A-A");
	BOOK B("B-B-B");

	cout << A.isSameISBN(B) << endl;   //�����ؽ��бȽϣ����跢��ת��

	cout << A.isSameISBN(string("A-A-A")) << endl; //�˴�������һ����ʽת����string����-->BOOK���ͣ�����BOOK�Ĺ��캯������ת����������isSameISBN�����Ĳ����ڴ���
	cout << A.isSameISBN(BOOK("A-A-A")) << endl;    //��ʽ������ʱ����Ҳ���Ǳ������ɵ����顣

	system("pause");
}