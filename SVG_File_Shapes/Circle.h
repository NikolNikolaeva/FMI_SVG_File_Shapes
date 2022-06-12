#pragma once
#include "Shape.h"

class Circle : public Shape
{
	double radius;

public:
	Circle(int x, int y, double radius, const MyString& color);

	int getArea() const override;
	int getPer() const override;
	bool isPointIn(int x, int y) const override;
	Shape* clone() const override;
	void print() const override;

	double getRadius() const;

	void translate(int vertical, int horizontal);

	void saveInFile(std::ofstream& file) const override;
};