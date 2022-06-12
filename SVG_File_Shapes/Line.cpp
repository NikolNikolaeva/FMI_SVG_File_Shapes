#include "Line.h"

Line::Line(int x1, int y1, int x2, int y2, const MyString& color) :Shape(2, color)
{
	type = Shape::line;
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
}
int Line::getLength() const
{
	return getDist(getPointAtIndex(0), getPointAtIndex(1));
}
void Line::print() const
{
	std::cout << "line " << getXAtIndex(0) << " " << getYAtIndex(0) << " " << getXAtIndex(1) << " " << getYAtIndex(1) << " " << getLength() << " " << getColor() << std::endl;
}

Shape* Line::clone() const
{
	Shape* copy = new Line(*this);
	return copy;
}
int Line::getArea() const
{
	return getLength();
}
int Line::getPer()  const
{
	return getLength();
}
bool Line::isPointIn(int x, int y) const
{
	point p1(x, y);
	if (getDist(getPointAtIndex(0), p1) + getDist(getPointAtIndex(1), p1) == getDist(getPointAtIndex(0), getPointAtIndex(1)))
		return true;
	return false;
}

void Line::translate(int vertical, int horizontal)
{
	setPoint(0, getXAtIndex(0) + horizontal, getYAtIndex(0) + vertical);
	setPoint(1, getXAtIndex(1) + horizontal, getYAtIndex(1) + vertical);
}

void Line::saveInFile(std::ofstream& file) const
{
	file << "<rect x1=\"" << getXAtIndex(0) << "\" y1=\"" << getYAtIndex(0) << "\" x2=\"" << getXAtIndex(1) << "\" y2=\"" << getYAtIndex(1) << "\" fill=\"" << getColor() << "\"/ >\n";
}