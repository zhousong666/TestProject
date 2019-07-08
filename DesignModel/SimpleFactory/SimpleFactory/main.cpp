#include "shape.h"
#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include "shapeFactory.h"
int main() {
	shapeFacetory* factory = new shapeFacetory;
	shape* ps = factory->getShape("circle");
	ps->draw();
	return 0;
	}