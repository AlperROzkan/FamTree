#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include <person.hpp>

unsigned int Person::id = 0;

class PersonTest : public testing::Test {
protected:
	Person* johnDoe = new Person("John", "Doe", Gender::other);
	Person* jackDoe = new Person("Jack", "Doe", Gender::male);
	Person* janePoe = new Person("Jane", "Poe", Gender::female);
	Person* paulDoe = new Person("Paul", "Poe", Gender::male);
	json jsonJohnDoe;

	virtual void SetUp() override {
		jsonJohnDoe["firstname"] = "John";
		jsonJohnDoe["lastname"] = "Doe";
		jsonJohnDoe["gender"] = "Male";
	}

	virtual void TearDown() override {

	}
};

TEST_F(PersonTest, PersonInstanciate1) {
	EXPECT_EQ("John", johnDoe->getFirstname());
	EXPECT_EQ("Doe", johnDoe->getLastname());
	EXPECT_EQ("other", johnDoe->getGender());
}

TEST_F(PersonTest, PersonAddParent1) {
	johnDoe->addParent(jackDoe);
	EXPECT_TRUE(johnDoe->getParents().contains(jackDoe));
	EXPECT_TRUE(jackDoe->getChildren().contains(johnDoe));
}

TEST_F(PersonTest, PersonAddChildren1) {
	janePoe->addChild(paulDoe);
	EXPECT_TRUE(janePoe->getChildren().contains(paulDoe));
	EXPECT_TRUE(paulDoe->getParents().contains(janePoe));
}

TEST_F(PersonTest, PersonAddSpouse1) {
	janePoe->addSpouse(johnDoe);
	EXPECT_TRUE(johnDoe->getSpouse().contains(janePoe));
	EXPECT_TRUE(janePoe->getSpouse().contains(johnDoe));
}

TEST_F(PersonTest, PersonSerialize1) {
	json j = johnDoe->serializeSimplePerson();
	EXPECT_EQ(j["firstname"], johnDoe->getFirstname());
	EXPECT_EQ(j["lastname"], johnDoe->getLastname());
	EXPECT_EQ(j["gender"], johnDoe->getGender());
}

TEST_F(PersonTest, PersonSerialize2) {
	johnDoe->addParent(jackDoe);
	json j = johnDoe->serializePerson();
	std::cout << *jackDoe << std::endl << j << std::endl;
}


TEST_F(PersonTest, PersonDeserialize1) {
	Person* p = Person::deserializeSimplePerson(jsonJohnDoe);
	EXPECT_EQ(jsonJohnDoe["firstname"], p->getFirstname());
	EXPECT_EQ(jsonJohnDoe["lastname"], p->getLastname());
	EXPECT_EQ(jsonJohnDoe["gender"], p->getGender());
}

TEST_F(PersonTest, PersonSerDePerson1) {
	json j = johnDoe->serializeSimplePerson();
	Person* p = Person::deserializeSimplePerson(j);
	EXPECT_EQ(p->getFirstname(), johnDoe->getFirstname());
	EXPECT_EQ(p->getLastname(), johnDoe->getLastname());
	EXPECT_EQ(p->getGender(), johnDoe->getGender());
}
