#include <stdafx.h>

#include <utility>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <regex>

#include "setup.h"

/**
 * Helper für die Tests
 */
class StringTestCase : public ::testing::Test {
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

std::vector<std::string> split(const std::string& subject,const std::string& separator ="\\s+") {
    const std::regex re{separator};
    std::vector<std::string> container{
            std::sregex_token_iterator(subject.begin(), subject.end(), re, -1),
            std::sregex_token_iterator()
    };
    return container;
}

TEST_F(StringTestCase, string_stream) {
    auto logger = testSetup->getLogger();

    std::stringstream ss;
    ss << "Mike";

    logger->info(ss.str());
    EXPECT_STREQ(ss.str().c_str(),"Mike");
}

TEST_F(StringTestCase, string_stream_with_format) {
    auto logger = testSetup->getLogger();

    std::stringstream ss;

    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss.precision(2);

    ss << "Mike" << " age: " << 99.9;

    logger->info(ss.str());
    EXPECT_STREQ(ss.str().c_str(),"Mike age: 99.90");
}

TEST_F(StringTestCase, toString) {
    EXPECT_STREQ(std::to_string(5).c_str(),"5");
}

TEST_F(StringTestCase, to_array) {
    std::string array{ "1 2 3" };

    auto splitted = split(array);

    EXPECT_EQ(splitted.size(),3);
    EXPECT_STREQ(splitted[1].c_str(),"2");
}
