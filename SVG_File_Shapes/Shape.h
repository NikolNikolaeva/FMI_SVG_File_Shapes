#pragma once
#include <iostream>
#include "MyString.h"

class Shape
{
protected:
	struct point
	{
		point() :x(0), y(0) {}
		point(int x, int y) :x(x), y(y) {}
		int x;
		int y;
		double getDist(const point& other) const
		{
			int dx = x - other.x;
			int dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};
	const point& getPointAtIndex(size_t index) const;
	double getDist(const point& p1, const point& p2) const;
	int& getXAtIndex(size_t index) const;
	int& getYAtIndex(size_t index) const;

	enum Type
	{
		rectangle,
		line,
		circle
	}type;

private:
	point* points;
	size_t pointsCount;
	MyString color;

	void copyFrom(const Shape& other);
	void free();


public:
	Shape(size_t pointsCount, const MyString& color);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape();

	void setPoint(size_t pointIndex, int x, int y);
	virtual void translate(int vertical, int horizontal) = 0;

	virtual int getArea() const = 0;
	virtual int getPer()  const = 0;
	virtual bool isPointIn(int x, int y) const = 0;
	virtual Shape* clone() const = 0;

	const MyString& getColor() const;
	void setColor(const MyString& color);
	const Type& getType() const;

	virtual void print() const = 0;

	virtual void saveInFile(std::ofstream& file) const = 0;

};