#include "ShapeCollection.h"

class SVGFile
{
	ShapeCollection shapes;

public:

	void menu() const;

	void createReactangle();
	void createCircle();
	void createLine();
	void erase();
	void translate();
	void translateAll();
	void saveInFile(const MyString& name);
	void withinReactangle() const;
	void withinCircle() const;
	void withinLine() const;
	void pointIn() const;

	void interface();
};