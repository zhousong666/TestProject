#include <iostream>
#include <type_traits>

template<typename Ty>
class SharedPtr {
public:
	SharedPtr() = default;

	explicit SharedPtr(Ty&& value);
	explicit SharedPtr(const Ty& value);

	~SharedPtr();

	SharedPtr(const SharedPtr<Ty>& other);
	SharedPtr(SharedPtr<Ty>&& other);

	inline int use_count()noexcept
	{
		return *(this->counter);
	}

	//notice that:
	//当对 SharedPtr进行 *(解引用操作)的时候会调用这个先把SharedPtr转为指针.
	operator Ty*()noexcept;

	SharedPtr<Ty>& operator=(const SharedPtr<Ty>& other);
	SharedPtr<Ty>& operator=(SharedPtr<Ty>&& other);

private:
	mutable int* counter{ nullptr }; //引用计数.
	Ty* data{ nullptr }; //存储数据的指针.
};

template<typename Ty>
SharedPtr<Ty>::SharedPtr(Ty&& value)
	:data{ new Ty{ std::move(value) } },
	counter{ new int{ 0 } }
{
	++(*(this->counter));
}

template<typename Ty>
SharedPtr<Ty>::SharedPtr(const Ty& value)
	: data{ new Ty{ value } },
	counter{ new int{ 0 } }
{
	++(*(this->counter));
}

template<typename Ty>
SharedPtr<Ty>::SharedPtr(const SharedPtr<Ty>& other)
	:counter{ other.counter },
	data{ other.data }
{
	std::cout << "copy constructor" << std::endl;

	++((*this->counter));
}

template<typename Ty>
SharedPtr<Ty>::SharedPtr(SharedPtr<Ty>&& other)
	:counter{ other.counter },
	data{ std::move(other.data) }
{
	std::cout << "move-constructor" << std::endl;

	other.counter = nullptr;
	other.data = nullptr;
}

template<typename Ty>
SharedPtr<Ty>& SharedPtr<Ty>::operator=(const SharedPtr<Ty>& other)
{
	std::cout << "copy operator=" << std::endl;

	if (*(this->counter) == 1) {
		delete this->data;
		delete this->counter;
		this->data = nullptr;
		this->counter = nullptr;

	}
	else {
		--(*(this->counter));
	}

	++(*(other.counter));
	this->counter = other.counter;
	this->data = other.data;

	return *this;
}

template<typename Ty>
SharedPtr<Ty>& SharedPtr<Ty>::operator=(SharedPtr<Ty>&& other)
{
	std::cout << "move operator=" << std::endl;

	this->counter = other.counter;
	this->data = std::move(other.data);

	other.counter = nullptr;
	other.data = nullptr;

	return *this;
}

template<typename Ty>
SharedPtr<Ty>::operator Ty*()noexcept
{
	std::cout << "change to ptr" << std::endl;
	return (this->data);
}

template<typename Ty>
SharedPtr<Ty>::~SharedPtr()
{
	--(*(this->counter));
	if (*(this->counter) == 0) {
		delete this->counter;
		delete this->data;
		this->data = nullptr;
		this->counter = nullptr;
	}
}

SharedPtr<int> func()
{
	SharedPtr<int> ptr1{ 10 };
	SharedPtr<int> ptr2 = ptr1;
	SharedPtr<int> ptr3(ptr1);

	delete  ptr1;

	std::cout << ptr1.use_count() << "====" << ptr2.use_count() << std::endl;

	return ptr2;
}

int main()
{
	//    SharedPtr<int> ptr{ 20 };
	//    std::cout << *ptr << std::endl; //先调用了 operator Ty*();
	//    std::cout << ptr.use_count() << std::endl;

	std::cout << func().use_count() << std::endl;

	return 0;
}