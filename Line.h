#pragma once
#include "Shape.h"

class Line : public Shape
{

public:

	Line(int x1, int y1, int x2, int y2, const MyString& color);

	int getLength() const;
	void print() const override;

	Shape* clone() const;

	int getArea() const override;
	int getPer()  const override;
	bool isPointIn(int x, int y) const override;

	void translate(int vertical, int horizontal);

	void saveInFile(std::ofstream& file) const override;
};