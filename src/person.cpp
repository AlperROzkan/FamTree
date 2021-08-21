#include <person.hpp>

Person::Person() : Person("John", "Doe", Gender::other)
{
}

Person::~Person()
{
	firstname.erase(firstname.begin(), firstname.end());
	lastname.erase(lastname.begin(), lastname.end());
	gender.erase(gender.begin(), gender.end());
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
	this->id_person = id;
	id++;
}

Person::Person(std::string firstname, std::string lastname, std::string gender)
{
	this->firstname = firstname;
	this->lastname = lastname;
	this->gender = gender;
	this->id_person = id;
	id++;
}

Person::Person(unsigned int id, std::string firstname, std::string lastname, std::string gender)
{
	this->id_person = id;
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
	os << "id : " << person.id_person << std::endl;
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

std::map<Relation, std::set<int>> Person::getRelations() {
	return this->relations;
}

void Person::addParent(Person* parent) {
	// Add corresponding relations to each of the people involved
	this->addRelation(Relation::parent, parent->getId());
	parent->addRelation(Relation::child, this->getId());
}

void Person::addChild(Person* person) {
	this->addRelation(Relation::child, person->getId());
	person->addRelation(Relation::parent, this->getId());
}

void Person::addSpouse(Person* person) {
	this->addRelation(Relation::spouse, person->getId());
	person->addRelation(Relation::spouse, this->getId());
}

unsigned int Person::getId()
{
	return this->id_person;
}

std::set<int> Person::getParents() {
	return this->getSpecificRelation(Relation::parent);
}

std::set<int> Person::getChildren() {
	return this->getSpecificRelation(Relation::child);
}

std::set<int> Person::getSpouse() {
	return this->getSpecificRelation(Relation::spouse);
}

std::string Person::printPerson() {
	std::string str;
	str = "\n---\n" + this->firstname + "\n" + this->lastname + "\n" + this->gender + "\n---\n";

	return str;
}

json Person::serializeSimplePerson()
{
	json j;
	// Simple attributes
	j["firstname"] = this->firstname;
	j["lastname"] = this->lastname;
	j["gender"] = this->gender;
	return j;
}

Person* Person::deserializeSimplePerson(json j)
{
	return new Person(j["firstname"].get<std::string>(), j["lastname"].get<std::string>(), j["gender"].get<std::string>());
}

json Person::serializePerson()
{
	json j_set;
	json returnJson = this->serializeSimplePerson();
	returnJson["id"] = this->id_person;

	std::map<Relation, std::set<int>>::iterator itExtern;

	// To go through the map
	for (itExtern = this->relations.begin(); itExtern != this->relations.end(); itExtern++) {
		// To go through the set
		for (auto person : itExtern->second) {
			j_set.push_back(person);
		}

		switch (itExtern->first)
		{
		case Relation::parent:
			returnJson["relations"]["parent"] = j_set;
			break;
		case Relation::child:
			returnJson["relations"]["child"] = j_set;
			break;
		case Relation::spouse:
			returnJson["relations"]["spouse"] = j_set;
			break;
		default:
			break;
		}
	}
	return returnJson;
}

Person* Person::deserializePerson(json j)
{
	// The reference of the person to return at the end of the function
	Person* returnPerson = new Person(
		j["id"].get<unsigned int>(),
		j["firstname"].get<std::string>(),
		j["lastname"].get<std::string>(),
		j["gender"].get<std::string>());

	// Register the relations of the person in a json for better handling
	json relations = j["relations"];

	// Go through each of the relation 
	for (json::iterator it = relations.begin(); it != relations.end(); ++it) {
		// Go through each of the ids of the people in the relation
		for each (auto var in it.value())
		{
			//returnPerson->addRelation(famTree::convertToRelationEnum(it.key()), var);
		}
	}
	return returnPerson;
}

void Person::addRelation(Relation relation, unsigned int person) {
	this->relations[relation].insert(person);
}

std::set<int> Person::getSpecificRelation(Relation relation) {
	return this->relations[relation];
}