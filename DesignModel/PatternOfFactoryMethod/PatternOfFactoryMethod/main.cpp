#include "animalConcreteFactory.h"
#include "animalConcreteProduct.h"
#include <iostream>
#include <string>
int main() {
	animalAbstractFactory *pFactory = new dogFactory();
	animalAbstractProduct *dog = pFactory->createAnimal();
	std::cout << "Dog Factory: s" + dog->getAnimalName() << std::endl;

	delete pFactory;
	pFactory = NULL;
	pFactory = new catFactory();
	animalAbstractProduct *cat = pFactory->createAnimal();
	std::cout << "Cat Factory: s" + cat->getAnimalName() << std::endl;

	delete pFactory;
	pFactory = NULL;
	pFactory = new pigFactory();
	animalAbstractProduct *pig = pFactory->createAnimal();
	std::cout << "Pig Factory: s" + pig->getAnimalName() << std::endl;
	return 0;
}