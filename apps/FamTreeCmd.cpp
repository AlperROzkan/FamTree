// FamTreeCmd.cpp : Command line app for family genealogy management
#include <iostream>
#include <vector>
#include "person.hpp"

using namespace std;

unsigned int Person::id = 0;


int main()
{
	int input;

	// Initialize 
	string firstname;
	string lastname;
	string gender;

	// Vector of people
	vector<Person *> people;

	while (true) {
		cout << "FamTree:" << endl;
		cout << "1) Add a person" << endl;
		cout << "0) Quit the app" << endl;
		cin >> input;

		switch (input)
		{
		case 0:
			// Quits the app
			return 0;
		case 1:
			// Adds a person to the pool of people
			cout << "Input firstname : ";
			cin >> firstname;
			cout << "Input lastname : ";
			cin >> lastname;
			cout << "Input gender : ";
			cin >> gender;
			people.push_back(new Person(firstname, lastname, gender));
			cout << endl;
			break;
		case 2:
			// Add a relation between two people
			break;
		default:
			return 0;
		}
	}
}
