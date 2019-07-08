#pragma once
#include "animalAbstractFactory.h"
#include "animalConcreteProduct.h"
class pigFactory : public animalAbstractFactory {
	animalAbstractProduct* createAnimal() {
		return new pig();
	}
};

class dogFactory : public animalAbstractFactory {
	animalAbstractProduct* createAnimal() {
		return new dog();
	}
};

class catFactory : public animalAbstractFactory {
	animalAbstractProduct* createAnimal() {
		return new cat();
	}
};