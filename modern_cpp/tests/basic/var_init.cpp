#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-equals-delete"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <stdafx.h>

#include <utility>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <typeinfo>
#include <sstream>

#include "setup.h"

class Person {
private:
    Logger logger = DefaultLogger::get(DefaultLogger::TEST_LOGGER);

public:
    static uint8_t nrOfCTORCalls;

    const int age;

    std::string name;

    std::vector<int> myValues;

    std::vector<std::string> myPetNames;

    Person() = delete;

    // const auto p1 = Person{"Mike"};
    // const Person name = p1;
    // Person(const Person& person) = delete;

    Person(std::string name, int age)
            : age{ age }, name{ std::move(name) } {

        nrOfCTORCalls++;

        logger->info("Person(std::string name, int age)");
    }

    Person(std::initializer_list<int> values) : age{ 99 } {
        nrOfCTORCalls++;

        for(auto value : values) {
            myValues.push_back(value);
        }
    }

    explicit Person(std::vector<std::string> petNames) : age{ -1 }, myPetNames{std::move( petNames )}{
        nrOfCTORCalls++;

        logger->info("Person(std::vector<std::string> petNames)");
    }

    explicit Person(int age) : age{ age }, name{ "undefined" } {
        nrOfCTORCalls++;

        logger->info("Person(const int age)");
    }

    explicit Person(std::string name) : age{ -1 }, name{ std::move(name) } {
        nrOfCTORCalls++;
        logger->info("Person(std::string name)");
    }

    // Da der CTOR nicht explicit ist wird der
    // call "Person name2 = "Gerda";" mit diesem CTOR durch den compiler realisiert
    Person(const char* name) : age{ -1 }, name{ name } { // NOLINT(google-explicit-constructor)
        nrOfCTORCalls++;
        logger->info("Person(const char* name)");
    }

};

std::string genUserName(const Person& person){
    std::ostringstream oss;
    oss << person.name << person.age;
    std::string username = oss.str();
    return username;
}

uint8_t Person::nrOfCTORCalls = 0;

class VarInitTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    void SetUp() override {
        delete testSetup;
        testSetup = new TestSetup();
        Person::nrOfCTORCalls = 0;
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

    int list1[]{ 1, 2, 3 };
    EXPECT_EQ(list1[1], 2);

    const std::vector<int> list2{ 1, 2, 3 };
    EXPECT_EQ(list2[1], 2);

    std::vector<int> list3 = std::vector<int>{ 1, 2, 3 };
    EXPECT_EQ(list3[1], 2);

    std::vector<int> list4 = std::vector<int>(2, -1);
    EXPECT_EQ(list4[1], -1);
    EXPECT_EQ(list4.size(), 2);
}

TEST_F(VarInitTestCase, init_array_auto) {
    auto logger = testSetup->getLogger();

    auto int1 = {42};
    EXPECT_EQ(typeid(int1), typeid(std::initializer_list<int>));
    EXPECT_EQ(int1.size(), 1);
    EXPECT_EQ(*int1.begin(), 42);

    //Person p1 = Person("Sarah", int1); does not work!
    const Person p1 = Person{int1};
    EXPECT_EQ(*(p1.myValues.begin()), 42);

    auto int2 {42};
    EXPECT_EQ(typeid(int2), typeid(int));
    EXPECT_EQ(int2, 42);

    // auto list1 {1, 2};   does not work at all since C++17 -> too many expressions
    auto list1 = {1, 2};
    EXPECT_EQ(typeid(list1), typeid(std::initializer_list<int>));
    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(*list1.begin(), 1);
    EXPECT_EQ(*(list1.end() - 1), 2);

    auto list3 = std::vector<int>{ 1, 2, 3 };
    EXPECT_EQ(list3[1], 2);

    auto list4 = std::vector<int>(2, -1);
    EXPECT_EQ(list4[1], -1);
    EXPECT_EQ(list4.size(), 2);
}

TEST_F(VarInitTestCase, auto_type_conversion) {
    // CTOR Person(const int age) wird NICHT verwendet, stattdessen wird der
    // CTOR Person(std::initializer_list<int> values) verwendet
    const Person p1 = Person{ 5 };
    EXPECT_EQ(p1.age, 99);
    EXPECT_EQ(*p1.myValues.begin(), 5);
    EXPECT_EQ(p1.nrOfCTORCalls, 1);

    // CTOR Person(std::string name) wird hier allerdings verwendet
    const Person p2 = Person{"Sarah"};
    EXPECT_EQ(p2.name, "Sarah");
    EXPECT_EQ(p1.nrOfCTORCalls, 2);

    const Person p3 = { "Sarah", 25};
    // Alternativ: const Person p3{ "Sarah", 25};
    EXPECT_EQ(p3.name, "Sarah");
    EXPECT_EQ(p3.age, 25);
}

TEST_F(VarInitTestCase, explicit_conversion) {
    auto name = Person("Mike");
    EXPECT_EQ(name.nrOfCTORCalls, 1);
}

TEST_F(VarInitTestCase, temp_object) {
    auto username = genUserName({"BlauerFalke", 95});
    EXPECT_EQ(username, "BlauerFalke95");

    auto username2 = genUserName({"Sarah"});
    EXPECT_EQ(username2, "Sarah-1");

    auto username3 = genUserName(Person{"Sarah", 25});
    EXPECT_EQ(username3, "Sarah25");

}

TEST_F(VarInitTestCase, init_list_vector) {
    std::vector<std::string> pets {"Marie", "Sophie", "Niki", "Pebbles"};

    Person p1 = Person{pets};

    EXPECT_EQ(p1.myPetNames[2], "Niki");
}

TEST_F(VarInitTestCase, test_nr_of_calls_1) {
    auto firstname = std::string{"Mike"};
    auto name = Person{firstname};

    EXPECT_EQ(name.nrOfCTORCalls, 1);
}

TEST_F(VarInitTestCase, test_nr_of_calls_param_as_charpointer) {
    const auto p1 = Person{"Mike"};
    const Person name = p1;

    EXPECT_EQ(name.nrOfCTORCalls, 1);

    Person name2 = "Gerda";
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
    auto name = Person{ 1, 2, 7};

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

TEST_F(VarInitTestCase, testLambdaWithArrayAsReturnValue) {
    std::function<std::vector<uint8_t> ()> callback = [] () {
//        std::vector<uint8_t> test = { 1,2 };
//        return test;
        return std::vector<uint8_t>{ 1 ,2 ,3 };
    };

    // EXPECT_EQ(values[1], 2);
}




#pragma clang diagnostic pop
