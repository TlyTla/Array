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
class Iterator : public ConstIterator<T>
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = const value_type*;
	using reference = const value_type&;

	using ConstIterator<T>::ConstIterator;

	Iterator& operator++() noexcept
	{
		ConstIterator<T>::operator++();
		return *this;
	}
	Iterator& operator++(int) noexcept
	{
		ConstIterator temp(*this);
		ConstIterator<T>::operator++();
		return temp;
	}
	Iterator& operator--() noexcept
	{
		ConstIterator<T>::operator--();
		return *this;
	}
	Iterator& operator--(int) noexcept
	{
		ConstIterator temp(*this);
		ConstIterator<T>::operator--();
		return temp;
	}
};

template<typename T, size_t SIZE>
struct myArray
{
	using value_type = T;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = Iterator<T>;
	using const_iterator = ConstIterator<T>;
	using reverse_iterator = std::reverse_iterator<const_iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr size_type size() const noexcept { return SIZE; }

	iterator begin() { return iterator{ &data[0] }; }
	iterator end() { return iterator{ &data[0] + size() }; }
	const_iterator begin() const { return const_iterator{ &data[0] }; }
	const_iterator end() const { return const_iterator{ &data[0] + size() }; }

	iterator cbegin() { return iterator{ &data[0] }; }
	iterator cend() { return iterator{ &data[0] + size() }; }
	const_iterator cbegin() const { return begin(); }
	const_iterator cend() const { return end(); }

	reverse_iterator rbegin() { return reverse_iterator{ end() }; }
	reverse_iterator rend() { return reverse_iterator{ begin() }; }
	const_reverse_iterator rbegin() const { return const_reverse_iterator{ end() }; }
	const_reverse_iterator rend() const { return const_reverse_iterator{ begin() }; }

	const_reverse_iterator crbegin() const { return rbegin(); }
	const_reverse_iterator crend() const { return rend(); }


	auto operator<=> (const myArray& t) const noexcept = default;
	T& operator[](size_type index)
	{
		if (index >= size())
		{
			throw std::out_of_range("FKU");
		}
		else
		{
			return this->data[index];
		}
	}
	const T& operator[](size_type index) const
	{
		if (index >= size())
		{
			throw std::out_of_range("FKU");
		}
		else
		{
			return this->data[index];
		}
	}

	template<typename T, std::same_as<T>...Us> //вариативный шаблон
	myArray(T first, Us... rest) -> myArray<T, 1 + sizeof...(Us)>;

	T data[SIZE];
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