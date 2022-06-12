#pragma once 
#include "MyString.h"
#include<iostream>
#include <cstring>
#pragma warning (disable:4996)

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
}

void MyString::free()
{
	delete[] str;
}

MyString::MyString()
{
	size = 0;
	str = new char[1];
	str[0] = '\0';

}
MyString::MyString(const char* data)
{
	size = strlen(data);
	str = new char[size + 1];
	strcpy(str, data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}
MyString& MyString::operator= (const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
MyString& MyString::operator=(MyString& other)
{
	if (this != &other)
	{
		free();
		str = other.str;
		other.str = nullptr;
		size = other.size;
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getSize() const
{
	return size;
}
void MyString::concat(const MyString& other)
{
	char* temp = new char[getSize() + other.getSize() + 1];
	strcpy(temp, str);
	strcat(temp, other.str);

	delete[] str;
	str = temp;
	size = size + other.getSize();
}

const char* MyString::c_str() const
{
	return str;
}

MyString& MyString::operator+=(const MyString& other)
{
	concat(other);
	return *this;
}

std::istream& operator>>(std::istream& in, MyString& str)
{
	delete[] str.str;
	char buff[1024];
	in.getline(buff, 1024);

	str.size = strlen(buff);
	str.str = new char[str.size + 1];
	strcpy(str.str, buff);
	return in;
}
std::ostream& operator<<(std::ostream& out, const MyString& str)
{
	out << str.str;
	return out;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString str(lhs);
	str += rhs;
	return str;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator<(const MyString& lhs, const MyString&rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

void MyString::getLine(std::istream& outFile)
{
	delete[] str;
	char buff[1024];

	outFile.getline(buff, 1024, '\n');
	size_t len = strlen(buff);
	str = new char[len + 1];
	for (size_t i = 0; i < len; i++)
		str[i] = buff[i];
	str[len] = '\0';
	size = len;
}
