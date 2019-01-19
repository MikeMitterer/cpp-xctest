//
// Created by Mike Mitterer on 02.11.15.
//

#include "gtest/gtest.h"
#include "rule_of_x.h"

#include <memory>

class PointerTest {

public:
    PointerTest() {
        std::cout << "created" << std::endl;
    }

    bool greet() {
        std::cout << "Hi!" << std::endl;
        return true;
    }

    virtual ~PointerTest() {
        std::cout << "deleted" << std::endl;
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

TEST(smart_pointer_test, simple_test) {
    std::unique_ptr<int> pTest(new int);

    *pTest = 10;
    EXPECT_EQ(*pTest,10);
}

TEST(smart_pointer_test, with_class) {
    std::unique_ptr<PointerTest> pTest(new PointerTest);

    EXPECT_EQ(pTest->greet(),true);
}

TEST(smart_pointer_test, with_array) {
    std::unique_ptr<PointerTest[]> pTest(new PointerTest[5]);

    // Zugriff über punkt!
    EXPECT_EQ(pTest[0].greet(),true);
}

TEST(smart_pointer_test, shared_pointer) {

    std::shared_ptr<PointerTest> pTest = std::make_shared<PointerTest>();
    std::shared_ptr<PointerTest> pTest2 = pTest;

    std::cout << "Finished" << std::endl;
}

TEST(smart_pointer_test, shared_pointer_with_scope) {

    std::shared_ptr<PointerTest> pTest2{nullptr};

    {
        // pTest geht "out of scope", die "deleted" Ausgabe kommt aber erst nach "Finished"
        std::shared_ptr<PointerTest> pTest = std::make_shared<PointerTest>();

        pTest2 = pTest;
    }

    std::cout << "Finished" << std::endl;
}



