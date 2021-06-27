#include "../include/person.hpp"
#include <gtest/gtest.h>
#include <iostream>

unsigned int Person::id = 0;

// Demonstrate some basic assertions.
TEST(FamTreeTests, PersonInstanciate1) {
	Person johnDoe = Person("John", "Doe", Gender::other);
	std::string firstname, lastname, gender;
	firstname = "John";
	lastname = "Doe";
	gender = "other";
	
	EXPECT_EQ(firstname, johnDoe.getFirstname());
	EXPECT_EQ(lastname, johnDoe.getLastname());
	EXPECT_EQ(gender, johnDoe.getGender());
	
}