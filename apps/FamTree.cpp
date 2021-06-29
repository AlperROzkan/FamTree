// FamTree.cpp : définit le point d'entrée de l'application.
//
#include <iostream>
#include "person.hpp"

using namespace std;

unsigned int Person::id = 0; 

int main()
{
	Person* john = new Person("John", "Goodman", Gender::male);
	Person* helen = new Person("Helen", "Trueman", Gender::female);
	Person* paul = new Person("Paul", "Goodman", Gender::male);
	Person* eliott = new Person("Eliott", "Goodman", Gender::male);

	Person* jacob = new Person("Jacob", "Woodman", Gender::male);
	Person* anna = new Person("Anna", "Wigger", Gender::female);
	Person* elise = new Person("Elise", "Woodman", Gender::female);

	Person* cory = new Person("Cory", "Goodman", Gender::male);
	
	john->addChild(paul);
	paul->addParent(john);
	return 0;
}
