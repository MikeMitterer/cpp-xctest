#include <gtest/gtest.h>

#include <utility>

#include "setup.h"


using namespace std;

class ConstTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    void SetUp() override {
        delete testSetup;
        testSetup = new TestSetup();
    }

    void TearDown() override {
        delete testSetup;
        testSetup = nullptr;
    }
};

class Cat{
private:
    // Rule 1: make objects immutable by default
    // Rule 4: use const to define objects that do not change after construction
    const std::string name;
    mutable int age;

public:
    static constexpr int numHindLegs = 2;
    static constexpr int numForeLegs = 2;

public:
    // Rule 3: pass pointers and references to consts
    // using std::move instead of const std::string& bc move is faster than copying
    explicit Cat(std::string  _name, const int& _age) : name{std::move(_name)}, age{_age} {};

    [[nodiscard]]
    // Rule 2: member function should be const by default
    int getAge() const {
        return age;
    }

    void incrementAge() const {
        age++;
    }

    // Rule 5: use constexpr for values that can be computed at compile time
    constexpr int getNumLegs() const {
        return numHindLegs + numForeLegs;
    }

};

TEST_F(ConstTestCase, const_membe_functions) {
    Cat pebbles{"Pebbles", 5};
    // name cannot be modified after initialization

    EXPECT_EQ(pebbles.getAge(), 5);
    EXPECT_EQ(pebbles.numHindLegs, 4);

    const Cat niki{"Niki", 9};
    EXPECT_EQ(niki.getAge(), 9);

    // const method from const object can only modify age because of keyword mutable
    niki.incrementAge();
    EXPECT_EQ(niki.getAge(), 10);

    EXPECT_EQ(niki.getNumLegs(), 4);
}


