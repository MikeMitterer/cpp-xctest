#include <utility>

//
// Created by Mike Mitterer on 2019-01-19.
//

#include <stdafx.h>

#include "setup.h"
#include "tdd/Name.h"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>



// Static initializer
std::string Name::lastname { "Mitterer" };

class CTORTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    virtual void SetUp() { testSetup = new TestSetup(); }
    virtual void TearDown() { delete testSetup; testSetup = nullptr; }
};

TEST_F(CTORTestCase, simple_ctor) {
    auto logger = testSetup->getLogger();

    const Name name("Gerda") ;
    logger->debug(name.firstname);
    logger->debug(name.getAge());

    Name mike("Mike");
    logger->debug(mike.getNameWithBrackets());
    logger->debug(mike.lastname);
    logger->debug(Name::getLastName());

    EXPECT_EQ(true, true);
}

TEST_F(CTORTestCase, cpy_ctor) {
    auto logger = testSetup->getLogger();

    const Name mike("Mike");
    Name anotherName(mike);

    EXPECT_EQ(anotherName.firstname,mike.firstname);
}

/*
// Geht nicht - wird als Fehler angezeigt!
std::string& getMyName() {
    std::string name { "Mike"};
    return name;
}
*/

std::string getMyName() {
    std::string name { "Mike"};
    return name;
}

TEST_F(CTORTestCase, ret_by_ref) {
    auto logger = testSetup->getLogger();

    auto name = getMyName();

    logger->info("My name:" + name);
}


