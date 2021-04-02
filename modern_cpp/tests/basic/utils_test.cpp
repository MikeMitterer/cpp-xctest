#include <stdafx.h>

#include "setup.h"
#include "utils.h"

#include <utility>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <regex>



/**
 * Helper für die Tests
 */
class UtilsTestCase : public ::testing::Test {
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



TEST_F(UtilsTestCase, tolower) {
    EXPECT_STREQ(mm::utils::toLower("Mike").c_str(), "mike");
    EXPECT_STREQ(mm::utils::toLower("").c_str(), "");
}

TEST_F(UtilsTestCase, removeSpace) {
    EXPECT_STREQ(mm::utils::removeSpace("Dies ist ein Test").c_str(), "DiesisteinTest");
}

