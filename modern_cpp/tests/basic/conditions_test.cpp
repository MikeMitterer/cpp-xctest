#include <gtest/gtest.h>

#include "stdafx.h"
#include "setup.h"


using namespace std;


class ConditionTestCase : public ::testing::Test {
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


TEST_F(ConditionTestCase, switch_case){
    enum number {ZERO, ONE, TWO, THREE, FOUR, FIVE};
    number num = TWO;

    switch (num) {
        case ZERO: // valid handling of two cases being handled equally
        case ONE:
            cout << "value smaller than one" << endl;
            break;
        case TWO:
            cout << "value equals two" << endl;
            [[fallthrough]]; // explicitly document missing break statement
        case THREE:
            cout << "value smaller than four" << endl;
            break;
        case FOUR:
            cout << "value equals four" << endl;
            break;
        default:
            // always include default statement unless all classes are handled (e.g. enumeration)
            cout << "value greater four" << endl;
            break;
    }
    EXPECT_EQ(true, true);
}
