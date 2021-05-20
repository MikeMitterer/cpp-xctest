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
        // Konstruktor
        auto ado = RuleOf5();

        ASSERT_STREQ(ado.getName(),"<null>");

        // Destruktor - am Ende des Scopes
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::DefaultCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}

TEST_F(RuleOfXTestCase, test_user_defined_ctor) {
    {
        auto ado = RuleOf5{"Mike"};

        ASSERT_STREQ(ado.getName(),"Mike");
    }
    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}

TEST_F(RuleOfXTestCase, test_user_defined_ctor2) {
    {
        auto ado = RuleOf5{"Mike", "Mitterer", 99, { "Biken" }};

        ASSERT_STREQ(ado.getName(),"Mike");
        ASSERT_STREQ(ado.getHobbies().c_str(),"Biken");
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
        // (1) Param CTOR
        auto rule1 = RuleOf5{"Mike"};

        // (2) (3) Copy CTOR (Initialisierung!!!!)
        auto rule2 = rule1;

        ASSERT_STREQ(rule1.getName(),"Mike");
        ASSERT_STREQ(rule2.getName(),"Mike");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 5);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1); // (1)
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::CopyCTOR), 1);  // (2) - auf der linken Seite!
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::DelegateCTOR), 1); // (3)

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 2);
}

// Klassischer Anwendungsfall für einen Copy-CTOR
//  - neues Objekt wird basierend auf einem anderen object erzeugt
//
// Wie oben - allerdings hier mit dem zweiten, erweiterten Konstruktor!
// Bei diesem Sample wird auch ein Delegation-CTOR verwendet.
//
//       auto rule2 = rule1;
//
TEST_F(RuleOfXTestCase, test_copy_ctor2) {
    {
        // (1) Param CTOR
        auto rule1 = RuleOf5{"Mike", "Mitterer", 99, { "Snowboarden", "Biken"}};

        // (2) (3) Copy CTOR (Initialisierung!!!!)
        auto rule2 = rule1;

        ASSERT_STREQ(rule1.getName(),"Mike");
        ASSERT_STREQ(rule1.getFullName().c_str(),"Mike Mitterer");
        ASSERT_EQ(rule1.getAge(), 99);
        ASSERT_STREQ(rule1.getHobbies().c_str(),"Snowboarden, Biken");

        ASSERT_STREQ(rule2.getName(),"Mike");
        ASSERT_STREQ(rule2.getFullName().c_str(),"Mike Mitterer");
        ASSERT_EQ(rule2.getAge(), 99);
        ASSERT_STREQ(rule2.getHobbies().c_str(),"Snowboarden, Biken");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 5);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1); // (1)

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::CopyCTOR), 1);  // (2) - auf der linken Seite!

    // (2) ruft in der Initializer-Sektion den User-Defined-CTOR auf
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::DelegateCTOR), 1); // (3)

    // ACHTUNG! Obwohl 3x ein Konstruktor aufgerufen wird, wird nur 2x der Destruktor
    // aufgerufen. Der Grund ist, dass bei (2) eine CTOR-Delegation gemacht wird und somit
    // kein eigenes Object erstellt wird
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 2);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
// Beim aufruf der Funktion verwendet der Compiler den Copy-CTOR
void functionTakesObjectByValue(const RuleOf5 ruf) {
    ruf.getName();
}
#pragma clang diagnostic pop

// Übergabe eines objektes per value
TEST_F(RuleOfXTestCase, test_copy_ctor_function_call) {
    {
        // (1) Param CTOR
        auto mike { RuleOf5{ "Mike" } };

        // (2) (3) Copy-CTOR
        functionTakesObjectByValue(mike);
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 5);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);  // (1)
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::CopyCTOR), 1);   // (2)
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::DelegateCTOR), 1); // (3) Function-Call

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
TEST_F(RuleOfXTestCase, test_copy_ctor_return_value) {
    {
        // (1) (2)
        auto rule { functionReturnsObjectByValue() };

        ASSERT_STREQ(rule.getName(),"Gerda");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 2);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::Destructor), 1);
}

// Copy-CTOR - Das eigene Object wird übergeben
TEST_F(RuleOfXTestCase, test_copy_ctor_own_object) {
    {
        auto rule1 = RuleOf5("Sarah");
        auto rule2 = RuleOf5(rule1);

        ASSERT_STREQ(rule2.getName(),"Sarah");
    }

    ASSERT_EQ(RuleOf5::nrOfCalls(), 5);

    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::ParamCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::CopyCTOR), 1);
    ASSERT_EQ(RuleOf5::nrOfCalls(FunctionType::DelegateCTOR), 1);

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
