
#include <iostream>
#include "SVG-fail.h"

void SVGFile::createReactangle()
{
	int x, y, width, height;
	MyString color;
	std::cout << "\tEnter x, y, width, height and color of the reactangle in that order: " << std::endl;
	std::cout << "\t-> ";
	std::cin >> x >> y >> width >> height >> color;
	std::cin.ignore();

	shapes.addRectangle(x, y, width, height, color);
	std::cout << "\tSuccessfully created rectangle (" << shapes.getCount() << ")" << std::endl;
}
void SVGFile::createCircle()
{
	int x, y, radius;
	MyString color;
	std::cout << "\tEnter x, y, radius and color of the circle in that order: " << std::endl;
	std::cout << "\t-> ";
	std::cin >> x >> y >> radius >> color;
	std::cin.ignore();

	shapes.addCircle(x, y, radius, color);
	std::cout << "\tSuccessfully created circle (" << shapes.getCount() << ")" << std::endl;
}
void SVGFile::createLine()
{
	int x1, y1, x2, y2;
	MyString color;
	std::cout << "\tEnter x1, y1, x2, y2 and color of the line in that order: " << std::endl;
	std::cout << "\t-> ";
	std::cin >> x1 >> y1 >> x2 >> y2 >> color;
	std::cin.ignore();

	shapes.addLine(x1, y1, x2, y2, color);
	std::cout << "\tSuccessfully created line (" << shapes.getCount() << ")" << std::endl;
}
void SVGFile::erase()
{
	int index;
	std::cout << "\tEnter the number of figure: " << std::endl;;
	std::cout << "\t-> ";
	std::cin >> index;
	std::cin.ignore();

	if (shapes.erase(index - 1) == true)
	{
		std::cout << "\tErased figure" << std::endl;
	}
	else
	{
		std::cout << "\tThere is no figure number " << index << "!" << std::endl;
	}

}
void SVGFile::translate()
{
	size_t index;
	int vertical, horizontal;
	std::cout << "\tEnter number of the figure, vertical and horizontal translate: " << std::endl;;
	std::cout << "\t->";
	std::cin >> index >> vertical >> horizontal;
	std::cin.ignore();

	if (shapes.translate(index - 1, vertical, horizontal))
	{
		std::cout << "\tTranslated " << index << std::endl;;
	}
	else
	{
		std::cout << "There is no figure number " << index << "!" << std::endl;
	}
}
void SVGFile::translateAll()
{
	size_t vertical, horizontal;
	std::cout << "\tEnter vertical and horizontal translate: ";
	std::cin >> vertical >> horizontal;
	std::cin.ignore();

	if (shapes.getCount() > 0)
	{
		shapes.translate(vertical, horizontal);
		std::cout << "\tTranslated all figures" << std::endl;
	}
	else
	{
		std::cout << "\tNo figures!" << std::endl;
	}
}
void SVGFile::saveInFile(const MyString& fileName)
{
	std::ofstream file(fileName.c_str(), std::ios::trunc);
	if (!file.is_open())
	{
		std::cout << "\tError opening the file!" << std::endl;
		return;
	}
	shapes.saveInFile(file);
	std::cout << "\tSuccessfully saved the changes to " << fileName.c_str() << std::endl;
	file.close();
}
void SVGFile::withinReactangle() const
{
	int x, y, width, height;
	std::cout << "\tEnter x, y, width and height of the reactangle in that order: " << std::endl;
	std::cout << "\t-> ";
	std::cin >> x >> y >> width >> height;
	std::cin.ignore();
	shapes.withinReac(x, y, width, height);
}
void SVGFile::withinCircle() const
{
	int x, y, radius;
	std::cout << "\tEnter x, y, radius of the circle in that order: " << std::endl;
	std::cout << "\t-> ";
	std::cin >> x >> y >> radius;
	std::cin.ignore();
	shapes.withinCircle(x, y, radius);
}
void SVGFile::withinLine() const
{
	int x1, y1, x2, y2;
	std::cout << "\tEnter x1, y1, x2, y2 of the reactangle in that order: " << std::endl;
	std::cout << "\t-> ";
	std::cin >> x1 >> y1 >> x2 >> y2;
	std::cin.ignore();
	shapes.withinLine(x1, y1, x2, y2);
}
void SVGFile::pointIn() const
{
	int x, y;
	std::cout << "\tEnter x, y of the point in that order: " << std::endl;
	std::cout << "\t-> ";
	std::cin >> x >> y;
	std::cin.ignore();
	shapes.getShapesThatContainPoint(x, y);
}

void SVGFile::menu() const
{
	std::cout << std::endl;
	std::cout << " Write one of the following commands for figures and press enter: " << std::endl;
	std::cout << "\tPrint" << std::endl;
	std::cout << "\tCreate rectangle" << std::endl;
	std::cout << "\tCreate circle" << std::endl;
	std::cout << "\tCreate line" << std::endl;
	std::cout << "\tErase" << std::endl;
	std::cout << "\tTranslate" << std::endl;
	std::cout << "\tTranslate all figures" << std::endl;
	std::cout << "\tWithin reactangle" << std::endl;
	std::cout << "\tWithin circle" << std::endl;
	std::cout << "\tWithin line" << std::endl;
	std::cout << "\tPointIn" << std::endl;
	std::cout << "\tAreas" << std::endl;
	std::cout << "\tPerimeters" << std::endl;
	std::cout << "\tSave" << std::endl;
	std::cout << "\tExit" << std::endl;
}

void SVGFile::interface()
{
	MyString fileName;
	std::cout << "\t>open ";
	std::cin >> fileName;

	std::ifstream file(fileName.c_str());
	if (!file.is_open())
	{
		std::cout << "Error opening the file!" << std::endl;
		return;
	}
	std::cout << "\tSuccessfully opened " << fileName.c_str() << std::endl;

	shapes.readSVGfile(file);

	file.close();

	menu();
	std::cout << std::endl;

	MyString command;
	std::cout << "\t-> ";
	std::cin >> command;

	while (!(command == "Exit"))
	{

		if (command == "Print")
		{
			shapes.printAll();
			std::cout << std::endl;
		}
		else if (command == "Create rectangle")
		{
			createReactangle();
			std::cout << std::endl;
		}
		else if (command == "Create circle")
		{
			createCircle();
			std::cout << std::endl;
		}
		else if (command == "Create line")
		{
			createLine();
			std::cout << std::endl;
		}
		else if (command == "Erase")
		{
			erase();
			std::cout << std::endl;
		}
		else if (command == "Translate")
		{
			translate();
			std::cout << std::endl;
		}
		else if (command == "Translate all figures")
		{
			translateAll();
			std::cout << std::endl;
		}
		else if (command == "Within reactangle")
		{
			withinReactangle();
			std::cout << std::endl;
		}
		else if (command == "Within circle")
		{
			withinCircle();
			std::cout << std::endl;
		}
		else if (command == "Within line")
		{
			withinLine();
			std::cout << std::endl;
		}
		else if (command == "PointIn")
		{
			pointIn();
			std::cout << std::endl;
		}
		else if (command == "Areas")
		{
			shapes.printAreas();
			std::cout << std::endl;
		}
		else if (command == "Perimeters")
		{
			shapes.printPers();
			std::cout << std::endl;
		}
		else if (command == "Save")
		{
			saveInFile(fileName);
			std::cout << std::endl;
		}
		std::cout << "\t-> ";
		std::cin >> command;
	}

	return;
}