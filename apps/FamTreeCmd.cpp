// FamTreeCmd.cpp : Command line app for family genealogy management
#include <iostream>
#include <vector>
#include <fam_tree/person.hpp>

using namespace std;

unsigned int Person::id = 0;

string displayPeople(vector<Person*> people) {
	// Counter
	int count = 1;

	// string to return
	string strReturn;

	for (auto value : people) {
		strReturn = strReturn + to_string(count) + " : " + value->printPerson();
		count++;
	}
	return strReturn;
}

int main()
{
	// Input to make a choice in the workflow 
	int input;

	// Boolean to verify if the user does not input a bad choice
	bool inputCorrect = false;

	// Initialize strings for inputing during the workflow
	string firstname;
	string lastname;
	string gender;

	// Relationship to add between the two people (choice 2)
	Relation relationLink = Relation::error;

	// Main vector of people, everyone will be stocked in this vector
	vector<Person*> people;

	// Another vector, to help add relationships
	vector<Person*> helperVec;

	while (true) {
		cout << "FamTree:" << endl;
		cout << "1) Add a person" << endl;
		cout << "2) Add a relation between two people" << endl;
		cout << "3) Prints all the people registered" << endl;
		cout << "0) Quit the app" << endl;
		cin >> input;

		switch (input)
		{
		case 0:
			/* Quits the app */
			return 0;
		case 1:
			/* Adds a person to the pool of people */
			cout << "Add a person to the pool of people" << endl;

			// Input firstname
			cout << "Input firstname : ";
			cin >> firstname;

			// Input lastname 
			cout << "Input lastname : ";
			cin >> lastname;

			// Input gender
			cout << "Input gender : ";
			cin >> gender;

			// Add the new person to pool
			people.push_back(new Person(firstname, lastname, gender));
			cout << endl;
			break;
		case 2:
			/* Add a relation between two people */
			cout << "Add a relation between two people" << endl;

			// Display everyone 
			cout << displayPeople(people) << endl;

			// Choose the link type between the two people
			cout << "Choose the relationship between the two people (Careful : The order is important)" << endl;
			cout << "0) Cancel" << endl;
			cout << "1) Parent/Child" << endl;
			cout << "2) Spouses" << endl;
			cout << "Your Choice : ";
			cin >> input;

			// While the input is incorrect we ask for the answer
			while (!inputCorrect) {
				switch (input)
				{
				case 0:
					/* Come back to main menu */
					cout << "Canceled the operation, coming back to main menu" << endl;
					inputCorrect = true;
					break;
				case 1:
					/* Parent/Child relationship */
					cout << "Parent and child" << endl;
					relationLink = Relation::parent;
					inputCorrect = true;
					break;
				case 2:
					/* Spouse */
					cout << "Spouse" << endl;
					relationLink = Relation::spouse;
					inputCorrect = true;
					break;
				}
			}

			// Choose the first person to link
			cout << "Choose the first person : " << endl;
			cin >> input;
			helperVec.push_back(people[input]);

			// Choose the second person to link
			cout << "Choose the second person : " << endl;
			cin >> input;
			helperVec.push_back(people[input]);

			// Match relationLink with the related action

			switch (relationLink)
			{
			case Relation::parent:
				helperVec[0]->addChild(helperVec[1]);
				break;
			case Relation::spouse:
				helperVec[0]->addSpouse(helperVec[1]);
				break;
			case Relation::error:
				cout << "An error happened, aborting" << endl;
				break;
			default:
				break;
			}

			break;
		case 3:
			/* Prints all the people */
			std::cout << displayPeople(people);
			break;
		case 4:
			/* Save the people in a file */
			break;
		case 5:
			/* Load the people from a file */
			break;
		default:
			return 0;
		}
	}
}
