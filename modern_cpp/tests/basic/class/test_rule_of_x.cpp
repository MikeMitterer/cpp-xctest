#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-equals-delete"
#pragma ide diagnostic ignored "hicpp-use-equals-delete"
#pragma ide diagnostic ignored "cert-err58-cpp"

//
// Created by Mike Mitterer on 02.11.15.
//

#include "gtest/gtest.h"
#include "rule_of_x.h"

#include "setup.h"

//Resource createObjectTest(bool condition);

class RuleOfXTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    void SetUp() override {
        delete testSetup; testSetup = nullptr;
        testSetup = new TestSetup();

        RuleOf5::functionCalls.assign(RuleOf5::functionCalls.size(),0);
    }

    void TearDown() override { delete testSetup; testSetup = nullptr; }
};

TEST_F(RuleOfXTestCase, test_default_ctor) {
    //auto logger = testSetup->getLogger();
    {
        auto ado = RuleOf5();

        ASSERT_STREQ(ado.getName(),"<null>");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::DefaultCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}

TEST_F(RuleOfXTestCase, test_ctor) {
    {
        auto ado = RuleOf5{"Mike"};

        ASSERT_STREQ(ado.getName(),"Mike");
    }
    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}

// Klassischer Anwendungsfall für einen Copy-CTOR
//  - neues Objekt wird basierend auf einem anderen object erzeugt
//
//       auto rule2 = rule1;
//
TEST_F(RuleOfXTestCase, test_copy_ctor) {
    {
        // Param CTOR
        auto rule1 = RuleOf5{"Mike"};

        // Copy CTOR (Initialisierung!!!!)
        auto rule2 = rule1;

        ASSERT_STREQ(rule1.getName(),"Mike");
        ASSERT_STREQ(rule2.getName(),"Mike");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 4);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::CopyCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 2);
}

// Return value optimization (RVO)
// Copy-CTOR wird hier vom Compiler wegoptimiert
//
// Bei der Rückgabe wird keine Kopie angelegt
// https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization
RuleOf5 functionReturnsObjectByValue(bool choose = true) {
    if(choose) {
        // Param CTOR
        return RuleOf5{ "Gerda" };
    }
    // Param CTOR
    return RuleOf5{ "Mike" };
}

// Copy-CTOR - rückgabe per value aus Funktion
// Funktioniert hier aber nicht da die copy-Funktion wegoptimiert wird
TEST_F(RuleOfXTestCase, test_copy_ctor2) {
    {
        auto rule { functionReturnsObjectByValue() };

        ASSERT_STREQ(rule.getName(),"Gerda");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
// Beim aufruf der Funktion verwendet der Compiler den Copy-CTOR
void functionTakesObjectByValue(const RuleOf5 ruf) {
    ruf.getName();
}
#pragma clang diagnostic pop

// Übergabe eines objektes per value
TEST_F(RuleOfXTestCase, test_copy_ctor3) {
    {
        // Param CTOR
        auto mike { RuleOf5{ "Mike" } };

        // Copy-CTOR
        functionTakesObjectByValue(mike);
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 4);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::CopyCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 2);
}

TEST_F(RuleOfXTestCase, test_move_ctor) {
    {
        // Param-CTOR
        RuleOf5 rof1{ "Donald" };

        // Move-CTOR
        auto rof2 = std::move(rof1);

        ASSERT_STREQ(rof2.getName(),"Donald");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 4);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::MoveCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 2);
}

TEST_F(RuleOfXTestCase, test_assignement_operator) {
    {
        auto ado1 = RuleOf5{"Mike"};
        auto ado2 = RuleOf5{"Gerda"};

        // copy assignment operator
        ado1 = ado2;

        ASSERT_STREQ(ado1.getName(),"Gerda");
        ASSERT_STREQ(ado2.getName(),"Gerda");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 5);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 2);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::AssignmentOperator), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 2);
}

TEST_F(RuleOfXTestCase, test_move_assignement) {
    {
        auto ado1 = RuleOf5{};
        auto ado2 = RuleOf5{"Mike"};

        ado1 = std::move(ado2);

        ASSERT_STREQ(ado1.getName(),"Mike");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 5);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::DefaultCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::MoveAssignmentOperator), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 2);
}

TEST_F(RuleOfXTestCase, operator_conversion) {
    {
        auto ruf = RuleOf5{"Mike"};
        std::string name = ruf;

        ASSERT_TRUE(name == "Mike");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}

TEST_F(RuleOfXTestCase, ofstream_test) {
    {
        std::stringstream buffer;
        auto ruf = RuleOf5{"Mike"};

        buffer << ruf;

        auto result = buffer.str();

        ASSERT_TRUE(result == "Mike");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}


#pragma clang diagnostic pop
