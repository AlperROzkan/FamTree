#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include <person.hpp>
#include <utils.hpp>

namespace fs = std::filesystem;
unsigned int Person::id = 0;


class UtilsTest : public testing::Test {
protected:
	Person* john;
	Person* helen;
	Person* paul;
	Person* eliott;

	virtual void SetUp() override {
		john = new Person("John", "Doe", Gender::male);
		helen = new Person("Helen", "Smith", Gender::female);
		paul = new Person("Paul", "Doe", Gender::male);
		eliott = new Person("Eliott", "Doe", Gender::male);
	}

	virtual void TearDown() override {
		delete john;
		delete helen;
		delete paul;
		delete eliott;
	}
};

TEST_F(UtilsTest, readFromFile1) {
	std::string s = famTree::readFromFile(fs::path(PROJECT_PATH) /= "tests/readFromFileTest.txt");
	EXPECT_EQ(s, "Test reading file");
}

TEST_F(UtilsTest, readFromFile2) {
	std::string s = famTree::readFromFile(fs::path(PROJECT_PATH) /= "tests/readFromFileTest.txt");
	EXPECT_NE(s, "Test reading file unequal");
}

TEST_F(UtilsTest, writeToFile1) {
	std::string messageToWrite = "Test write to file";
	fs::path pathToTestFile = fs::path(PROJECT_PATH) /= "tests/writeToFile.txt";
	famTree::writeToFile(messageToWrite, pathToTestFile);
	EXPECT_EQ(messageToWrite, famTree::readFromFile(pathToTestFile));
}

TEST_F(UtilsTest, serializeToFile1) {
}