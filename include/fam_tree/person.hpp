// person.hpp
#ifndef PERSON_HPP
#define PERSON_HPP


#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <variant>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "gender.hpp"
#include "relation.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class Person
{
public:
	/// Attributes
	static unsigned int id; // static id to keep track of the number of people
	unsigned int id_person; // id of the person

	/// Methods
	// Default constructor
	Person();

	// Destructor
	~Person();

	/// <summary>
	/// Constructor with a gender enum
	/// </summary>
	/// <param name="firstname">The firstname of the Person.</param>
	/// <param name="lastname">The lastname of the Person.</param>
	/// <param name="gender">The gender of a person. Specified in an enumeration.</param>
	Person(std::string firstname, std::string lastname, Gender gender);

	/// <summary>
	/// Initializes the Person with a firstname, lastname and a specified gender from a Gender string. 
	/// </summary>
	/// <param name="firstname">The firstname of the Person.</param>
	/// <param name="lastname">The lastname of the Person.</param>
	/// <param name="gender">The gender of a person.</param>
	Person(std::string firstname, std::string lastname, std::string gender);

	// Copy Constructor
	Person(const Person&); // Recopy

	// Move Constructor
	Person(Person&&) noexcept; // Move

	Person& operator=(const Person&);
	Person& operator=(Person&&) noexcept;
	friend std::ostream& operator<<(std::ostream& os, Person& person);

	// Firstname getter
	std::string getFirstname();

	// Lastname getter
	std::string getLastname();

	// Gender getter
	std::string getGender();

	// Relations getter
	std::map<Relation, std::set<Person*>> getRelations();

	/// <summary>
	/// Adds a father to this person 
	/// </summary>
	/// <param name="parent">Father to this person</param>
	void addParent(Person* parent);

	/// <summary>
	/// Adds a child to this person
	/// </summary>
	/// <param name="person">Child to this person</param>
	void addChild(Person* person);

	/// <summary>
	/// Adds a spouse to this person
	/// </summary>
	/// <param name="person">Spouse of this person</param>
	void addSpouse(Person* person);

	/// <summary>
	/// Prints the sets concerned
	/// </summary>
	/// <param name="relation">The relation whose set must prints</param>
	void printSet(Relation relation);

	/// <summary>
	/// Gets the parents of this person
	/// </summary>
	/// <returns></returns>
	std::set<Person*> getParents();

	/// <summary>
	/// Gets the children of this person 
	/// </summary>
	/// <returns></returns>
	std::set<Person*> getChildren();

	/// <summary>
	/// Gets the spouse of this person
	/// </summary>
	/// <returns></returns>
	std::set<Person*> getSpouse();

	/// <summary>
	/// Prints a person 
	/// </summary>
	std::string printPerson();

	/// <summary>
	/// Serialize this person without relations
	/// </summary>
	/// <returns>A json containing all the info for this person besides their relations</returns>
	json serializeSimplePerson();

	/// <summary>
	/// Converts a person from json without relations
	/// </summary>
	/// <param>Json representing a person without his relations</param>
	/// <returns>A person without </returns>
	static Person* deserializeSimplePerson(json j); 

private:
	/// Attributes
	std::string firstname;
	std::string lastname;
	std::string gender; // a person can specify the gender themselves, or can choose it from a list
	std::map<Relation, std::set<Person*>> relations;

	/// Methods

	/// <summary>
	/// Adds a relation with a person to this person
	/// </summary>
	/// <param name="relation">The relationship with the person</param>
	/// <param name="person">The person linked to this person</param>
	void addRelation(Relation relation, Person* person);

	/// <summary>
	/// Gets the specific relation of this person
	/// </summary>
	/// <returns>A set containing the specific relation of this person</returns>
	std::set<Person*> getSpecificRelation(Relation relation);
};

#endif // !PERSON_HPP
