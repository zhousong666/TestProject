#pragma once
#include "animalAbstractProduct.h"

class animalAbstractFactory {
public:
	virtual animalAbstractProduct* createAnimal() = 0;
};