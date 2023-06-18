#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>

// Vector implementation made during OOP practicum by me
template <typename T>
class Vector
{
	T* data;
	size_t size;
	size_t capacity;

	// Big 6 logic
	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	
	// Array resize logic
	void resize(size_t newCapacity);

public:

	// Big 6 interface
	Vector();
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);

	Vector<T> operator=(const Vector<T>& other);
	Vector<T> operator=(Vector<T>&& other);

	// Add to end functions
	void pushBack(const T& element);
	void pushBack(T&& element);

	// Remove from end function
	void popBack();

	// Insert at index functions
	void insert(const T& element, size_t index);
	void insert(T&& element, size_t index);

	// Remove at index function
	void erase(size_t index);

	// Remove all data function
	void clear();

	// Indexers
	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	// Getters
	bool isEmpty() const;
	size_t getSize() const;

	~Vector();
};

/*
	Big 6 Logic
*/

template <typename T>
void Vector<T>::free()
{
	delete data;
	data = nullptr;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;

	other.data = nullptr;
}

/*
	Memory Resize functionality
*/

template <typename T>
void Vector<T>::resize(size_t newCapacity)
{
	T* newData = new T[newCapacity];

	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
}

/*
	Constructors
*/

template <typename T>
Vector<T>::Vector()
{
	capacity = 8;
	size = 0;

	data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other)
{
	moveFrom(std::move(other));
}

/*
	Operator =
*/

template <typename T>
Vector<T> Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

/*
	Add element to end of vector
*/

template <typename T>
void Vector<T>::pushBack(const T& element)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = element;
}

template <typename T>
void Vector<T>::pushBack(T&& element)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = std::move(element);
}

/*
	Remove element from end of vector
*/

template <typename T>
void Vector<T>::popBack()
{
	if (isEmpty())
	{
		throw std::runtime_error("Cannot remove element from empty vector!");
	}

	if (size * 4 == capacity)
	{
		resize(capacity / 2);
	}

	size--;
}

/*
	Insert element at index of vector
*/

template <typename T>
void Vector<T>::insert(const T& element, size_t index)
{
	if (index >= size)
	{
		throw std::runtime_error("Cannot insert element at non-existing index!");
	}

	if (size == capacity)
	{
		resize(2 * capacity);
	}

	for (size_t i = size; i > index; i--)
	{
		data[i] = std::move(data[i - 1]);
	}

	data[index] = element;
	size++;
}

template <typename T>
void Vector<T>::insert(T&& element, size_t index)
{
	if (index >= size)
	{
		throw std::runtime_error("Cannot insert element at non-existing index!");
	}

	if (size == capacity)
	{
		resize(2 * capacity);
	}
	
	for (size_t i = size; i > index; i--)
	{
		data[i] = std::move(data[i - 1]);
	}

	data[index] = std::move(element);
	size++;
}

/*
	Remove element at index of vector
*/

template <typename T>
void Vector<T>::erase(size_t index)
{
	if (index >= size)
	{
		throw std::runtime_error("Cannot erase element at non-existing index!");
	}

	if (size * 4 == capacity)
	{
		resize(capacity / 2);
	}

	size--;

	for (size_t i = index; i < size; i++)
	{
		data[i] = std::move(data[i + 1]);
	}
}

/*
	Remove all elements
*/

template <typename T>
void Vector<T>::clear()
{
	free();
	size = 0;
	capacity = 8;
	data = new T[capacity];
}

/*
	Indexers
*/

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	return data[index];
}

/*
	Destructors
*/

template <typename T>
Vector<T>::~Vector()
{
	free();
}

/*
	Getter functions
*/

template <typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return size;
}
