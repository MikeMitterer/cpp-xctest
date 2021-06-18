#include "setup.h"
#include "utils.h"

#include <gtest/gtest.h>

class DecayFunctionTestCase : public ::testing::Test {
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

const uint64_t mSToSFactor = 1000; // Conversion factor for milliseconds to seconds

const unsigned long maxLoopTime =  60; // loop time in seconds
const unsigned long initialLoopDelayTicks = 20; // initial delay of 100ms
const unsigned long maxLoopDelayTicks = 220; // initial delay of 100ms

const unsigned long getDecayedDelayTicks(const unsigned long currentLoopMillis){
    unsigned long decayedDelayTicks = ((maxLoopDelayTicks - initialLoopDelayTicks) / (double)(maxLoopTime * mSToSFactor)) *
                                      currentLoopMillis + initialLoopDelayTicks;
    return decayedDelayTicks;
}

TEST_F(DecayFunctionTestCase, test_linearTickDecay) {
    std::cout << getDecayedDelayTicks(0 * mSToSFactor) << std::endl;
    std::cout << getDecayedDelayTicks(30 * mSToSFactor) << std::endl;
    std::cout << getDecayedDelayTicks(60 * mSToSFactor) << std::endl;
    
    EXPECT_EQ(getDecayedDelayTicks(0 * mSToSFactor), initialLoopDelayTicks);
    EXPECT_EQ(getDecayedDelayTicks(maxLoopTime / 2 * mSToSFactor),
              (initialLoopDelayTicks + maxLoopDelayTicks) / 2);
    EXPECT_EQ(getDecayedDelayTicks(maxLoopTime * mSToSFactor), maxLoopDelayTicks);
}
