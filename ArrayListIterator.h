#ifndef ARRAYLISTITERATOR_H_
#define ARRAYLISTITERATOR_H_

#include "ConcurrentModificationException.h"

template<typename T>
class ArrayListIterator
{
private:
	T* array;
	int size;
	int curIndex;
	unsigned long initialMods;
	unsigned long* totalMods;
public:
	ArrayListIterator(T*, int, unsigned long*, bool = false);

	T& operator*();

	void operator++();

	bool operator!=(const ArrayListIterator<T>& rhs);
private:
	bool isComplete();

	void checkForModification();
};

template<typename T>
ArrayListIterator<T>::ArrayListIterator(T* array, int size, unsigned long* modifications, bool complete)
{
	this->array = array;
	this->size = size;
	this->initialMods = *modifications;
	this->totalMods = modifications;

	if (complete)
	{
		this->curIndex = size;
	}
	else
	{
		this->curIndex = 0;
	}
}

template<typename T>
T& ArrayListIterator<T>::operator*()
{
	checkForModification();
	return array[curIndex];
}

template<typename T>
void ArrayListIterator<T>::operator++()
{
	if (isComplete())
	{
		return;
	}
    
	checkForModification();
	curIndex++;
}

template<typename T>
bool ArrayListIterator<T>::operator!=(const ArrayListIterator<T>& rhs)
{
	if (rhs.array != array)
	{
		return true;
	}
    
	if (rhs.size != size)
	{
		return true;
	}
	return rhs.curIndex != curIndex;
}

template<typename T>
bool ArrayListIterator<T>::isComplete()
{
	return curIndex >= size;
}

template<typename T>
void ArrayListIterator<T>::checkForModification()
{
	if (initialMods != *totalMods)
	{
		throw ConcurrentModificationException();
	}
}

#endif /* ARRAYLISTITERATOR_H_ */
