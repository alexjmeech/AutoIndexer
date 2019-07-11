#ifndef ALEX_STRING_H_
#define ALEX_STRING_H_

#include <iostream>
#include <fstream>
#include <functional>
#include "ArrayWrapper.h"
using namespace std;

class String
{
private:
	char* buffer;
	unsigned int length;
	unsigned int bufferSize;
	String(unsigned int);
	void initialize(int = 0);
public:
	String();
	String(const char[]);
	String(const String&);
	~String();

	String& operator=(const String&);
	String& operator=(const char[]);
	friend bool operator==(const String&, const String&);
	friend bool operator!=(const String&, const String&);
	friend bool operator<(const String&, const String&);
	friend bool operator>(const String&, const String&);
	friend bool operator>=(const String&, const String&);
	friend bool operator<=(const String&, const String&);
	friend bool operator==(const char[], const String&);
	friend bool operator==(const String&, const char[]);
	friend bool operator!=(const char[], const String&);
	friend bool operator!=(const String&, const char[]);
	String& operator+=(const String&);
	String& operator+=(const char[]);
	String& operator+=(const char);
	char& operator[](const unsigned int);
	friend String operator+(const String&, const String&);
	friend String operator+(const String&, const char[]);
	friend String operator+(const String&, const char);
	friend String operator+(const char[], const String&);
	friend String operator+(const char, const String&);
	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);
	friend istream& getline(istream&, String&);
	friend istream& getline(istream&, String&, char);

	unsigned int getLength();
	String substring(unsigned int, unsigned int);
	String substringLength(unsigned int, unsigned int);
	ArrayWrapper<String> split(String&, bool = true);
	ArrayWrapper<String> split(const char[], bool = true);
	ArrayWrapper<String> split(char, bool = true);
	ArrayWrapper<String> split(function<bool(char)>);
	unsigned int find(String&, bool = true, unsigned int = 0);
	unsigned int find(const char[], bool = true, unsigned int = 0);
	unsigned int find(char, bool = true, unsigned int = 0);
	long getHashCode() const;

	String trim();
	String trimStart();
	String trimEnd();

	String stripCharacter(char, bool = true);
	String stripCharacter(function<bool(char)>);

	String toLower();
	String toUpper();

	String clone();

	char* c_string();
};

#endif /* ALEX_STRING_H_ */
