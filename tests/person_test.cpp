#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "../include/person.hpp"

unsigned int Person::id = 0;

class PersonTest : public testing::Test {
protected:
	Person* johnDoe = new Person("John", "Doe", Gender::other);
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
	Person* jackDoe = new Person("Jack", "Doe", Gender::male);
	johnDoe->addParent(jackDoe);
	EXPECT_TRUE(johnDoe->getSpecificRelation(Relation::parent).contains(jackDoe));
	EXPECT_TRUE(jackDoe->getSpecificRelation(Relation::child).contains(johnDoe));
} 