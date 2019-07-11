#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <algorithm>
#include "ArrayListIterator.h"
#include "IndexOutOfBoundsException.h"

template<typename T>
class ArrayList
{
private:
	constexpr static unsigned int MINIMUM_CAPACITY = 10;
	constexpr static float CAPACITY_RESIZE_BUFFER = 0.7;
	constexpr static int CAPACITY_RESIZE_MULTIPLIER = 2;

	T* data;
	unsigned int minCapacity;
	unsigned int capacity;
	unsigned int size;
	unsigned long* mods;
	bool sorted;
public:
	ArrayList();
	ArrayList(unsigned int);
	ArrayList(const ArrayList<T>&);
	~ArrayList();

	ArrayList<T>& operator=(const ArrayList<T>&);
	T& operator[](unsigned int);

	const T& at(unsigned int);

	unsigned int getSize();
	bool isEmpty();
	unsigned int indexOf(T&);

	ArrayListIterator<T> begin();
	ArrayListIterator<T> end();

	void insert(unsigned int, T&);
	void push_back(T&, bool = true);
	T pop();
	T pop_back();
	void remove(unsigned int);
	bool remove(T&);
	void clear();

	bool isSorted();
	void sort();
private:
	void resize();
	void moveUp(unsigned int);
	void moveDown(unsigned int);

	void swap(T*, T*);
	int partition(int, int);
	void quickSort(int, int);
};

template<typename T>
ArrayList<T>::ArrayList()
{
	minCapacity = MINIMUM_CAPACITY;
	data = new T[minCapacity];
	capacity = minCapacity;
	size = 0;
	mods = new unsigned long(0);
	sorted = true;
}

template<typename T>
ArrayList<T>::ArrayList(unsigned int baseCapacity)
{
	if (capacity < MINIMUM_CAPACITY)
	{
		capacity = MINIMUM_CAPACITY;
	}
    
	minCapacity = baseCapacity;
	data = new T[minCapacity];
	capacity = minCapacity;
	size = 0;
	mods = new unsigned long(0);
	sorted = true;
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& copy)
{
	minCapacity = copy.minCapacity;
	capacity = copy.capacity;
	size = copy.size;
	data = new T[capacity];
    
	for (unsigned int i = 0; i < size; i++)
	{
		data[i] = copy.data[i];
	}
    
	mods = new unsigned long(0);
	*mods = *copy.mods;
	sorted = copy.sorted;
}

template<typename T>
ArrayList<T>::~ArrayList()
{
	delete[] data;
	delete mods;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& copy)
{
	if (&copy != this)
	{
		delete[] data;
		delete mods;
		minCapacity = copy.minCapacity;
		capacity = copy.capacity;
		size = copy.size;
		data = new T[capacity];
        
		for (unsigned int i = 0; i < size; i++)
		{
			data[i] = copy.data[i];
		}
        
		mods = new unsigned long(0);
		*mods = *copy.mods;
		sorted = copy.sorted;
	}

	return *this;
}

template<typename T>
T& ArrayList<T>::operator[](unsigned int index)
{
	if (index >= size)
	{
		throw IndexOutOfBoundsException();
	}
    
	(*mods)++;
	sorted = false;
	return data[index];
}

template<typename T>
const T& ArrayList<T>::at(unsigned int index)
{
	if (index >= size)
	{
		throw IndexOutOfBoundsException();
	}
    
	return data[index];
}

template<typename T>
unsigned int ArrayList<T>::getSize()
{
	return size;
}

template<typename T>
bool ArrayList<T>::isEmpty()
{
	return size < 1;
}

template<typename T>
unsigned int ArrayList<T>::indexOf(T& element)
{
	if (size == 0)
	{
		return size;
	}
	else if (size == 1)
	{
		return element == data[0] ? 0 : size;
	}
    
	if (sorted)
	{
		unsigned int min = 0;
		unsigned int max = size - 1;
        
		while (min <= max)
		{
			unsigned int mid = (min + max) / 2;
            
			if (data[mid] < element)
			{
				min = mid + 1;
			}
			else if (data[mid] > element)
			{
				max = mid - 1;
			}
			else
			{
				return mid;
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < size; i++)
		{
			if (data[i] == element)
			{
				return i;
			}
		}
	}

	return size;
}

template<typename T>
void ArrayList<T>::insert(unsigned int index, T& element)
{
	if (index > size)
	{
		throw IndexOutOfBoundsException();
	}
    
	if (index == size)
	{
		data[size++] = element;
	}
	else
	{
		moveDown(index);
		data[index] = element;
		size++;
	}
    
	(*mods)++;
	sorted = false;
	resize();
}

template<typename T>
void ArrayList<T>::push_back(T& element, bool maintainSort)
{
	if (!maintainSort || !sorted)
	{
		data[size++] = element;
		(*mods)++;
		sorted = false;
		resize();
	}
	else
	{
		int position = 0;
        
		for (unsigned int i = 0; i < size; i++)
		{
			if (element > data[i])
			{
				position++;
			}
			else
			{
				break;
			}
		}
        
		insert(position, element);
		sorted = true;
	}
}

template<typename T>
T ArrayList<T>::pop()
{
	if (size < 1)
	{
		throw IndexOutOfBoundsException();
	}
    
	T d = data[0];
	moveUp(1);
	size--;
	(*mods)++;
	resize();
    
	return d;
}

template<typename T>
T ArrayList<T>::pop_back()
{
	if (size < 1)
	{
		throw IndexOutOfBoundsException();
	}
    
	T d = data[size-- - 1];
	data[size] = T();
	(*mods)++;
	resize();
    
	return d;
}

template<typename T>
void ArrayList<T>::remove(unsigned int index)
{
	if (index >= size)
	{
		throw IndexOutOfBoundsException();
	}
    
	if (index == size - 1)
	{
		data[index] = T();
		size--;
	}
	else
	{
		moveUp(index + 1);
		size--;
	}
    
	(*mods)++;
	resize();
}

template<typename T>
bool ArrayList<T>::remove(T& element)
{
	unsigned int index = indexOf(element);
    
	if (index != size)
	{
		remove(index);
		resize();
		(*mods)++;
        
		return true;
	}
    
	return false;
}

template<typename T>
void ArrayList<T>::clear()
{
	delete[] data;
	data = new T[minCapacity];
	size = 0;
	(*mods)++;
}

template<typename T>
void ArrayList<T>::resize()
{
	unsigned int newCapacity;
	T* copy;

	if (size <= (CAPACITY_RESIZE_BUFFER * (capacity / CAPACITY_RESIZE_MULTIPLIER)) && capacity > minCapacity)
	{
		newCapacity = capacity / CAPACITY_RESIZE_MULTIPLIER;
		copy = new T[std::min(minCapacity, newCapacity)];
	}
	else if (size > (CAPACITY_RESIZE_BUFFER * capacity))
	{
		newCapacity = capacity * CAPACITY_RESIZE_MULTIPLIER;
		copy = new T[newCapacity];
	}
	else
	{
		return;
	}

	for (unsigned int i = 0; i < size; i++)
	{
		copy[i] = data[i];
	}

	capacity = newCapacity;
	delete[] data;
	data = copy;
}

template<typename T>
void ArrayList<T>::moveUp(unsigned int start)
{
	unsigned int i;
    
	for (i = start; i < size; i++)
	{
		data[i - 1] = data[i];
	}

	data[i] = T();
}

template<typename T>
void ArrayList<T>::moveDown(unsigned int start)
{
	for (unsigned int i = size; i > start; i--)
	{
		data[i] = data[i - 1];
	}
    
	data[start] = T();
}

template<typename T>
ArrayListIterator<T> ArrayList<T>::begin()
{
	return ArrayListIterator<T>(data, size, mods);
}

template<typename T>
ArrayListIterator<T> ArrayList<T>::end()
{
	return ArrayListIterator<T>(data, size, mods, true);
}

template<typename T>
bool ArrayList<T>::isSorted()
{
	return sorted;
}

template<typename T>
void ArrayList<T>::sort()
{
	if (sorted || size <= 1)
	{
		return;
	}

	quickSort(0, size - 1);
	sorted = true;
}

template<typename T>
void ArrayList<T>::swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

template<typename T>
int ArrayList<T>::partition(int low, int high)
{
	T& pivot = data[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (data[j] <= pivot)
		{
			i++;
			swap(&data[i], &data[j]);
		}
	}
    
	swap(&data[i + 1], &data[high]);

	return (i + 1);
}

template<typename T>
void ArrayList<T>::quickSort(int low, int high)
{
	if (low < high)
	{
		int pi = partition(low, high);

		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

#endif /* ARRAYLIST_H_ */
