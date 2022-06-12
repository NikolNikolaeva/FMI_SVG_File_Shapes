
#pragma once
#include <fstream>

class MyString
{
private:

	char* str;
	size_t size;

	void copyFrom(const MyString&);
	void free();

public:

	MyString();
	MyString(const char*);

	MyString(const MyString&);
	MyString& operator = (const MyString&);
	MyString& operator=(MyString&);

	~MyString();

	size_t getSize() const;
	void concat(const MyString&);
	void concat(char);

	const char* c_str() const;

	MyString& operator+=(const MyString&);

	friend std::istream& operator>>(std::istream&, MyString&);
	friend std::ostream& operator<<(std::ostream&, const MyString&);

	void getLine(std::istream& outFile);

};

MyString operator+(const MyString&, const MyString&);

bool operator==(const MyString&, const MyString&);
bool operator<=(const MyString&, const MyString&);
bool operator<(const MyString&, const MyString&);