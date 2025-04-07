#ifndef _MYARRAY_HPP_
#define _MYARRAY_HPP_
#include<iostream>
#include<Windows.h>
#include<memory>
#include<initializer_list>
#include<algorithm>
#include<span>
#include<utility>
#include<sstream>
#include<iterator>


template<typename T>
class ConstIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = const value_type*;
	using reference = const value_type&;

	ConstIterator() = default;
	ConstIterator(pointer ptr) : ptr(ptr) {}


	ConstIterator& operator++() noexcept
	{
		++ptr;
		return *this;
	}
	ConstIterator& operator++(int) noexcept
	{
		ConstIterator temp(*this);
		++(*this);
		return temp;
	}
	ConstIterator& operator--() noexcept
	{
		--ptr;
		return *this;
	}
	ConstIterator& operator--(int) noexcept
	{
		ConstIterator temp(*this);
		--(*this);
		return temp;
	}
	reference operator*()const noexcept { return *ptr; }
	pointer operator->()const noexcept { return ptr; }
	


private:
	pointer ptr = nullptr;
};

template<typename T>
class Iterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = const value_type*;
	using reference = const value_type&;

	using ConstIterator<T>::ConstIterator;

	ConstIterator& operator++() noexcept
	{
		++ptr;
		return *this;
	}
	ConstIterator& operator++(int) noexcept
	{
		ConstIterator temp(*this);
		++(*this);
		return temp;
	}
	ConstIterator& operator--() noexcept
	{
		--ptr;
		return *this;
	}
	ConstIterator& operator--(int) noexcept
	{
		ConstIterator temp(*this);
		--(*this);
		return temp;
	}
	reference operator*()const noexcept { return *ptr; }
	pointer operator->()const noexcept { return ptr; }
};



class MyArray final
{
public:
	explicit MyArray(size_t size);
	explicit MyArray(std::initializer_list<int> list);
	MyArray(const MyArray& originalArray);
	MyArray& operator=(const MyArray& rightArray);
	MyArray(MyArray&& original) noexcept;
	MyArray& operator=(MyArray&& rightArray) noexcept;
	~MyArray();

	size_t size() const noexcept;
	std::string toString() const;

	bool operator==(const MyArray& rightArray) const noexcept;
	int& operator[](size_t index);
	const int& operator[](size_t index) const;
	explicit operator bool() const noexcept;

	MyArray& operator++();
	MyArray operator++(int);
	MyArray& operator+=(int value);

private:
	std::unique_ptr<int[]> ptr;
	size_t arrSize{ 0 };

	friend std::istream& operator>> (std::istream& in, MyArray& obj);
	friend void swap(MyArray& fristObj, MyArray& secondObj) noexcept;
};

std::ostream& operator<<(std::ostream& out, const MyArray& obj);


#endif  // !_MYARRAY_HPP_