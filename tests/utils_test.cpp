#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include <person.hpp>
#include <utils.hpp>

namespace fs = std::filesystem;

class UtilsTest : public testing::Test {
protected:
	virtual void SetUp() override {

	}

	virtual void TearDown() override {

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