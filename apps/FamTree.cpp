// FamTree.cpp : définit le point d'entrée de l'application.
//
#include <iostream>
#include "person.hpp"

using namespace std;

unsigned int Person::id = 0; 

int main()
{
	Person pers = Person();
	cout << pers << endl;
	return 0;
}
