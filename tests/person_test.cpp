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
}

TEST_F(PersonTest, personDeserialize2) {
	jsonJohnDoe["relations"]["child"] = { 42 };
	Person* p = Person::deserializePerson(jsonJohnDoe);
	EXPECT_EQ(jsonJohnDoe["firstname"], p->getFirstname());
	EXPECT_EQ(jsonJohnDoe["lastname"], p->getLastname());
	EXPECT_EQ(jsonJohnDoe["gender"], p->getGender());
	EXPECT_TRUE(p->getChildren().contains(42));
}

TEST_F(PersonTest, personSerDePerson1) {
	json j = johnDoe->serializeSimplePerson();
	Person* p = Person::deserializeSimplePerson(j);
	EXPECT_EQ(p->getFirstname(), johnDoe->getFirstname());
	EXPECT_EQ(p->getLastname(), johnDoe->getLastname());
	EXPECT_EQ(p->getGender(), johnDoe->getGender());
}
