#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-use-equals-delete"
#pragma ide diagnostic ignored "cert-err58-cpp"

//
// Created by Mike Mitterer on 02.11.15.
//

#include "gtest/gtest.h"
#include "rule_of_x.h"

#include "setup.h"

Resource createObjectTest(bool condition);

AllDefaultOperators getTempValueViaCopyElision();
AllDefaultOperators getTempValueViaMoveCTOR();

void moveCTOR(const TestSetup& setup, AllDefaultOperators operators);

class RuleOfXTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    void SetUp() override {
        delete testSetup; testSetup = nullptr;
        testSetup = new TestSetup(); }

    void TearDown() override { delete testSetup; testSetup = nullptr; }
};

TEST_F(RuleOfXTestCase, test_instance_counter) {
    //auto logger = testSetup->getLogger();
    //logger->set_level(mm::DEFAULT_LOG_LEVEL);

    // Führt zu einer Fehlermeldung da dieser Konstruktor gelöscht wurde
    // const auto r1 = Resource{};

    const auto r1 = Resource{"Mike1"};
    EXPECT_EQ(r1.instanceCounter, 1);

    const auto r2 = Resource{"Mike2"};
    EXPECT_EQ(r1.instanceCounter, 2);
    EXPECT_EQ(r2.instanceCounter, 2);

    const auto r3 = createObjectTest(true);
    EXPECT_EQ(r1.instanceCounter, 4);
    EXPECT_EQ(r2.instanceCounter, 4);
    EXPECT_EQ(r3.instanceCounter, 4);
}

TEST_F(RuleOfXTestCase, test_default_ctor) {
    auto logger = testSetup->getLogger();

    auto ado = AllDefaultOperators();
    auto expectedResult = (UNDEFINED + MSG_CREATED_IN_DEFAULT_CTOR);

    ASSERT_STREQ(ado.getName(), expectedResult.c_str());
}

TEST_F(RuleOfXTestCase, test_ctor) {
    auto logger = testSetup->getLogger();

    auto ado = AllDefaultOperators{"Mike"};
    auto expectedResult = (std::string("Mike") + MSG_CREATED_IN_CTOR);

    ASSERT_STREQ(ado.getName(), expectedResult.c_str());
}

TEST_F(RuleOfXTestCase, test_copy_ctor) {
    auto logger = testSetup->getLogger();

    auto ado1 = AllDefaultOperators{"Mike"};
    auto ado2 = ado1;

    auto expectedName1 = (std::string{"Mike"} + MSG_CREATED_IN_CTOR);
    auto expectedName2 = (expectedName1 + MSG_CREATED_IN_COPY_CTOR);

    ASSERT_STREQ(ado2.getName(), expectedName2.c_str());
}

TEST_F(RuleOfXTestCase, test_assignement_operator) {
    auto logger = testSetup->getLogger();

    auto ado1 = AllDefaultOperators{"Mike"};
    auto ado2 = AllDefaultOperators{"Gerda"};

    // copy assignment operator
    ado1 = ado2;

    auto expectedName1 = (std::string{"Gerda"} + MSG_CREATED_IN_CTOR);
    auto expectedName2 = (std::string{"Gerda"} + MSG_CREATED_IN_CTOR);

    ASSERT_STREQ(ado1.getName(), expectedName1.c_str());
    ASSERT_STREQ(ado2.getName(), expectedName2.c_str());
}


TEST_F(RuleOfXTestCase, test_move_ctor) {
    auto logger = testSetup->getLogger();

    auto ado1 = AllDefaultOperators{"Sarah"};

    // Param von moveCTOR wird per Value übergeben
    moveCTOR(*testSetup, std::move(ado1));

    ASSERT_TRUE(ado1.getName() == nullptr);
}

TEST_F(RuleOfXTestCase, test_move_ctor2) {
    auto logger = testSetup->getLogger();

    auto ado1 = getTempValueViaCopyElision();

    auto expectedName1 = (std::string{"Pepples"} + MSG_CREATED_IN_CTOR);
    ASSERT_STREQ(ado1.getName(),expectedName1.c_str());
}

TEST_F(RuleOfXTestCase, test_move_ctor3) {
    auto logger = testSetup->getLogger();

    auto ado1 = getTempValueViaMoveCTOR();

    auto expectedName1 = (std::string{"Pepples2"} + MSG_CREATED_IN_CTOR);
    ASSERT_STREQ(ado1.getName(),expectedName1.c_str());
}

TEST_F(RuleOfXTestCase, test_move_assignement) {
    auto logger = testSetup->getLogger();

    auto ado1 = AllDefaultOperators{};
    auto ado2 = AllDefaultOperators{"Mike"};

    // copy assignment operator
    ado1 = ado2;

    auto expectedName1 = (std::string{"Mike"} + MSG_CREATED_IN_CTOR);
    auto expectedName2 = (std::string{"Mike"} + MSG_CREATED_IN_CTOR);

    ASSERT_STREQ(ado1.getName(), expectedName1.c_str());
    ASSERT_STREQ(ado2.getName(), expectedName2.c_str());

    // Move assignment wird aufgerufen
    ado1 = std::move(AllDefaultOperators{"Sarah"});
    expectedName1 = (std::string{"Sarah"} + MSG_CREATED_IN_CTOR);
    ASSERT_STREQ(ado1.getName(), expectedName1.c_str());
}

/// Return value optimization (RVO)
///
/// Bei der Rückgabe wird keine Kopie angelegt
/// https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization
Resource createObjectTest(bool condition) {
    const auto r1 = Resource("Gerda");
    const auto r2 = Resource("Sarah");

    return condition ? r1 : r2;
}

AllDefaultOperators getTempValueViaCopyElision() {
    auto ado1 = AllDefaultOperators{"Pepples"};

    // Move bringt hier nichts - copy elision!!!
    // Return value optimization!!!
    return ado1;
}

/// Die Funktion hat mehr als einen möglichen Rückgabewert!!!!
/// Move-CTRO wird aufgerufen
AllDefaultOperators getTempValueViaMoveCTOR() {
    auto ado1 = AllDefaultOperators{"Pepples2"};

    if(std::strcmp(ado1.getName(),"abc") == 0) {
        return AllDefaultOperators{"move-to-test"};;
    }
    return ado1;
}

/// Nur wenn der Param keine Adresse oder Referenze ist wird
/// der move constructor aufgerufen
void moveCTOR(const TestSetup& setup, AllDefaultOperators operators) {
    auto logger = setup.getLogger();

    logger->set_level(spdlog::level::debug);

    logger->debug("Inside function: {}",operators.getName());
}

#pragma clang diagnostic pop
