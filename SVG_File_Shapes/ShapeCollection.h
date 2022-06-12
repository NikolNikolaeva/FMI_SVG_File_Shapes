#pragma once
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class ShapeCollection
{
	Shape** shapes;
	size_t shapesCount;
	size_t capacity;

	void free();
	void copyFrom(const ShapeCollection& other);
	void resize();

	void addShape(Shape* shape);

public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();

	size_t getCount() const;

	void addRectangle(int x, int y, int width, int height, MyString& color);
	void addCircle(int x, int y, double radius, MyString& color);
	void addLine(int x1, int y1, int x2, int y2, MyString& color);

	void printAreas() const;
	void printPers() const;
	void printAll() const;

	bool erase(size_t index);

	void translate(int vertical, int horizontal);
	bool translate(size_t index, int vertical, int horizontal);

	void getShapesThatContainPoint(int x1, int y1) const;

	void withinReac(int x, int y, int width, int height) const;
	void withinCircle(int x, int y, int radius) const;
	void withinLine(int x1, int y1, int x2, int y2) const;

	void printType(size_t index) const;

	size_t getFileSize(std::ifstream& f);

	void readSVGfile(std::ifstream& file);
	void readReactangle(std::ifstream& file);
	void readCircle(std::ifstream& file);
	void readLine(std::ifstream& file);

	void saveInFile(std::ofstream& file) const;
};