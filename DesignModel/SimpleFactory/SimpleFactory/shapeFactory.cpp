#include "shapeFactory.h"
#include "shape.h"
#include "rectangle.h"
#include "square.h"
#include "circle.h"
#include <string>


shape* shapeFacetory::getShape(std::string shapeType)
{
	if (shapeType == "circle") {
		return new circle();
	}	
	else if (shapeType == "rectangle") {
		return new rectangle();

	}
	else if (shapeType == "square") {
		return new square();
	}
}

