#include "stdafx.h"
#include "setup.h"
#include "template_test.h"

#include <utility>
#include <gtest/gtest.h>


using namespace std;

class TemplateTestCast : public ::testing::Test {
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

TEST_F(TemplateTestCast, functionTemplate) {

    EXPECT_EQ(toString("Mike"), "Mike");

    EXPECT_EQ(toString(10), "10");
    EXPECT_EQ(toString(M_PI + 10.0), "13.14");
    EXPECT_EQ(toString(M_PI + 100.0), "103.14");

    EXPECT_EQ(toString(3.14f), "3.14f");
}


