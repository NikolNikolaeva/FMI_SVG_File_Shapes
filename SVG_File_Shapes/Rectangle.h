#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
	int width;
	int height;
public:

	Rectangle(int x, int y, int width, int height, const MyString& color);
	int getArea() const override;
	int getPer() const override;
	bool isPointIn(int x, int y) const override;
	Shape* clone() const override;

	void print() const override;

	double getWidth() const;
	double getHeight() const;

	void translate(int horizontal, int vertical) override;

	void saveInFile(std::ofstream& file) const override;
};