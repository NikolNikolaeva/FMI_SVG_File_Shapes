#include "Circle.h"

const double PI = 3.1415;
Circle::Circle(int x, int y, double radius, const MyString& color) : Shape(1, color), radius(radius)
{
	type = Type::circle;
	setPoint(0, x, y);
}

int Circle::getArea() const
{
	return PI * radius * radius;
}
int Circle::getPer() const
{
	return 2 * PI * radius;
}
bool Circle::isPointIn(int x, int y) const
{
	Shape::point p(x, y);
	return p.getDist(getPointAtIndex(0)) <= radius;
}
Shape* Circle::clone() const
{
	Shape* copy = new Circle(*this);
	return copy;
}

double Circle::getRadius() const
{
	return radius;
}
void Circle::print() const
{
	std::cout << "circle " << getXAtIndex(0) << " " << getYAtIndex(0) << " " << getRadius() << " " << getColor() << std::endl;
}

void Circle::translate(int vertical, int horizontal)
{
	setPoint(0, getXAtIndex(0) + horizontal, getYAtIndex(0) + vertical);
}

void Circle::saveInFile(std::ofstream& file) const
{
	file << "<circle cx=\"" << getXAtIndex(0) << "\" cy=\"" << getYAtIndex(0) << "\" r=\"" << getRadius() << "\" fill=\"" << getColor() << "\"/ >\n";
}