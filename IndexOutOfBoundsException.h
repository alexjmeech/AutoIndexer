#ifndef INDEXOUTOFBOUNDSEXCEPTION_H_
#define INDEXOUTOFBOUNDSEXCEPTION_H_

#include <exception>

struct IndexOutOfBoundsException : public std::exception
{
	virtual const char* what() const throw ()
	{
		return "Attempted to access an index which is out of bounds";
	}
};

#endif /* INDEXOUTOFBOUNDSEXCEPTION_H_ */
