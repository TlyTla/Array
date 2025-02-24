#include"MyArray.hpp"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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

	return 0;
}