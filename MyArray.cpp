#include "MyArray.hpp"

MyArray::MyArray(size_t size)
{
	this->arrSize = size;
	this->ptr = std::make_unique<int[]>(size);
}

MyArray::MyArray(std::initializer_list<int> list)
{
	this->arrSize = list.size();
	this->ptr = std::make_unique<int[]>(list.size());
	std::copy(std::begin(list), std::end(list), this->ptr.get());
}

MyArray::MyArray(const MyArray& originalArray)
{
	this->arrSize = originalArray.size();
	this->ptr = std::make_unique<int[]>(originalArray.size());
	const std::span<const int> source{ originalArray.ptr.get(), originalArray.size()};
	std::copy(std::begin(source), std::end(source), this->ptr.get());
}

size_t MyArray::size() const noexcept
{
	return arrSize;
}

MyArray& MyArray::operator=(const MyArray& rightArray)
{
	MyArray temp(rightArray);
	if (this != &rightArray)
	{
		swap(*this, temp);
	}
	return *this;
}

MyArray::MyArray(MyArray&& original) noexcept
{
	this->arrSize = std::exchange(original.arrSize, 0);
	this->ptr = std::move(original.ptr);
}

MyArray& MyArray::operator=(MyArray&& rightArray) noexcept
{
	if (this != &rightArray) {
		this->arrSize = std::exchange(rightArray.arrSize, 0);
		this->ptr = std::move(rightArray.ptr);
	}
	return *this;
}

MyArray::~MyArray()
{

}


std::string MyArray::toString() const
{
	const std::span<const int> arrayItems{ this->ptr.get(), this->arrSize };
	std::ostringstream output;
	for (size_t i = 0; const auto & item : arrayItems)
	{
		i++;
		output << item << (i < this->arrSize ? ", " : "");
	}
	return output.str();
}

bool MyArray::operator==(const MyArray& rightArray) const noexcept
{
	const std::span<const int> leftArr{ this->ptr.get(), this->arrSize };
	const std::span<const int> rightArr{ rightArray.ptr.get(), rightArray.arrSize };
	return std::equal(std::begin(leftArr), std::end(leftArr), std::begin(rightArr), std::end(rightArr));
}

int& MyArray::operator[](size_t index)
{
	if (index >= this->arrSize)
	{
		throw std::out_of_range("ERROR");
	}
	return this->ptr[index];
}

const int& MyArray::operator[](size_t index) const
{
	if (index >= this->arrSize)
	{
		throw std::out_of_range("ERROR");
	}
	return this->ptr[index];
}

MyArray::operator bool() const noexcept
{
	return size() != 0;
}

MyArray& MyArray::operator++()
{
	const std::span<int> items{this->ptr.get(), this->arrSize};
	std::for_each(items.begin(), items.end(), [](auto& i) {++i;});

	return *this;
}

MyArray MyArray::operator++(int)
{
	MyArray temp(*this);
	++(*this);
	return temp;
}

MyArray& MyArray::operator+=(int value)
{
	const std::span<int> items{ this->ptr.get(), this->arrSize };
	std::for_each(items.begin(), items.end(), [value](auto& i) {i += value; });
	return *this;
}

std::istream& operator>>(std::istream& in, MyArray& obj)
{
	std::span<int> items(obj.ptr.get(), obj.arrSize);
	for (auto& i : items)
	{
		in >> i;
	}
	return in;
}

void swap(MyArray& fristObj, MyArray& secondObj) noexcept
{
	std::swap(fristObj.arrSize, secondObj.arrSize);
	fristObj.ptr.swap(secondObj.ptr);
}

std::ostream& operator<<(std::ostream& out, const MyArray& obj)
{
	out << obj.toString();
	return out;
}
