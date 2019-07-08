#pragma once
#pragma once
#include <string>
#include "shape.h"

class shapeFacetory {
public:
	shape* getShape(std::string shapeType);
};