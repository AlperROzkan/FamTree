#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include <vector>
#include <person.hpp>
#include <utils.hpp>

unsigned int Person::id = 0;
std::set<Person*> Person::peopleHolder;

class PersonTest : public testing::Test {
protected:
	Person* johnDoe;
	Person* jackDoe;
	Person* janePoe;
	Person* paulDoe;
	json jsonJohnDoe;

	virtual void SetUp() override {
		Person::id = 0;
		johnDoe = new Person("John", "Doe", Gender::other);
		jackDoe = new Person("Jack", "Doe", Gender::male);
		janePoe = new Person("Jane", "Poe", Gender::female);
		paulDoe = new Person("Paul", "Poe", Gender::male);

		jsonJohnDoe["id"] = 420;
		jsonJohnDoe["firstname"] = "John";
		jsonJohnDoe["lastname"] = "Doe";
		jsonJohnDoe["gender"] = "Male";
	}

	virtual void TearDown() override {
		delete johnDoe;
		delete jackDoe;
		delete janePoe;
		delete paulDoe;
	}
};

TEST_F(PersonTest, personInstanciate1) {
	EXPECT_EQ("John", johnDoe->getFirstname());
	EXPECT_EQ("Doe", johnDoe->getLastname());
	EXPECT_EQ("other", johnDoe->getGender());
}

TEST_F(PersonTest, personAddParent1) {
	johnDoe->addParent(jackDoe);
	EXPECT_TRUE(johnDoe->getParents().contains(jackDoe->getId()));
	EXPECT_TRUE(jackDoe->getChildren().contains(johnDoe->getId()));
}

TEST_F(PersonTest, personAddChildren1) {
	janePoe->addChild(paulDoe);
	EXPECT_TRUE(janePoe->getChildren().contains(paulDoe->getId()));
	EXPECT_TRUE(paulDoe->getParents().contains(janePoe->getId()));
}

TEST_F(PersonTest, personAddSpouse1) {
	janePoe->addSpouse(johnDoe);
	EXPECT_TRUE(johnDoe->getSpouse().contains(janePoe->getId()));
	EXPECT_TRUE(janePoe->getSpouse().contains(johnDoe->getId()));
}

TEST_F(PersonTest, personSerialize1) {
	json j = johnDoe->serializeSimplePerson();
	EXPECT_EQ(j["firstname"], johnDoe->getFirstname());
	EXPECT_EQ(j["lastname"], johnDoe->getLastname());
	EXPECT_EQ(j["gender"], johnDoe->getGender());
}

TEST_F(PersonTest, personSerialize2) {
	johnDoe->addParent(jackDoe);
	json j = johnDoe->serializePerson();
	EXPECT_EQ(j["id"], johnDoe->getId());
	EXPECT_EQ(j["firstname"], johnDoe->getFirstname());
	EXPECT_EQ(j["lastname"], johnDoe->getLastname());
	EXPECT_EQ(j["gender"], johnDoe->getGender());
	EXPECT_EQ(j["relations"]["parent"][0], jackDoe->getId());

}

TEST_F(PersonTest, personDeserialize1) {
	Person* p = Person::deserializeSimplePerson(jsonJohnDoe);
	EXPECT_EQ(jsonJohnDoe["firstname"], p->getFirstname());
	EXPECT_EQ(jsonJohnDoe["lastname"], p->getLastname());
	EXPECT_EQ(jsonJohnDoe["gender"], p->getGender());
	delete p;
}

TEST_F(PersonTest, personDeserialize2) {
	jsonJohnDoe["relations"]["child"] = { 42 };
	Person* p = Person::deserializePerson(jsonJohnDoe);
	EXPECT_EQ(jsonJohnDoe["firstname"], p->getFirstname());
	EXPECT_EQ(jsonJohnDoe["lastname"], p->getLastname());
	EXPECT_EQ(jsonJohnDoe["gender"], p->getGender());
	EXPECT_TRUE(p->getChildren().contains(42));
	delete p;
}

TEST_F(PersonTest, personSerDePerson1) {
	json j = johnDoe->serializeSimplePerson();
	Person* p = Person::deserializeSimplePerson(j);
	EXPECT_EQ(p->getFirstname(), johnDoe->getFirstname());
	EXPECT_EQ(p->getLastname(), johnDoe->getLastname());
	EXPECT_EQ(p->getGender(), johnDoe->getGender());
	delete p;
}

/// TODO
TEST(PersonToFileTest, personSerializeToFile1) {
	// Initialize the test crowd
	Person::id = 0;
	Person* john = new Person("John", "Doe", Gender::male);
	Person* helen = new Person("Helen", "Smith", Gender::female);
	Person* paul = new Person("Paul", "Doe", Gender::male);
	Person* eliott = new Person("Eliott", "Doe", Gender::male);

	// Serialize them to file
	fs::path pathToTestFile = fs::path(PROJECT_PATH) /= "tests/serializeToFileTest.txt";
	Person::serializeToFile(pathToTestFile);

	// Delete the test crowd
	delete john;
	delete helen;
	delete paul;
	delete eliott;

	FAIL() << "Not implemented";
}

/// TODO
TEST(PersonToFileTest, personDeserializeFromFile) {
	Person::id = 0;

	// firstnames, lastnames, and genders to test in order
	std::vector<std::string> firstnames = { "John", "Eliott", "Helen", "Paul" };
	std::vector<std::string> lastnames = { "Doe", "Doe", "Smith", "Doe" };

	fs::path pathToTestFile = fs::path(PROJECT_PATH) /= "tests/deserializeFromFileTest.txt";
	std::set<Person*> testSet = Person::deserializeFromFile(pathToTestFile);
	FAIL() << "Not Implemented";
}
