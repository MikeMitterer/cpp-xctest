#include <utility>
#include <gtest/gtest.h>

#include "stdafx.h"
#include "setup.h"


using namespace std;

class Cat {
private:
    vector<string> furColours{ "white", "grey", "orange" };

public:
    string firstname{ "Pebbles" };

    // TODO: Nochmal checken...
    const vector<string>& getFurColours() { return furColours; };
};


class LoopTestCase : public ::testing::Test {
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

TEST_F(LoopTestCase, range_based_for_loop) {
    const vector<string> vs = { "Hello", "World" };
    int counter = 0;

    // use reference to avoid expensive copies
    // use const if variable isn't modified or copied
    for (const string& s : vs) {
        cout << s << endl;
        counter++;
    }

    EXPECT_EQ(counter, vs.size());
}

TEST_F(LoopTestCase, range_based_for_loop_with_init) {
    int counter = 0;

    // in C++20 initializations statements can be used in a range-for
    for (Cat ourBelovedCat; const auto& colour : ourBelovedCat.getFurColours()) {
        cout << ourBelovedCat.firstname << "' fur is " << colour << endl;
        counter++;
    }

    Cat testCat;
    EXPECT_EQ(counter, testCat.getFurColours().size());
}

TEST_F(LoopTestCase, range_based_for_loop_with_init_idx) {
    const vector<vector<uint8_t>> matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 }
    };

    for (int rowIdx = 0; const auto& row : matrix) {
        for (int columnIdx = 0; const auto& value : row) {
            cout << "Value " << unsigned(value) << " in row " << rowIdx + 1 << " and column "
                 << columnIdx + 1 << endl;
            EXPECT_EQ(matrix[rowIdx][columnIdx], value);
            columnIdx++;
        }
        rowIdx++;
    }
}

TEST_F(LoopTestCase, range_based_for_loop_with_map) {
    map<int, string> numberMap({
        { 1, "one" },
        { 2, "two" },
        { 3, "three" }
    });

    numberMap.insert(std::pair<int, string>(4, "four"));

    int counter = 0;
    for (auto i : numberMap) {
        std::cout << '{' << i.first << ", " << i.second << "}\n";
        counter++;
    }

    EXPECT_EQ(counter, numberMap.size());
}

TEST_F(LoopTestCase, breaking_out_of_loop_break) {
    const vector<vector<uint8_t>> matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 }
    };

    int counter = 0;
    uint8_t maxValue = 4;

    for (const vector<uint8_t>& row : matrix)
        for (const uint8_t& value : row) {
            // minimize use of break and continue!
            // however break is usually the better alternative to goto
            if (value > maxValue) break;

            cout << unsigned(value) << endl;
            counter++;
        }

    cout << "broken out of loop" << endl;

    EXPECT_EQ(counter, maxValue);
}

TEST_F(LoopTestCase, breaking_out_of_loop_goto) {
    const vector<vector<uint8_t>> matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 }
    };

    int counter = 0;
    uint8_t maxValue = 4;
    for (const vector<uint8_t>& row : matrix)
        for (const uint8_t& value : row) {
            // goto should be avoided where possible, if needed in a nested for-loop
            // -> always jump forwards
            if (value > maxValue) goto finished;

            cout << unsigned(value) << endl;
            counter++;
        }

    finished:
    cout << "broken out of loop" << endl;

    EXPECT_EQ(counter, maxValue);
}
