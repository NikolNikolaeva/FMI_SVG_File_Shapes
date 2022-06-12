#include "ShapeCollection.h"
#include <stdexcept> 

void ShapeCollection::free()
{
	for (size_t i = 0; i < shapesCount; i++)
		delete shapes[i];
	delete[] shapes;
}
void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	shapes = new Shape * [other.shapesCount];
	shapesCount = other.shapesCount;
	capacity = other.capacity;

	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];
	for (size_t i = 0; i < shapesCount; i++)
		newCollection[i] = shapes[i];
	delete[] shapes;
	shapes = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}
ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ShapeCollection::~ShapeCollection()
{
	free();
}

size_t ShapeCollection::getCount() const
{
	return shapesCount;
}

void ShapeCollection::addShape(Shape* shape)
{
	if (shapesCount == capacity)
		resize();
	shapes[shapesCount++] = shape;
}

void ShapeCollection::addRectangle(int x, int y, int width, int height, MyString& color)
{
	Rectangle* rect = new Rectangle(x, y, width, height, color);
	addShape(rect);
}
void ShapeCollection::addCircle(int x, int y, double radius, MyString& color)
{
	Circle* circlce = new Circle(x, y, radius, color);
	addShape(circlce);

}
void ShapeCollection::addLine(int x1, int y1, int x2, int y2, MyString& color)
{
	Line* circlce = new Line(x1, y1, x2, y2, color);
	addShape(circlce);
}

bool ShapeCollection::erase(size_t index)
{
	if (index >= shapesCount)
		return false;

	for (size_t i = index; i < shapesCount; i++)
	{
		shapes[i] = shapes[i + 1];
	}
	shapesCount--;
	return true;
}

void ShapeCollection::printAreas() const
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << "\t" << i + 1 << ". ";
		std::cout << shapes[i]->getArea() << std::endl;
	}
}

void ShapeCollection::printPers() const
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << "\t" << i + 1 << ". ";
		std::cout << shapes[i]->getPer() << std::endl;;
	}
}

void ShapeCollection::translate(int vertical, int horizontal)
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i]->translate(vertical, horizontal);
	}
}

bool ShapeCollection::translate(size_t index, int vertical, int horizontal)
{
	if (index >= shapesCount)
		return false;
	shapes[index]->translate(vertical, horizontal);
	return true;
}

void ShapeCollection::getShapesThatContainPoint(int x1, int y1) const
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isPointIn(x1, y1))
		{
			std::cout << "\t" << i + 1 << ". ";
			shapes[i]->print();
		}
	}
}

void ShapeCollection::withinReac(int x, int y, int width, int height) const
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isPointIn(x, y) && shapes[i]->isPointIn(x, y - height) && shapes[i]->isPointIn(x + width, y - height) && shapes[i]->isPointIn(x + width, y))
		{
			std::cout << "\t" << i + 1 << ". ";
			shapes[i]->print();
		}
	}
}
void ShapeCollection::withinCircle(int x, int y, int radius) const
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isPointIn(x, y + radius) && shapes[i]->isPointIn(x, y - radius) && shapes[i]->isPointIn(x - radius, y) && shapes[i]->isPointIn(x + radius, y))
		{
			std::cout << "\t" << i + 1 << ". ";
			shapes[i]->print();
		}
	}
}
void ShapeCollection::withinLine(int x1, int y1, int x2, int y2) const
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isPointIn(x1, y1) && shapes[i]->isPointIn(x2, y2))
		{
			std::cout << "\t" << i + 1 << ". ";
			shapes[i]->print();
		}
	}
}

void ShapeCollection::printType(size_t index) const
{
	std::cout << "\t" << shapes[index]->getType();
}

void ShapeCollection::printAll() const
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << "\t" << i + 1 << ". ";
		shapes[i]->print();
	}
}

void ShapeCollection::saveInFile(std::ofstream& file) const
{
	file << "<svg>\n";
	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i]->saveInFile(file);
	}
	file << "</svg>\n";
}

void ShapeCollection::readSVGfile(std::ifstream& file)
{
	char buff[1024];
	while (!file.eof())
	{
		file >> buff;
		if (strcmp(buff, "<svg>") == 0)
		{
			while (strcmp(buff, "</svg>") != 0)
			{
				file >> buff;
				if (strcmp(buff, "<rect") == 0)
				{
					readReactangle(file);
				}
				else if (strcmp(buff, "<circle") == 0)
				{
					readCircle(file);
				}
				else if (strcmp(buff, "<line") == 0)
				{
					readLine(file);
				}
			}
			if (strcmp(buff, "</svg>") == 0)
				break;
		}
	}
	if (shapesCount > 0)
	{
		std::cout << "\tRead " << shapesCount << " figures from file" << std::endl;
	}
	else
	{
		std::cout << "\tNo figures in file" << std::endl;
	}
}

void ShapeCollection::readReactangle(std::ifstream& file)
{
	char color[20];
	char x[10];
	char y[10];
	char width[10];
	char height[10];

	int i = 0;
	char ch = ' ';
	while (ch != '>')
	{
		file >> ch;

		if (ch == '\"')
		{
			file >> ch;
			while (ch != '\"')
			{
				x[i] = ch;
				i++;
				file >> ch;
			}
			x[i] = '\0';
			while (true)
			{
				if (ch == '>')
					break;

				file >> ch;
				if (ch == '\"')
				{
					file >> ch;
					i = 0;
					while (ch != '\"')
					{
						y[i] = ch;
						i++;
						file >> ch;
					}
					y[i] = '\0';
					while (true)
					{
						if (ch == '>')
							break;

						file >> ch;
						if (ch == '\"')
						{
							file >> ch;
							i = 0;
							while (ch != '\"')
							{
								width[i] = ch;
								i++;
								file >> ch;
							}
							width[i] = '\0';
							while (true)
							{
								if (ch == '>')
									break;

								file >> ch;
								if (ch == '\"')
								{
									file >> ch;
									i = 0;
									while (ch != '\"') {
										height[i] = ch;
										i++;
										file >> ch;
									}
									height[i] = '\0';
									while (true)
									{
										file >> ch;
										if (ch == '\"')
										{
											file >> ch;
											i = 0;
											while (ch != '\"') {
												color[i] = ch;
												i++;
												file >> ch;
											}
											color[i] = '\0';

										}
										if (ch == '>')
											break;
									}
								}

							}

						}


					}
				}

			}

		}
	}

	MyString currColor = color;
	addRectangle(atoi(x), atoi(y), atoi(width), atoi(height), currColor);
}
void ShapeCollection::readCircle(std::ifstream& file)
{
	char color[20];
	char x[10];
	char y[10];
	char radius[10];

	int i = 0;
	char ch = ' ';
	while (ch != '>')
	{
		file >> ch;

		if (ch == '\"')
		{
			file >> ch;
			while (ch != '\"')
			{
				x[i] = ch;
				i++;
				file >> ch;
			}
			x[i] = '\0';
			while (true)
			{
				if (ch == '>')
					break;

				file >> ch;
				if (ch == '\"')
				{
					file >> ch;
					i = 0;
					while (ch != '\"')
					{
						y[i] = ch;
						i++;
						file >> ch;
					}
					y[i] = '\0';
					while (true)
					{
						if (ch == '>')
							break;

						file >> ch;
						if (ch == '\"')
						{
							file >> ch;
							i = 0;
							while (ch != '\"')
							{
								radius[i] = ch;
								i++;
								file >> ch;
							}
							radius[i] = '\0';
							while (true)
							{
								if (ch == '>')
									break;

								file >> ch;
								if (ch == '\"')
								{
									file >> ch;
									i = 0;
									while (ch != '\"') {
										color[i] = ch;
										i++;
										file >> ch;
									}
									color[i] = '\0';
								}

							}

						}


					}
				}

			}

		}
	}

	MyString currColor = color;
	addCircle(atoi(x), atoi(y), atoi(radius), currColor);
}
void ShapeCollection::readLine(std::ifstream& file)
{
	char color[20];
	char x1[10];
	char y1[10];
	char x2[10];
	char y2[10];

	int i = 0;
	char ch = ' ';
	while (ch != '>')
	{
		file >> ch;

		if (ch == '\"')
		{
			file >> ch;
			while (ch != '\"')
			{
				x1[i] = ch;
				i++;
				file >> ch;
			}
			x1[i] = '\0';
			while (true)
			{
				if (ch == '>')
					break;

				file >> ch;
				if (ch == '\"')
				{
					file >> ch;
					i = 0;
					while (ch != '\"')
					{
						y1[i] = ch;
						i++;
						file >> ch;
					}
					y1[i] = '\0';
					while (true)
					{
						if (ch == '>')
							break;

						file >> ch;
						if (ch == '\"')
						{
							file >> ch;
							i = 0;
							while (ch != '\"')
							{
								x2[i] = ch;
								i++;
								file >> ch;
							}
							x2[i] = '\0';
							while (true)
							{
								if (ch == '>')
									break;

								file >> ch;
								if (ch == '\"')
								{
									file >> ch;
									i = 0;
									while (ch != '\"') {
										y2[i] = ch;
										i++;
										file >> ch;
									}
									y2[i] = '\0';
									while (true)
									{
										file >> ch;
										if (ch == '\"')
										{
											file >> ch;
											i = 0;
											while (ch != '\"') {
												color[i] = ch;
												i++;
												file >> ch;
											}
											color[i] = '\0';

										}
										if (ch == '>')
											break;
									}
								}

							}

						}


					}
				}

			}

		}
	}

	MyString currColor = color;
	addLine(atoi(x1), atoi(y1), atoi(x2), atoi(y2), currColor);
}