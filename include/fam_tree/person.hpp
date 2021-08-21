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
#include <person.hpp>
#include <nlohmann\json.hpp>

#include "gender.hpp"
#include "relation.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class Person
{
public:
	/// Attributes
	static unsigned int id; // static id to keep track of the number of people

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

	/// <summary>
	/// Initializes a person with an id
	/// </summary>
	/// <param name="id">Id of the person</param>
	/// <param name="firstname">The firstname of the Person.</param>
	/// <param name="lastname">The lastname of the Person.</param>
	/// <param name="gender">The gender of a person.</param>
	Person(unsigned int id, std::string firstname, std::string lastname, std::string gender);

	// Copy Constructor
	Person(const Person&); // Recopy

	// Move Constructor
	Person(Person&&) noexcept; // Move

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	Person& operator=(const Person&);

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	Person& operator=(Person&&) noexcept;

	/// <summary>
	/// The operator to print the person
	/// </summary>
	/// <param name="os">The buffer to print to</param>
	/// <param name="person">The person to print</param>
	/// <returns>The stream where the person will be printed</returns>
	friend std::ostream& operator<<(std::ostream& os, Person& person);

	/// <summary> 
	/// Firstname getter
	/// </summary>
	/// <returns>The firstname of the person</returns>
	std::string getFirstname();

	/// <summary>
	/// Lastname getter
	/// </summary>
	/// <returns>The lastname of the person</returns>
	std::string getLastname();

	/// <summary>
	/// Gender getter
	/// </summary>
	/// <returns></returns>
	std::string getGender();

	/// <summary>
	/// Relations getter
	/// </summary>
	/// <returns>The relations of the person</returns>
	std::map<Relation, std::set<int>> getRelations();

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
	/// Gets the id of the person
	/// </summary>
	/// <returns>The id of the person</returns>
	unsigned int getId();

	/// <summary>
	/// Gets the parents of this person
	/// </summary>
	/// <returns></returns>
	std::set<int> getParents();

	/// <summary>
	/// Gets the children of this person 
	/// </summary>
	/// <returns></returns>
	std::set<int> getChildren();

	/// <summary>
	/// Gets the spouse of this person
	/// </summary>
	/// <returns></returns>
	std::set<int> getSpouse();

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

	/// <summary>
	/// Serialize this person
	/// </summary>
	/// <returns></returns>
	json serializePerson();

	/// <summary>
	/// Returns a person from a json
	/// </summary>
	/// <param name="j">Json representing a person</param>
	/// <returns></returns>
	static Person* deserializePerson(json j);

private:
	/// Attributes
	unsigned int id_person; // id of the person
	std::string firstname;
	std::string lastname;
	std::string gender; // a person can specify the gender themselves, or can choose it from a list
	std::map<Relation, std::set<int>> relations;

	/// Methods

	/// <summary>
	/// Adds a relation with a person to this person
	/// </summary>
	/// <param name="relation">The relationship with the person</param>
	/// <param name="person">The number linked to this person</param>
	void addRelation(Relation relation, unsigned int person);

	/// <summary>
	/// Gets the specific relation of this person
	/// </summary>
	/// <returns>A set containing the specific relation of this person</returns>
	std::set<int> getSpecificRelation(Relation relation);
};

#endif // !PERSON_HPP
