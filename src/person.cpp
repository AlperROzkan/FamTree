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
	//this->relation = Relations();

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
