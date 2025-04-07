#include"MyArray.hpp"



#include <deque>
#include<array>


template<typename T>
class Stack;



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	

	/*
	MyArray a(5);
	std::cin >> a;
	std::cout << a << "\n";
	a++;
	std::cout << a << "\n";
	a += 2;
	std::cout << a << "\n";

	MyArray b{ 4,5,6,7,8,9 };
	std::cout << b << "\n";
	b = a;
	std::cout << b << "\n";

	MyArray z(b);
	std::cout << z << "\n";
	std::cout << z[2] << "\n";
	*/

	myArray one{ 1,2,3 };

	return 0;
}


template<typename T>
class Stack
{
public:
	void Pop()
	{
		if (!data.empty())
		{
			data.pop_back();
		}
		else
		{
			throw std::_Xout_of_range("Empty");
		}
	}
	void Push(const T& value)
	{
		data.push_back(value);
	}
	size_t Size()
	{
		data.size();
	}
	bool Empty() const
	{
		return data.empty();
	}
	const T& Top() const
	{
		if (!data.empty())
		{
			data.pop_back();
		}
		else
		{
			throw std::_Xout_of_range("Empty");
		}
	}

private:
	std::deque<T> data;
};