#pragma once
#include "animalAbstractProduct.h"
#include <string>
class pig : public animalAbstractProduct {
public:
	std::string getAnimalName() {
		return "I am a pig!";
	}
};

class cat : public animalAbstractProduct {
public:
	std::string getAnimalName() {
		return "I am a cat!";
	}
};

class dog : public animalAbstractProduct {
public:
	std::string getAnimalName() {
		return "I am a dog!";
	}
};