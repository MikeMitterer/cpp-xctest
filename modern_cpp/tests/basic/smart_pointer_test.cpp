//
// Created by Mike Mitterer on 02.11.15.
//

#include <memory>

#include "gtest/gtest.h"

#include "rule_of_x.h"
#include "setup.h"


class PointerTest {
    virtual std::string _class() { return "PointerTest"; }

private:
    const Logger logger = DefaultLogger::get(_class());

public:
    PointerTest() {
        logger->debug("created");
    }

    bool greet() {
        logger->debug("Hi");
        return true;
    }

    virtual ~PointerTest() {
        logger->debug("deleted");
    }
};

class PointerTestWithUniquePtrArray {
private:


    // Das funktioniert nicht!
    // std::unique_ptr<PointerTest[]> memberVar(new PointerTest[2]);

    // Das schon
    std::unique_ptr<PointerTest[]> memberVar{new PointerTest[2]};

    // Über die Initializer-List funktioniert es auch (V2)
    //std::unique_ptr<PointerTest[]> memberVar;

public:
    PointerTestWithUniquePtrArray()
            /* V2 - Initializer-List : memberVar{ new PointerTest[2]} */ {
    }

};

class SmartPointerTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    virtual void SetUp() { testSetup = new TestSetup(); }
    virtual void TearDown() { delete testSetup; testSetup = nullptr; }
};

TEST_F(SmartPointerTestCase, simple_test) {
    std::unique_ptr<int> pTest(new int);

    *pTest = 10;
    EXPECT_EQ(*pTest,10);
}

TEST_F(SmartPointerTestCase, with_class) {
    std::unique_ptr<PointerTest> pTest(new PointerTest);

    EXPECT_EQ(pTest->greet(),true);
}

TEST_F(SmartPointerTestCase, with_array) {
    std::unique_ptr<PointerTest[]> pTest(new PointerTest[5]);

    // Zugriff über punkt!
    EXPECT_EQ(pTest[0].greet(),true);
}

TEST_F(SmartPointerTestCase, shared_pointer) {

    std::shared_ptr<PointerTest> pTest = std::make_shared<PointerTest>();
    std::shared_ptr<PointerTest> pTest2 = pTest;

    std::cout << "Finished" << std::endl;
}

TEST_F(SmartPointerTestCase, shared_pointer_with_scope) {

    std::shared_ptr<PointerTest> pTest2{nullptr};

    {
        // pTest geht "out of scope", die "deleted" Ausgabe kommt aber erst nach "Finished"
        std::shared_ptr<PointerTest> pTest = std::make_shared<PointerTest>();

        pTest2 = pTest;
    }

    std::cout << "Finished" << std::endl;
}



