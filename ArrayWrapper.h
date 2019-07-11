#ifndef ARRAYWRAPPER_H_
#define ARRAYWRAPPER_H_

#include "IndexOutOfBoundsException.h"

template <typename T>
class ArrayWrapper
{
private:
	T* internal;
	unsigned int length;
public:
	ArrayWrapper(T* array, unsigned int length, bool deleteOld = false)
	{
		this->internal = new T[length];
		this->length = length;
        
		for (unsigned int i = 0; i < this->length; i++)
		{
			this->internal[i] = array[i];
		}
        
		if (deleteOld)
		{
			delete[] array;
		}
	}

	ArrayWrapper(const ArrayWrapper& copy)
	{
		internal = new T[copy.length];
		length = copy.length;
        
		for (unsigned int i = 0; i < length; i++)
		{
			internal[i] = copy.internal[i];
		}
	}

	~ArrayWrapper()
	{
		delete[] internal;
	}

	ArrayWrapper& operator=(const ArrayWrapper& copy)
	{
		if (this != &copy)
		{
			delete[] internal;
			internal = new T[copy.length];
			length = copy.length;
            
			for (unsigned int i = 0; i < length; i++)
			{
				internal[i] = copy.internal[i];
			}
		}

		return *this;
	}

	T& operator[](const unsigned int index)
	{
		if (index < 0 || index >= length)
		{
			throw IndexOutOfBoundsException();
		}

		return internal[index];
	}

	unsigned int arrayLength()
	{
		return length;
	}
};

#endif /* ARRAYWRAPPER_H_ */
