#include "utils.hpp"

Relation famTree::convertToRelationEnum(std::string enumStr)
{
	if (enumStr == "child") return Relation::child;
	else if (enumStr == "parent") return Relation::parent;
	else if (enumStr == "spouse") return Relation::spouse;
	else if (enumStr == "sibling") return Relation::sibling;

	return Relation::error;
}

void famTree::serializeToFile(std::vector<Person*> people, fs::path pathToFile)
{
	json jsonOfVector;

	std::ofstream myFile;
	myFile.open(pathToFile);
	size_t peopleCounter = 0;

	for each (Person* person in people)
	{	
		jsonOfVector["people"][peopleCounter] = person->serializePerson();
		peopleCounter++;
	}

	std::cout << jsonOfVector;
	
	myFile.close();
}

void famTree::writeToFile(std::string message, fs::path pathToFile)
{
	std::ofstream fileToWriteIn(pathToFile);
	fileToWriteIn << message;
	fileToWriteIn.close();
}

std::string famTree::readFromFile(fs::path path)
{
	std::ifstream input_file(path);
	if (!input_file.is_open()) {
		std::cerr << "Could not open the file - '"
			<< path << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}