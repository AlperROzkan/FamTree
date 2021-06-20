// person.hpp
#ifndef PERSON_HPP
#define PERSON_HPP


#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "gender.hpp"
#include "relation.hpp"

class Person
{
public:
	// static unsigned int id; // static id to keep track of the number of people
	unsigned int id_person; // id of the person

	// Default constructor
	Person();

	// Destructor
	~Person();

	// Initializes the Person with a firstname, lastname and a specified gender from a Gender enumeration.
	// firstname : The firstname of the Person.
	// lastname : The lastname of the Person.
	// gender : The gender of a person. Specified in an enumeration
	Person(std::string firstname, std::string lastname, Gender gender);

	// Initializes the Person with a firstname, lastname and a specified gender from a Gender string. 
	// firstname : The firstname of the Person.
	// lastname : The lastname of the Person.
	// gender : The gender of a person.
	Person(std::string firstname, std::string lastname, std::string gender);

	// Copy Constructor
	Person(const Person&); // Recopy

	// Move Constructor
	Person(Person&&) noexcept; // Move

	Person& operator=(const Person&);
	Person& operator=(Person&&) noexcept;

	friend std::ostream& operator<<(std::ostream& os, Person& person);

private:
	std::string firstname;
	std::string lastname;
	// a person can specify the gender themselves, or can choose it from a list
	std::string gender;
};

#endif // !PERSON_HPP
