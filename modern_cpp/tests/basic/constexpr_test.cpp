#include <gtest/gtest.h>

#include "setup.h"


using namespace std;

class ConstexprTestCase : public ::testing::Test {
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

class Cat {
public:
    // constexpr must be initialized
    static constexpr int numHindLegs = 4;
    static const int age;

};
const int Cat::age = 3;

constexpr int some_constexpr_function(int i){
    if (i < 3) { return i + 2; }

    int *ptr = new int(1);
    return i - 2;
}

constexpr int factorial_const_expr(int n){
    auto result = 1;
    for(auto i = 1; i <= n; ++i){
        result *= i;
    }
    return result;
}

constexpr int increment(int& n){ return ++n; }
constexpr int incr1(int k) { int x = increment(k); return x; }
// does not work bc lifetime of k began outside of expression (not a core constant)
// constexpr int incr2(int k) { constexpr int x = increment(k); return x; }

template<int N>
constexpr int value = N;

TEST_F(ConstexprTestCase, constexpr_variable) {
    EXPECT_EQ(Cat::age, 3);
    EXPECT_EQ(Cat::numHindLegs, 4);
}

TEST_F(ConstexprTestCase, constexpr_function) {
    // error without constexpr: variable sized object might not be initialized
    int a[factorial_const_expr(3)] = {};
    EXPECT_EQ(size(a), 6);

}

TEST_F(ConstexprTestCase, constexpr_function_context) {
    constexpr int v1 = some_constexpr_function(1);
    EXPECT_EQ(v1, 3);

    // non constexpr context
    int v2 = some_constexpr_function(3);
    EXPECT_EQ(v2, 1);

    // does not work!
    // constexpr int v3 = some_constexpr_function(4);
}

TEST_F(ConstexprTestCase, constexpr_function_core_constant) {
    constexpr int v = incr1(1);
    EXPECT_EQ(v, 2);
}

TEST_F(ConstexprTestCase, constexpr_variable_template) {
    // factorial function is run at compile time
    int v = value<factorial_const_expr(3)>;
    EXPECT_EQ(v, 6);

}

