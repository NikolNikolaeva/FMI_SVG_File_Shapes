#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height, const MyString& color) : Shape(4, color)
{
	type = Type::rectangle;
	setPoint(0, x, y);
	setPoint(1, x, y - height);
	setPoint(2, x + width, y - height);
	setPoint(3, x + width, y);
	this->width = width;
	this->height = height;
}

void Rectangle::translate(int horizontal, int vertical)
{
	int x = getXAtIndex(0);
	int y = getYAtIndex(0);

	setPoint(0, x+horizontal, y+vertical);
	setPoint(1, x + horizontal, y + vertical - height);
	setPoint(2, x + horizontal + width, y + vertical - height);
	setPoint(3, x + horizontal + width, y + vertical);
}
int Rectangle::getArea() const
{
	return (width * height);
}
int Rectangle::getPer() const
{
	return (2 * width + 2 * height);
}

bool Rectangle::isPointIn(int x, int y) const
{
	Shape::point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.y >= getPointAtIndex(1).y &&
		p.y <= getPointAtIndex(0).x && p.y >= getPointAtIndex(2).y;
}
Shape* Rectangle::clone() const
{
	Shape* copy = new Rectangle(*this);
	return copy;
}

double Rectangle::getWidth() const
{
	return width;
}
double Rectangle::getHeight() const
{
	return height;
}

void Rectangle::print() const
{
	std::cout << "rectangle " << getXAtIndex(0) << " " << getYAtIndex(0) << " " << getWidth() << " " << getHeight() << " " << getColor() << std::endl;
}

void Rectangle::saveInFile(std::ofstream& file) const
{
	file << "<rect x=\"" << getXAtIndex(0) << "\" y=\"" << getYAtIndex(0) << "\" width=\"" << getWidth() << "\" height=\"" << getHeight() << "\" fill=\"" << getColor() << "\"/>\n";
}
