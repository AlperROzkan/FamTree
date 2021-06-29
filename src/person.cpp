#include "person.hpp"
#include "gender.hpp"
#include <string>
#include <variant>

Person::Person() : Person("John", "Doe", Gender::other)
{
}

Person::~Person()
{
	firstname.erase(firstname.begin(), firstname.end());
	lastname.erase(lastname.begin(), lastname.end());
}

Person::Person(std::string firstname, std::string lastname, Gender gender)
{
	this->firstname = firstname;
	this->lastname = lastname;
	switch (gender)
	{
	case Gender::male:
		this->gender = "male";
		break;
	case Gender::female:
		this->gender = "female";
		break;
	default:
		this->gender = "other";
		break;
	}
	//this->relations = std::map<Relation, std::set<Person>>();
	this->id_person = id;
	id++;
}

Person::Person(std::string firstname, std::string lastname, std::string gender)
{
	this->firstname = firstname;
	this->lastname = lastname;
	this->gender = gender;
}

Person::Person(const Person& otherPerson)
{
	firstname = otherPerson.firstname;
	lastname = otherPerson.lastname;
	gender = otherPerson.gender;
}

Person::Person(Person&& otherPerson) noexcept
{
	firstname = std::move(otherPerson.firstname);
	lastname = std::move(otherPerson.lastname);
	gender = std::move(otherPerson.gender);
}

Person& Person::operator=(const Person& otherPerson)
{
	this->firstname = otherPerson.firstname;
	this->lastname = otherPerson.lastname;
	this->gender = otherPerson.gender;

	return *this;
}

Person& Person::operator=(Person&& otherPerson) noexcept
{
	firstname = std::move(otherPerson.firstname);
	lastname = std::move(otherPerson.lastname);
	gender = std::move(otherPerson.gender);

	return *this;
}

std::ostream& operator<<(std::ostream& os, Person& person)
{
	os << "----" << std::endl;
	os << "firstname : " << person.firstname << std::endl;
	os << "lastname : " << person.lastname << std::endl;
	os << "gender : " << person.gender << std::endl;
	return os;
}

std::string Person::getFirstname() {
	return this->firstname;
}

std::string Person::getLastname() {
	return this->lastname;
}

std::string Person::getGender() {
	return this->gender;
}

std::map<Relation, std::set<Person*>> Person::getRelations() {
	return this->relations;
}


void Person::addRelation(Relation relation, Person* person) {
	this->relations[relation].insert(person);
}

void Person::addParent(Person* person) {
	this->addRelation(Relation::parent, person);
}

void Person::addChild(Person* person) {
	this->addRelation(Relation::child, person);
}

std::set<Person*> Person::getParents() {
	return this->relations[Relation::parent];
}

void Person::printSet(Relation relation) {
	for each (auto var in this->relations[Relation::parent])
	{
		std::cout << var->getFirstname() << std::endl;
	}
}