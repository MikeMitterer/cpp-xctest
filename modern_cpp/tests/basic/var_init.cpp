#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-equals-delete"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <stdafx.h>

#include <utility>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include "setup.h"

class Integer {
private:
    Logger logger = DefaultLogger::get(DefaultLogger::TEST_LOGGER);

public:
    static uint8_t nrOfCTORCalls;

    const int age;

    std::string name;

    std::vector<int> myValues;

    Integer() = delete;

    Integer(std::string name, int age)
            : age{ age }, name{ std::move(name) } {
        nrOfCTORCalls++;

        logger->info("Integer(std::string name, int age)");
    }

    Integer(std::initializer_list<int> values) : age{ 99} {
        for(auto value : values) {
            myValues.push_back(value);
        }
    }

    explicit Integer(int age) : age{ age }, name{ "undefined" } {
        nrOfCTORCalls++;

        logger->info("Integer(const int age)");
    }

    explicit Integer(std::string name) : age{ -1 }, name{ std::move(name) } {
        nrOfCTORCalls++;
        logger->info("Integer(std::string name)");
    }

    // Da der CTOR nicht explicit ist wird der
    // call "Integer name2 = "Gerda";" mit diesem CTOR durch den compiler realisiert
    Integer(const char* name) : age{ -1 }, name{ name } { // NOLINT(google-explicit-constructor)
        nrOfCTORCalls++;
        logger->info("Integer(const char* name)");
    }

};

uint8_t Integer::nrOfCTORCalls = 0;

class VarInitTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    void SetUp() override {
        delete testSetup;
        testSetup = new TestSetup();
        Integer::nrOfCTORCalls = 0;
    }

    void TearDown() override {
        delete testSetup;
        testSetup = nullptr;
    }
};

TEST_F(VarInitTestCase, init_array) {
    auto logger = testSetup->getLogger();

    int list[] = { 1, 2, 3 };
    EXPECT_EQ(list[1], 2);

    const std::vector<int> list2{ 1, 2, 3 };
    EXPECT_EQ(list2[1], 2);

    auto list3 = std::vector<int>{ 1, 2, 3 };
    EXPECT_EQ(list3[1], 2);

    auto list4 = std::vector<int>(2, -1);
    EXPECT_EQ(list4[1], -1);
    EXPECT_EQ(list4.size(), 2);
}

TEST_F(VarInitTestCase, auto_type_conversion) {
    // CTOR wird automatisch aufgerufen - Integer(const int age)
    const Integer i = Integer{ 5 };

    EXPECT_EQ(i.age, 5);
    EXPECT_EQ(i.nrOfCTORCalls, 1);
}

TEST_F(VarInitTestCase, explicit_conversion) {
    auto name = Integer("Mike");
    EXPECT_EQ(name.nrOfCTORCalls, 1);
}

TEST_F(VarInitTestCase, test_nr_of_calls_1) {
    auto firstname = std::string("Mike");
    auto name = Integer(firstname);

    EXPECT_EQ(name.nrOfCTORCalls, 1);
}

TEST_F(VarInitTestCase, test_nr_of_calls_param_as_charpointer) {
    auto name = Integer("Mike");

    EXPECT_EQ(name.nrOfCTORCalls, 1);

    Integer name2 = "Gerda";
    EXPECT_EQ(name.nrOfCTORCalls, 2);
}

TEST_F(VarInitTestCase, simple_initializer_list) {
    std::initializer_list<int> values{ 1, 3, 7};

    EXPECT_EQ(values.begin()[0], 1);
    EXPECT_EQ(values.begin()[1], 3);
    EXPECT_EQ(values.begin()[2], 7);

    auto sum = 0;
    for(auto value : values) {
        sum += value;
    }

    EXPECT_EQ(sum,11);
}

TEST_F(VarInitTestCase, ctor_with_initializer_list) {
    auto name = Integer{1,2,7};

    EXPECT_EQ(name.myValues.back(), 7);
}

TEST_F(VarInitTestCase, remove_element_from_vector) {
    std::vector values{1,2,3};

    auto iterator = values.begin();
    iterator += 2;

    // Löscht das letzte Element
    values.erase(iterator);

    EXPECT_EQ(values.size(), 2);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
}

#pragma clang diagnostic pop
