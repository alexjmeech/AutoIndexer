#ifndef CONCURRENTMODIFICATIONEXCEPTION_H_
#define CONCURRENTMODIFICATIONEXCEPTION_H_

#include <exception>

struct ConcurrentModificationException : public std::exception
{
	virtual const char* what() const throw ()
	{
		return "Attempted to modify an array while iterating through it";
	}
};

#endif /* CONCURRENTMODIFICATIONEXCEPTION_H_ */
