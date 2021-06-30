#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "../include/person.hpp"

unsigned int Person::id = 0;

class PersonTest : public testing::Test {
protected:
	Person* johnDoe = new Person("John", "Doe", Gender::other);
	Person* jackDoe = new Person("Jack", "Doe", Gender::male);
	Person* janePoe = new Person("Jane", "Poe", Gender::female);
	Person* paulDoe = new Person("Paul", "Poe", Gender::male);
	
	virtual void SetUp() override {

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